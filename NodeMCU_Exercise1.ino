#include<ESP8266WiFi.h>

const char* ssid = "Uriah";
const char* password = "han910625";
String header = "";
int a = 0, b = 0;

const int output5 = 14;
const int output4 = 12;

WiFiServer server(80);

void setup() {
	Serial.begin(115200);
	pinMode(14, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(4, INPUT_PULLUP);
	pinMode(0, INPUT_PULLUP);
	WiFiSetting();
}

void WiFiSetting(){
	WiFi.begin(ssid, password);
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

void loop(){
	WiFiClient client = server.available();
	if(digitalRead(4) == LOW){
		Serial.println("Receive A");
		a++;
		delay(1000);
	}
  	if(digitalRead(0) == LOW){
    	Serial.println("Receive B");
    	b++;
		delay(1000);
	}
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
						if (header.indexOf("GET /14/on") >= 0){
							Serial.println("GPIO 14 on");
							digitalWrite(output5, HIGH);
						} else if (header.indexOf("GET /14/off") >= 0){
							Serial.println("GPIO 14 off");
							digitalWrite(output5, LOW);
						} else if (header.indexOf("GET /12/on") >= 0){
							Serial.println("GPIO 12 on");
							digitalWrite(output4, HIGH);
						} else if (header.indexOf("GET /12/off") >= 0){
							Serial.println("GPIO 12 off");
							digitalWrite(output4, LOW);
						}
						char buffer[100];
						sprintf(buffer, "A已經接收了%d次，B已經接收了%d次", a, b);
						client.println(buffer);
						break;
					} else {
						currentLine = "";
					}
				} else if (c != '\r') {
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
