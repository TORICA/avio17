//LPS25H-SPI
#include <SPI.h>
#include <SD.h>
const int chipSelectPin = 7;
const int chipSelect = 4;
void setup() 
{
  pinMode(chipSelectPin, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  delay(5);
  Serial.println(readLPS25H(0x0F),HEX );//通信確認正常ならば0ｘBDを受信
  writeLPS25H( 0x20, 0xC4);//パワーオン、25Hzを設定
  writeLPS25H( 0x10, 0x03);


    // シリアルポート初期化
  while (!Serial) {
    ; // USBケーブルが接続されるのを待つ。この待ちループは Leonardo のみ必要。
  }

  Serial.print(F("Initializing SD card..."));

  // SSピン（Unoは10番、Megaは53番）は使わない場合でも出力にする必要があります。
  // そうしないと、SPIがスレーブモードに移行し、SDライブラリが動作しなくなります。
  pinMode(SS, OUTPUT);

  // SDライブラリを初期化
  if (!SD.begin(chipSelect)) {
    Serial.println(F("Card failed, or not present"));
    // 失敗、何もしない
    while(1);
  }
  Serial.println(F("ok."));

  // 日付と時刻を返す関数を登録
  SdFile::dateTimeCallback( &dateTime );
}

void loop()
{
  int i;
  long data[5];
  float P,T,X,a;

  for(i=0;i<5;i++)
  {
    data[i]=readLPS25H(0x28+i);
  }
  P=( float)(data[2]*256*256+data[1]*256+data[0])/4096.0;

  if(data[4]>=128)
  {
    T=42.5-( float)(65536-(data[4]*256+data[3]))/480.0;
  }
  else
  {
    T=42.5+( float)(data[4]*256+data[3])/480.0;
  }
  T=T-5;
 T=15;
  a=pow(1013.25/P,1/5.257);
  X=(a-1.0)*(T+273.15)/0.0065+35;

  /*
  Serial.print("Pressure(hPa)=");
  Serial.print(P,2);
  Serial.print("\t");
  Serial.print("Temperature(C)=");
  Serial.print(T,2);
  Serial.print("\t");
  Serial.print("Elevation(m)=");
  Serial.println(X,2);
  */

  //Serial.println(X,2);
  //Serial.print(',');
  /*
  Serial.print(T,2);
  Serial.print(',');
  
  Serial.println(X,2);
  */




  // ファイルを開く
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // もしファイルが開けたら値を書き込む
  if (dataFile) {
    int value = analogRead(0);
    dataFile.print(P);
    dataFile.print(",");
    dataFile.println(X);
    dataFile.close();
    // シリアルポートにも出力
    Serial.print(P);
    Serial.print(",");
    Serial.println(X);
  }
  // ファイルが開けなかったらエラーを出力
  else {
    Serial.println(F("error opening datalog.txt"));
  } 

  // 一秒待つ
  delay(40);
  
}

byte readLPS25H( byte Register ) 
{
  byte rdata = 0x00;

   digitalWrite(chipSelectPin, LOW);
  SPI.transfer(0x80 | Register);
  rdata=SPI.transfer(0x00);
  digitalWrite(chipSelectPin, HIGH);
  return rdata;
}

void writeLPS25H(byte Register, byte Value)
{
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(0x7F & Register);
  SPI.transfer(Value);
  digitalWrite(chipSelectPin, HIGH);
}

void dateTime(uint16_t* date, uint16_t* time)
{
  uint16_t year = 2013;
  uint8_t month = 2, day = 3, hour = 9, minute = 0, second = 0;

  // GPSやRTCから日付と時間を取得
  // FAT_DATEマクロでフィールドを埋めて日付を返す
  *date = FAT_DATE(year, month, day);

  // FAT_TIMEマクロでフィールドを埋めて時間を返す
  *time = FAT_TIME(hour, minute, second);
}




