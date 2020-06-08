#include <SoftwareSerial.h>   // 引用程式庫
#include <LiquidCrystal.h>

// 定義連接藍牙模組的序列埠
SoftwareSerial BT(6, 7); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數
LiquidCrystal lcd(12, A0, 11, 10, 9, 8);

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");
  // 藍牙透傳模式的預設連線速率。
  BT.begin(9600);

  lcd.begin(16, 2);
}

bool LEDA = false;
bool LEDB = false;

void changeLED(int number){
  if(number == 1){
    digitalWrite(4, !LEDA ? HIGH : LOW);
    LEDA = !LEDA;
  }else{
    digitalWrite(5, !LEDB ? HIGH : LOW);
    LEDB = !LEDB;
  }
}

void loop() {
  if(digitalRead(2) == LOW){
    BT.print("0");
    Serial.println("Sending A");
    delay(500);
  }
  if(digitalRead(3) == LOW){
    BT.print("1");
    Serial.println("Sending B");
    delay(500);
  }
  if (Serial.available()){
    val = Serial.read();
    BT.print(val);
  }
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
    if (val == '0') {
      changeLED(1);
    } else if (val == '1') {
      changeLED(2);
    }
  }  
  lcd.clear();
  if(LEDA == false){
    lcd.print("LEDA         OFF");
  }else{
    lcd.print("LEDA          ON");
  }
  lcd.setCursor(0, 1);
  delay(5);
  if(LEDB == false){
    lcd.print("LEDB         OFF");
  }else{
    lcd.print("LEDB          ON");
  }
  delay(100);
}
