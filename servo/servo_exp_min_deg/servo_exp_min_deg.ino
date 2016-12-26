//servo_exp_min_deg.ino
//サーボ最小動作角度検証用
//最小角度の振動を繰り返す。KONDOのサーボをICS規格で動かす
//受信を切り捨てて通信速度を上げた
//ID設定

#include <Wire.h>
#include <string.h>

#undef int
#include <stdio.h>

uint8_t outbuf[6];    // array to store arduino output

const byte ICS_POS_CMD = 0x80;
const byte ICS_PARA_WRITE_COMMND = 0xC0;
const byte SUB_ST_COMMND = 0x01;
const byte SUB_SP_COMMND = 0x02;
const byte ICS_ID_CMD = 0xE0;
const byte SUB_ID_COMMND = 0x01;

void servoMove(int x, int y){ 
  /*
   * 3500...7500...11500
   * -135...0...   135    [deg]
   */
  int A, B;
  A = map(x,36,232,3500,11500);
  B = map(y,31,224,3500,11500);

  ics_set_pos(1,A);
  ics_set_pos(0,B);
}

///
/// 送受信する
///
bool Synchronize(byte *txBuff, size_t txLength, byte *rxBuff, size_t rxLength){
  int size; //受信したbyte数

  //定義していなかったらエラーにする
  if (Serial == false)return false;

  Serial.flush();

  Serial.write(txBuff, txLength);

  Serial.flush();   //送信が終わるのを待つ

  /*
  size = Serial.readBytes(rxBuff, rxLength);

  if (size != rxLength) //指定した受信数かどうか確認
  {
    return false;
  }
  */
  
  return true;
}

///
/// ポジションコマンドを送る
///
int ics_set_pos(byte id,unsigned short pos){
  byte tx_data[3];
  byte rx_data[3];
  bool flag;
  int rAngle;   //受信した角度データ
  /// 送信コマンドを作成
  tx_data[0] = ICS_POS_CMD + id;
  tx_data[1] = (byte)((pos & 0x3F80) >> 7);
  tx_data[2] = (byte)(pos & 0x007F);

  //送受信を行う
  flag = Synchronize(tx_data,3,rx_data,3);

  if(flag == false) //失敗した場合は-1を返す
  {
    return -1;
  }

  rAngle = ((rx_data[1] << 7) & 0x3F80) + (rx_data[2] & 0x007F);

  return rAngle;  
}

///
/// ストレッチを変更する
///
bool ics_set_st(byte id,byte stData){
  byte tx_data[3];
  byte rx_data[3];
  bool flag;
  /// 送信コマンドを作成
  tx_data[0] = ICS_PARA_WRITE_COMMND + id;
  tx_data[1] = SUB_ST_COMMND;
  tx_data[2] = stData;

  //送受信を行う
  flag = Synchronize(tx_data,3,rx_data,3);

  if(flag == false) //失敗した場合は-1を返す
  {
    return -1;
  }

  return flag;  
}

///
/// スピードを変更する
///
bool ics_set_sp(byte id,byte spData){
  byte tx_data[3];
  byte rx_data[3];
  bool flag;
  /// 送信コマンドを作成
  tx_data[0] = ICS_PARA_WRITE_COMMND + id;
  tx_data[1] = SUB_SP_COMMND;
  tx_data[2] = spData;

  //送受信を行う
  flag = Synchronize(tx_data,3,rx_data,3);

  if(flag == false) //失敗した場合は-1を返す
  {
    return -1;
  }  
  return flag;  
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
  //シリアルモードに切り替える
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  delay(1000);
  
  Serial.begin(115200, SERIAL_8E1);  //UARTの通信設定

  ics_set_id(0);
  delay(200);

  ics_set_sp(0,30);

  Serial.print ("Finished setup\n");
}

void loop (){ 
  //サーボ制御
  //ics_set_id(0x01);
  //delay(200);
  //idを変えるときは設定後にディレイを入れるとうまくいく
  //servoMove(outbuf[0], outbuf[1]);
  //delay(200);
  ics_set_pos(0, 7500);
  delay(1000);
  ics_set_pos(0, 7501);
  delay(1000);
   
}
