const int CK_PIN=8;  //Clock
const int LE_PIN=11;  //Latch Enable
const int DI_PIN=10;  //Data In
const int OE_PIN=9;  //Output Enable

void setup() {
  // put your setup code here, to run once:
  pinMode(CK_PIN, OUTPUT);
  pinMode(LE_PIN, OUTPUT);
  pinMode(DI_PIN, OUTPUT);
  pinMode(OE_PIN, OUTPUT);

  digitalWrite(CK_PIN, LOW);
  digitalWrite(LE_PIN, LOW);
  digitalWrite(DI_PIN, LOW);
  digitalWrite(OE_PIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte data0=0b11111111;
  byte data1=0b11111111;
  byte data2=0b11111111;
  byte data3=0b11111111;

  digitalWrite(LE_PIN, LOW);
  shiftOut(DI_PIN, CK_PIN, LSBFIRST, data0);
  shiftOut(DI_PIN, CK_PIN, LSBFIRST, data1);
  shiftOut(DI_PIN, CK_PIN, LSBFIRST, data2);
  shiftOut(DI_PIN, CK_PIN, LSBFIRST, data3);
  digitalWrite(LE_PIN, HIGH);

  delay(10
  );
}
