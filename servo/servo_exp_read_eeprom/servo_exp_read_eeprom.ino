//servo_exp_min_deg.ino
//サーボ最小動作角度検証用
//最小角度の振動を繰り返す。KONDOのサーボをICS規格で動かす

//ID設定

//トライステートバッファを使った半二重通信
//arduinoMEGA用

#include <Wire.h>
#include <string.h>

#undef int
#include <stdio.h>

uint8_t outbuf[6];    // array to store arduino output

const byte ICS_POS_CMD = 0x80;
const byte ICS_PARA_READ_COMMND = 0xA0;
const byte ICS_PARA_WRITE_COMMND = 0xC0;
const byte SUB_EEPROM_COMMND = 0x00;
const byte SUB_ST_COMMND = 0x01;
const byte SUB_SP_COMMND = 0x02;
const byte SUB_TMP_COMMND = 0x04;
const byte ICS_ID_CMD = 0xE0;
const byte SUB_ID_COMMND = 0x01;

unsigned short sv_pos=7500;
boolean pushFlg=false;
boolean pushIgn=false;
unsigned long t_push=0;

const int EN_RX=2;
const int EN_TX=3;

///
/// 送受信する
///

bool Synchronize(byte *txBuff, size_t txLength, byte *rxBuff, size_t rxLength){
  byte buff0[32];
  byte buff1[32];

  //定義していなかったらエラーにする
  if (Serial1 == false)return false;

  Serial1.flush();

  enTX();
  Serial1.write(txBuff, txLength);

  Serial1.flush();   //送信が終わるのを待つ

  enRX();
  Serial1.readBytes(rxBuff, rxLength);
  
  
  Serial1.readBytes(rxBuff, 2);
  Serial1.readBytes(buff0, 32);
  Serial1.readBytes(buff1, 32);

  for(int i=0;i<64;i++){
    rxBuff[i]=i<32?buff0[i]:buff1[i];
  }
  
  
  return true;
}

/*
bool Synchronize(byte *txBuff, size_t txLength, byte *rxBuff, size_t rxLength){
  int size; //受信したbyte数

  //定義していなかったらエラーにする
  if (Serial1 == false)return false;

  Serial1.flush();

  enTX();
  Serial1.write(txBuff, txLength);

  Serial1.flush();   //送信が終わるのを待つ

  enRX();
  size = Serial1.readBytes(rxBuff, rxLength);

  if (size != rxLength) //指定した受信数かどうか確認
  {
    return false;
  }
  
  
  return true;
}
*/
///
/// EEPROMを取得する
///
byte ics_get_eeprom(byte id,byte *eeprom){
  byte tx_data[2];
  byte rx_data[66];
  bool flag;

  /// 送信コマンドを作成
  tx_data[0] = ICS_PARA_READ_COMMND + id;
  tx_data[1] = SUB_EEPROM_COMMND;

  //送受信を行う
  flag = Synchronize(tx_data,2,eeprom,66);

  if(flag == false) //失敗した場合は-1を返す
  {
    return -1;
  }

  return eeprom;  
}

//トライステートバッファ制御
void enTX(){
  digitalWrite(EN_RX,HIGH);
  digitalWrite(EN_TX,LOW);
}
void enRX(){
  digitalWrite(EN_TX,HIGH);
  digitalWrite(EN_RX,LOW);
}

///
/// IDを変更する
///
void ics_set_id(byte id){
  byte tx_data[3];
  byte rx_data[1];
  bool flag;
  int rId;   //受信した角度データ
  /// 送信コマンドを作成
  tx_data[0] = ICS_ID_CMD + id;
  tx_data[1] = SUB_ID_COMMND; //ID書き込み
  tx_data[2] = SUB_ID_COMMND; //ID書き込み
  tx_data[3] = SUB_ID_COMMND; //ID書き込み

  //送受信を行う
  flag = Synchronize(tx_data,4,rx_data,1);
}

void setup (){
  //トライステートバッファ制御用ピン
  pinMode(EN_RX,OUTPUT);
  pinMode(EN_TX,OUTPUT);
  
  //シリアルモードに切り替える
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  delay(1000);

  Serial.begin(9600);
  
  Serial1.begin(115200, SERIAL_8E1);  //UARTの通信設定

  enRX();

  Serial.print ("Finished setup\n");
}

void loop (){
  byte eeprom[66];

  //ics_set_id(0);
  //delay(500);
  
  ics_get_eeprom(0,eeprom);
  for(int i=0;i<66;i++){
    Serial.print(i<2?-1:i-1,DEC);
    Serial.print(":");
    Serial.println(eeprom[i],HEX);
  }
  delay(10000);
}
