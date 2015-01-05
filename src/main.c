#include <pebble.h>
  
static Window *s_main_window;
static TextLayer *s_time_layer;

//Key IDs

enum {
  KEY_MESSAGE = 0,
};

//AppMessage send function. Send a key with a value to the JS part. 

void send_int(uint8_t key, uint8_t cmd)
{
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
 
    Tuplet value = TupletInteger(key, cmd);
    dict_write_tuplet(iter, &value);
 
    app_message_outbox_send();
}


/*

Call the send function with an int value for every button.

1-up
2-long up
3-select
4-long select
5-down
6-long down

*/

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_int(0, 3);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_int(0, 1);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_int(0, 5);
}

static void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_int(0, 4);
}

static void up_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_int(0, 2);
}

static void down_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_int(0, 6);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 700, select_long_click_handler, NULL);
  window_long_click_subscribe(BUTTON_ID_UP, 700, up_long_click_handler, NULL);
  window_long_click_subscribe(BUTTON_ID_DOWN, 700, down_long_click_handler, NULL);
}

static void update_time() {
  
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  
  static char buffer[] = "00:00";
  
  if(clock_is_24h_style() == true) {    
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {    
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }  
  text_layer_set_text(s_time_layer, buffer);
}

static void main_window_load(Window *window) {
  
  s_time_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(s_time_layer, GColorBlack);
  text_layer_set_text_color(s_time_layer, GColorClear);
  text_layer_set_text(s_time_layer, "00:00");
  
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));  
  
  update_time();
}

static void main_window_unload(Window *window) {  
  text_layer_destroy(s_time_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}
  
static void init() {
 
  s_main_window = window_create();  
  window_set_click_config_provider(s_main_window, click_config_provider);
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  window_set_fullscreen(s_main_window, true);
  window_set_background_color(s_main_window, GColorBlack);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());   
  window_stack_push(s_main_window, true);  
  update_time();  
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {  
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
