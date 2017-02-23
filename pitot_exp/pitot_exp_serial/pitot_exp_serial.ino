byte incomingByte;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for(byte i=0;i<256;i++){
    Serial.write(i);
    delay(20);
  }

  /*
  if (Serial.available() > 0) { // 受信したデータが存在する
    incomingByte = Serial.read(); // 受信データを読み込む

    Serial.print("I received: "); // 受信データを送りかえす
    Serial.println(incomingByte, DEC);
  }
  */
}
