const int CK_PIN=8;  //Clock
const int LE_PIN=11;  //Latch Enable
const int DI_PIN=10;  //Data In
const int OE_PIN=9;  //Output Enable

void setup() {
  /* HV9408用初期化処理　開始 */
  pinMode(CK_PIN, OUTPUT);
  pinMode(LE_PIN, OUTPUT);
  pinMode(DI_PIN, OUTPUT);
  pinMode(OE_PIN, OUTPUT);

  digitalWrite(CK_PIN, LOW);
  digitalWrite(LE_PIN, LOW);
  digitalWrite(DI_PIN, LOW);
  digitalWrite(OE_PIN, HIGH);
  /* HV9408用初期化処理　終了 */
}

void loop() {
  unsigned long data=0b00011101010101010101010101010101;

  shiftOutHV9408(DI_PIN, CK_PIN, LE_PIN, data);
  delay(1000);
}

/* dataの最下の桁がHV9408のHVOUT1に、最上の桁がHVOUT32に対応 */
void shiftOutHV9408(int DI_PIN, int CK_PIN, int LE_PIN, unsigned long data){
  digitalWrite(LE_PIN, LOW);
  shiftOut(DI_PIN, CK_PIN, MSBFIRST, (data >> 24));
  shiftOut(DI_PIN, CK_PIN, MSBFIRST, (data >> 16));
  shiftOut(DI_PIN, CK_PIN, MSBFIRST, (data >> 8));
  shiftOut(DI_PIN, CK_PIN, MSBFIRST, data);
  digitalWrite(LE_PIN, HIGH);
}

