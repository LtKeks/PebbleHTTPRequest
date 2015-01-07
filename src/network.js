Pebble.addEventListener("ready", function(e) {});

Pebble.addEventListener("appmessage", function(e) {

/*
Case:
1-up
2-long up
3-select
4-long select
5-down
6-long down
*/
  
  
 var xmlHttp = new XMLHttpRequest();
                
 switch(e.payload.message) {
   
    case 1:        
        xmlHttp.open( "GET", "http://192.168.178.31/?run=lichtan");
        break;
    case 2:        
        xmlHttp.open( "GET", "http://192.168.178.31/?run=lichtaus");
        break;
    case 3:          
        xmlHttp.open( "GET", "http://192.168.178.31:8080/jsonrpc?request=%7B%22jsonrpc%22%3A+%222.0%22%2C+%22method%22%3A+%22Player.PlayPause%22%2C+%22params%22%3A+%7B+%22playerid%22%3A+1+%7D%2C+%22id%22%3A+1%7D");
        break;
    case 4:        
        break;
    case 5:        
        xmlHttp.open( "GET", "http://192.168.178.31/?run=tvan");
        break;
    case 6:        
        xmlHttp.open( "GET", "http://192.168.178.31/?run=tvaus");
        break;
    default:
        console.log('Case Default / Error');        
      } 
  
 xmlHttp.send(null);
  
});