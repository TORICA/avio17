#include <SPI.h>
#include <SD.h>

const int CK_PIN=8;  //Clock
const int LE_PIN=11;  //Latch Enable
const int DI_PIN=10;  //Data In
const int OE_PIN=9;  //Output Enable

unsigned long t0h=0;

void setup() {
  //UART
  Serial.begin(9600);   //USB
  Serial1.begin(9600);  //pitot
  Serial3.begin(9600);  //CTRL

  //SDC
  SD.begin();
   
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

  delay(100);
}

void loop() {
  unsigned long ct=millis();  //起動時間の取得
  
  /* 高度計　開始 */
  float hight;
  hight=analogRead(0)*2*0.01; //xの単位を[m]に変換
  updateDisplay(hight);
  /* 高度計　終了 */

  //Serial.println(millis()-ct);

  /* 高度ログ書き込み 開始*/
  if(millis()-t0h>200){
    File file = SD.open("hight.csv", FILE_WRITE);
    file.print(hight);
    file.print(',');
    file.println(ct);
    file.close();
    t0h=millis();
  }

  /* 高度ログ書き込み 終了*/

  //Serial.println(millis()-ct);

  /* ピトー管ログ書き込み 開始*/
  int s1a=Serial1.available();
  if (s1a > 0) {
    File file = SD.open("pitot.csv", FILE_WRITE);   

    while(s1a>0){
      int s1=Serial1.read();

      /* 改行コード(0x0D 0x0A)の直前に起動時間を挿入 */
      if(s1==0x0D){
        file.print(',');
        file.print(ct);
      }

      file.write(s1);
      Serial.write(s1);
      
      s1a--;
    }

    
    file.close();
  }
  /* ピトー管ログ書き込み 終了*/

  //Serial.println(millis()-ct);

  /* 操舵系ログ書き込み 開始*/
  int s3a=Serial3.available();
  if (s3a > 0) {
    File file = SD.open("ctrl.csv", FILE_WRITE);

    while(s3a>0){
      int s3=Serial3.read();
    
      /* 改行コードの直前に起動時間を挿入 */
      if(s3==0x0D){
        file.print(',');
        file.print(ct);
      }

      file.write(s3);
      //Serial.write(s3);

      s3a--;
   }
    
    file.close();
  }
  /* 操舵系ログ書き込み 終了*/

  //Serial.println(millis()-ct);
}

void updateDisplay(float hight){
  unsigned long data=0;
  
  if(hight<0.5)                       data=0b00000000000000000000000001000000;
  else if(hight>=0.5 && hight<1.0)    data=0b00000000000000000000000011000000;
  else if(hight>=1.0 && hight<1.5)    data=0b00000000000000000000000111000000; 
  else if(hight>=1.5 && hight<2.0)    data=0b00000000000000000000001111000000;   
  else if(hight>=2.0 && hight<2.5)    data=0b00000000000000000000011111000000;  
  else if(hight>=2.5 && hight<3.0)    data=0b00000000000000000000111111000000;
  else if(hight>=3.0 && hight<3.5)    data=0b00000000000000000001111111000000;
  else if(hight>=3.5 && hight<4.0)    data=0b00000000000000000011111111000000;
  else if(hight>=4.0 && hight<4.5)    data=0b10000000000000000011111111000000;
  else if(hight>=4.5 && hight<5.0)    data=0b11000000000000000011111111000000;
  else if(hight>=5.0 && hight<5.5)    data=0b11100000000000000011111111000000;
  else if(hight>=5.5 && hight<6.0)    data=0b11110000000000000011111111000000;
  else if(hight>=6.0 && hight<6.5)    data=0b11111000000000000011111111000000;
  else if(hight>=6.5 && hight<7.0)    data=0b11111100000000000011111111000000;
  else if(hight>=7.0 && hight<7.5)    data=0b11111110000000000011111111000000;
  else if(hight>=7.5 && hight<8.0)    data=0b11111111000000000011111111000000;
  else if(hight>=8.0 && hight<8.5)    data=0b11111111100000000011111111000000;
  else if(hight>=8.5 && hight<9.0)    data=0b11111111110000000011111111000000;
  else if(hight>=9.0 && hight<9.5)    data=0b11111111111000000011111111000000;
  else if(hight>=9.5 && hight<10.0)   data=0b11111111111100000011111111000000;
  else if(hight>=10.0)                data=0b11111111111110000011111111000000;
   
  shiftOutHV9408(DI_PIN, CK_PIN, LE_PIN, data);
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

