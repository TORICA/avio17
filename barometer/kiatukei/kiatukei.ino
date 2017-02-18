//LPS25H-SPI
#include <SPI.h>
 const int chipSelectPin = 7;

void setup() 
{
  pinMode(chipSelectPin, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  delay(5);
  Serial.println(readLPS25H(0x0F),HEX );//通信確認正常ならば0ｘBDを受信
  writeLPS25H( 0x20, 0xC4);//パワーオン、25Hzを設定
  writeLPS25H( 0x10, 0x03);
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

  Serial.println(X,2);
  //Serial.print(',');
  /*
  Serial.print(T,2);
  Serial.print(',');
  
  Serial.println(X,2);
  */
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
