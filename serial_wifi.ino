
#include <ESP8266WiFi.h>
//#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <FS.h>   // Include the SPIFFS library

String ssid;
String password;

ESP8266WebServer server(80);
File fsUploadFile; 

void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);

}

void serial() {

  String text= "<!DOCTYPE html><html><head>";
  text +="<meta name='viewport' content='width=device-width, initial-scale=1.0'></head><body>";
  text +="<p>Until cnc finished moving you can not make another commands\n"; 
  text +="If cnc finished moving you can make this commands:</p>";
  text +="<p><h1><a href='/xplus'>X+ </a>";
  text +="<a href='/xminus'>X- </a>";
  text +="<a href='/yplus'>Y+ </a>";
  text +="<a href='/yminus'>Y- </a></h1></p>";
  text +="<p><a href='index.html'>index</a></p>";
  text +="</body></html>";
  server.send(200, "text/html", text);
  //set_position(0.0, 10.0, 0.0);
  //String message="G01 X0 Y0\n";
  //process_string(message,message.length());
  //set_position(0.0, 0.0, 0.0);
  //disable_steppers();
}


void setup() {

  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  SPIFFS.begin(); 
//  ssid=LoadDataFromFile("ssid.txt");
//password=LoadDataFromFile("password.txt");

ESP.eraseConfig();
WiFi.disconnect(true);
WiFi.mode(WIFI_AP);
WiFi.softAP("Costycnc1");
  //Serial.printf("Try connecting to %s ", ssid1);
  WiFi.begin(ssid, password);
  int attempt=0;
  while ((WiFi.status() != WL_CONNECTED) && attempt<10)//try 10 times to connect to router 
    // if not succeed ... connect locally
  {
    attempt ++;
    delay(500);
    Serial.print(attempt);

  }
  if(attempt < 10){
  Serial.println(" connected to router and local");}
    else{
      Serial.println(" connected only local");
}
     server.begin();
  Serial.println("TCP server started");
  server.on("/serial",serial);
 server.onNotFound(handleNotFound);

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop() {
  // put your main code here, to run repeatedly:

}
