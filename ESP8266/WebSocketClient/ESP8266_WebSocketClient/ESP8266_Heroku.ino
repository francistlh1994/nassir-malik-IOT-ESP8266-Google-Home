/*
 *Netmedias
 *
 *  Created on: 24.05.2015
 *  
 */
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>
#include <Hash.h>


// @@@@@@@@@@@@@@@ You only need to midify modify wi-fi and domain info @@@@@@@@@@@@@@@@@@@@
const char* ssid     = "enter your ssid name"; //enter your ssid/ wi-fi(case sensitiv) router name - 2.4 Ghz only
const char* password = "enter ssid password";     // enter ssid password (case sensitiv)
char host[] = "jdsdes.herokuapp.com/"; //enter your Heroku domain name like "espiot.herokuapp.com" 
// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

int port = 80;
char path[] = "/ws"; 
ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
const int Relay1 = 5;
const int Relay2 = 4;
const int Relay3 = 0;
const int Relay4 = 2;
const int Relay5 = 14;
const int Relay6 = 12;
const int Relay7 = 13;
const int Relay8 = 15;
DynamicJsonBuffer jsonBuffer;
String currState;
int pingCount=0;
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) { //uint8_t *


    switch(type) {
        case WStype_DISCONNECTED:
           Serial.println("Disconnected! ");
           Serial.println("Connecting...");
               webSocket.begin(host, port, path);
               webSocket.onEvent(webSocketEvent);
            break;
            
        case WStype_CONNECTED:
            {
             Serial.println("Connected! ");
          // send message to server when Connected
            webSocket.sendTXT("Connected");
            }
            break;
            
        case WStype_TEXT:
            Serial.println("Got data");
              //data = (char*)payload;
           processWebScoketRequest((char*)payload);
            break;
            
        case WStype_BIN:

            hexdump(payload, length);
            Serial.print("Got bin");
            // send data to server
            webSocket.sendBIN(payload, length);
            break;
    }

}

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    
    pinMode(Relay1, OUTPUT);
    pinMode(Relay2, OUTPUT);
    pinMode(Relay3, OUTPUT);
    pinMode(Relay4, OUTPUT);
    pinMode(Relay5, OUTPUT);
    pinMode(Relay6, OUTPUT);
    pinMode(Relay7, OUTPUT);
    pinMode(Relay8, OUTPUT);
    
      for(uint8_t t = 4; t > 0; t--) {
          delay(1000);
      }
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    
    //Serial.println(ssid);
    WiFiMulti.addAP(ssid, password);

    //WiFi.disconnect();
    while(WiFiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
        delay(100);
    }
    Serial.println("Connected to wi-fi");
    webSocket.begin(host, port, path);
    webSocket.onEvent(webSocketEvent);

}

void loop() {
    webSocket.loop();
  //If you make change to delay mak sure adjust the ping
    delay(2000);
  // make sure after every 40 seconds send a ping to Heroku
  //so it does not terminate the websocket connection
  //This is to keep the conncetion alive between ESP and Heroku
  if (pingCount > 20) {
    pingCount = 0;
    webSocket.sendTXT("\"heartbeat\":\"keepalive\"");
  }
  else {
    pingCount += 1;
  }
}

void processWebScoketRequest(String data){

            JsonObject& root = jsonBuffer.parseObject(data);
            String device = (const char*)root["device"];
            String location = (const char*)root["location"];
            String state = (const char*)root["state"];
            String query = (const char*)root["query"];
            String number = (const char*)root["number"]
            String message="";

            Serial.println(data);
            if(query == "cmd"){ //if query check state
              Serial.println("Recieved command!");
                    if(state=="on"){
                      digitalWrite(Relay1, HIGH);
                      message = "{\"state\":\"ON\"\"number\":\"ONE\"}";
                      currState = "ON";
                    }else{
                      digitalWrite(Relay1, LOW);
                      message = "{\"state\":\"OFF\"\"number\":\"ONE\"}";
                      currState = "OFF";
                    }
                  
            }else if(query == "?"){ //if command then execute   
              Serial.println("Recieved query!");
              int state = digitalRead(Relay1);
                 if(currState=="ON"){
                      message = "{\"state\":\"ON\"\"number\":\"ONE\"}";
                    }else{
                      message = "{\"state\":\"OFF\"\"number\":\"ONE\"}";
                    }
            }else{//can not recognized the command
              Serial.println("Command is not recognized!");
            }
            Serial.print("Sending response back");
            Serial.println(message);
                  // send message to server
                  webSocket.sendTXT(message);
                  if(query == "cmd" || query == "?"){webSocket.sendTXT(message);}
}
if(query == "cmd"){ //if query check state
              Serial.println("Recieved command!");
                    if(state=="on"){
                      digitalWrite(Relay2, HIGH);
                      message = "{\"state\":\"ON\"\"number\":\"TWO\"}";
                      currState = "ON";
                    }else{
                      digitalWrite(Relay2, LOW);
                      message = "{\"state\":\"OFF\"\"number\":\"TWO\"}";
                      currState = "OFF";
                    }
                  
            }else if(query == "?"){ //if command then execute   
              Serial.println("Recieved query!");
              int state = digitalRead(Relay2);
                 if(currState=="ON"){
                      message = "{\"state\":\"ON\"\"number\":\"TWO\"}";
                    }else{
                      message = "{\"state\":\"OFF\"\"number\":\"TWO\"}";
                    }
            }else{//can not recognized the command
              Serial.println("Command is not recognized!");
            }
            Serial.print("Sending response back");
            Serial.println(message);
                  // send message to server
                  webSocket.sendTXT(message);
                  if(query == "cmd" || query == "?"){webSocket.sendTXT(message);}
}
if(query == "cmd"){ //if query check state
              Serial.println("Recieved command!");
                    if(state=="on"){
                      digitalWrite(Relay3, HIGH);
                      message = "{\"state\":\"ON\"\"number\":\"THREE\"}";
                      currState = "ON";
                    }else{
                      
                      digitalWrite(Relay3, LOW);
                      message = "{\"state\":\"OFF\"\"number\":\"THREE\"}";
                      currState = "OFF";
                    }
                  
            }else if(query == "?"){ //if command then execute   
              Serial.println("Recieved query!");
              int state = digitalRead(Relay3);
                 if(currState=="ON"){
                      message = "{\"state\":\"ON\"\"number\":\"THREE\"}";
                    }else{
                      message = "{\"state\":\"OFF\"\"number\":\"THREE\"}";
                    }
            }else{//can not recognized the command
              Serial.println("Command is not recognized!");
            }
            Serial.print("Sending response back");
            Serial.println(message);
                  // send message to server
                  webSocket.sendTXT(message);
                  if(query == "cmd" || query == "?"){webSocket.sendTXT(message);}
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
