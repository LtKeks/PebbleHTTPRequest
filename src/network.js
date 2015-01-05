 var xmlHttp = null;

/*KEY Werte:
1-up
2-long up
3-select
4-long select
5-down
6-long down
*/

Pebble.addEventListener("ready",
							function(e) {
							});



Pebble.addEventListener("appmessage",
							function(e) {
                
switch(e.payload.message) {
   case 1:
        xmlHttp = new XMLHttpRequest();
        xmlHttp.open( "GET", "http://192.168.178.31/?run=lichtan", false );
        xmlHttp.send( null );
        console.log('Case 1');
        break;
    case 2:
        xmlHttp = new XMLHttpRequest();
        xmlHttp.open( "GET", "http://192.168.178.31/?run=lichtaus", false );
        xmlHttp.send( null );
        console.log('Case 2');
        break;
    case 3:
        xmlHttp = new XMLHttpRequest();  
        xmlHttp.open( "GET", "http://192.168.178.31:8080/jsonrpc?request=%7B%22jsonrpc%22%3A+%222.0%22%2C+%22method%22%3A+%22Player.PlayPause%22%2C+%22params%22%3A+%7B+%22playerid%22%3A+1+%7D%2C+%22id%22%3A+1%7D", false );
        xmlHttp.send( null );
        console.log('Case 3');
        break;
    case 4:
        console.log('Case 4');
        break;
    case 5:
        xmlHttp = new XMLHttpRequest();
        xmlHttp.open( "GET", "http://192.168.178.31/?run=tvan", false );
        xmlHttp.send( null );
        console.log('Case 5');
        break;
    case 6:
        xmlHttp = new XMLHttpRequest();
        xmlHttp.open( "GET", "http://192.168.178.31/?run=tvaus", false );
        xmlHttp.send( null );
        console.log('Case 6');
        break;
    default:
        
} 
});