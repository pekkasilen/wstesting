#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
WebSocketsClient ws;

String ssid = "vihreathaisee";
String pwd = "SalainenSana1";

String msgToSend = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Connecting to wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pwd);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected as ");
  Serial.println(WiFi.localIP());
  ws.begin("10.15.10.132",8080,"/");
  ws.onEvent(webSocketEvent);
}

void loop() {
  ws.loop();
  while(Serial.available()>0){
    char c = Serial.read();
    if(c=='\n'){
      ws.sendTXT(msgToSend);
      msgToSend = "";
    } else{
      msgToSend += c;
    }
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  if(type==WStype_CONNECTED){
    ws.sendTXT("Tultii sisään, moro vaa");
  }
  if(type==WStype_TEXT){
    Serial.printf("Socket got: %s\n",payload);
  }
  if(type==WStype_BIN) {
    hexdump(payload,length);
  }
}
