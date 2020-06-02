#include <VirtualWire.h>

const char *data1="A";
const char *data2="B";
const char *data3="C";
const char *data4="D";
bool a_or_b = true;
bool c_or_d = true;
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen=VW_MAX_MESSAGE_LEN;

void setup() {
  Serial.begin(9600);
  vw_set_ptt_inverted(true);
  vw_setup(300);
  vw_set_tx_pin(8);
  vw_set_tx_pin(8);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  digitalWrite(6, LOW);
  digitalWrite(12, LOW);
  if(digitalRead(2) == LOW){
    if(a_or_b == true){
      vw_send((uint8_t *)data1, strlen(data1));
      Serial.println("Sending A.");
    }else{
      vw_send((uint8_t *)data3, strlen(data3));
      Serial.println("Sending C.");
    }
    a_or_b = !a_or_b;
    vw_wait_tx();
    delay(200);
  }else if(digitalRead(3) == LOW){
    if(c_or_d == true){
      vw_send((uint8_t *)data2, strlen(data2));
      Serial.println("Sending B.");
    }else{
      vw_send((uint8_t *)data4, strlen(data4));
      Serial.println("Sending D.");
    }
    c_or_d = !c_or_d;
    vw_wait_tx();
    delay(200);
  }
  if (vw_get_message(buf, &buflen)) {
    Serial.println(buf[0]);
    if (buf[0]=='A') {
      Serial.println("Receive 'A'");
      digitalWrite(5, HIGH);
    }
    if(buf[0]=='B') {
      Serial.println("Receive 'B'");
      digitalWrite(11, HIGH);
    }
    if (buf[0]=='C') {
      Serial.println("Receive 'C'");
      digitalWrite(5, LOW);
    }
    if (buf[0]=='D') {
      Serial.println("Receive 'D'");
      digitalWrite(11, LOW);  //狀態為 ON 就點亮 LED
    }
  }
} 
