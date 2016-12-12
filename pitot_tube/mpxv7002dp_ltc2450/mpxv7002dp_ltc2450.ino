//mpxv7002dp_ltc2450.ino

/*
 * LTC2450
 * 16bit ΔΣADC
 * SPI
 * 
 * 秋月の資料を参考
 */
#include <SPI.h>

byte m_data;
byte l_data;

const int CS=10;

const int OFFSET=34100;//[LSB]
const int SEN=1;//[V/Pa]
const double RHO=1.205;//[kg/m^3]

void setup() {
  // put your setup code here, to run once:
  pinMode(CS, OUTPUT);

  Serial.begin(9600);
  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(CS, LOW);
  m_data=SPI.transfer(0x00);
  l_data=SPI.transfer(0x00);
  digitalWrite(CS, HIGH);

  unsigned int val = (m_data << 8)|l_data;
  
  double v= sqrt(abs(2*((int)val-OFFSET)/SEN/RHO));

  Serial.print(val);
  Serial.print(",");
  Serial.println(v);
  
  delay(100);
}