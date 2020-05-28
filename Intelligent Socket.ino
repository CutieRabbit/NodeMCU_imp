#include<ESP8266WiFi.h>

const char* ssid = "Uriah";
const char* password = "han910625";

IPAddress ip(192,168,43,77);   
IPAddress gateway(192,168,43,254);   
IPAddress subnet(255,255,255,0);
  
String header = "";

const int output = 15;

WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    pinMode(output, OUTPUT);
    WiFiSetting();
}

void WiFiSetting(){
    WiFi.begin(ssid, password);
    WiFi.config(ip, gateway, subnet);
    while(WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    Serial.println("Wi-Fi Connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void doingConnect(){
  
}

void loop(){
    WiFiClient client = server.available(); 
    if (client) {                            
      Serial.println("New Client.");
      String currentLine = "";
      while (client.connected()) {
          if (client.available()) {
              char c = client.read();
              Serial.write(c);
              header += c;
              if (c == '\n') {
                  if (currentLine.length() == 0) {
                      client.println("HTTP/1.1 200 OK");
                      client.println("Content-type:text/html");
                      client.println("Connection: close");
                      client.println();
                      if (header.indexOf("GET /15/on") >= 0){
                          Serial.println("GPIO 15 on");
                          digitalWrite(output, LOW);
                          client.println("插頭已開啟");
                      }else if(header.indexOf("GET /15/off") >= 0){
                          Serial.println("GPIO 15 off");
                          digitalWrite(output, HIGH);
                          client.println("插頭已關閉");
                      } 
                      break;
                  }else{
                      currentLine = "";
                  }
              }else if(c != '\r'){ 
                  currentLine += c;
              }
          }
      }
      header = "";
      client.stop();
      Serial.println("Client disconnected.");
      Serial.println("");
    }
}
