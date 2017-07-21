//KONDOのサーボをICS規格で動かす

//ID設定

//トライステートバッファを使った半二重通信
//arduinoMEGA用

//インバーターを使って二つのトライステートバッファを一本の線で制御する

//シリアル通信のタイムアウトを短く設定
//サーボの片方と通信できない場合に、もう片方が正常でも、受信待ちのために正常な方にもラグが発生してしまう為。

//JS中心付近のデッドゾーン
//JS辺縁のパディング

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

const int EN_RX_H=2;
const int EN_RX_V=3;

const int SV_H = 1;
const int SV_V = 2;

unsigned long t0=0;

  /* 調整用数値 */
  const int SV_V_L=8187;
  const int SV_V_N=7735;
  const int SV_V_R=7399;
  const int SV_H_U=7228;
  const int SV_H_N=7642;
  const int SV_H_D=8170;

  const int JS_V_L=874;
  const int JS_V_N=550;
  const int JS_V_R=230;
  const int JS_H_U=900;
  const int JS_H_N=550;
  const int JS_H_D=230;


void servoMove(int js_h_val, int js_v_val){

  
   // 3500...7500...11500
   // -135...0...   135    [deg]

    // js_h_val 230...550...900 (down..neutral..up)
    // js_v_val 195...550...800 (right..neutral..left)


    
    //sv_h -8...0...8[deg]  7263..7500..7737
    //sv_v -8...0...8[deg]  7263..7500..7737
  
  
  int sv_pos_H, sv_pos_V;

/*  
  sv_pos_H = map(js_h_val,230,900,8092,7114);
  //if(sv_pos_H>7500) sv_pos_H=7500;
  sv_pos_V = map(js_v_val,195,800,8427,9388);
  //sv_pos_V=6462;
*/


/* JSのDZ対策　開始12*/
    const int DZ = 100;

    const int PAD =100;
  
    if(js_h_val<=JS_H_N+DZ && js_h_val>=JS_H_N-DZ){
      sv_pos_H=SV_H_N;
    }else if(js_h_val>JS_H_N+DZ && js_h_val <= JS_H_U-PAD){
      sv_pos_H = map(js_h_val,JS_H_N+DZ,JS_H_U-PAD,SV_H_N,SV_H_U);
    }else if(js_h_val<JS_H_N-DZ && js_h_val >= JS_H_D+PAD){
      sv_pos_H = map(js_h_val,JS_H_D+PAD,JS_H_N-DZ,SV_H_D,SV_H_N);
    }else if(js_h_val>JS_H_U-PAD){
      sv_pos_H =SV_H_U; 
    }else if(js_h_val<JS_H_D+PAD){
      sv_pos_H =SV_H_D; 
    }
  
    if(js_v_val<=JS_V_N+DZ && js_v_val>=JS_V_N-DZ){
      sv_pos_V=SV_V_N;
    }else if(js_v_val>JS_V_N+DZ && js_v_val <= JS_V_L-PAD){
      sv_pos_V = map(js_v_val,JS_V_N+DZ,JS_V_L-PAD,SV_V_N,SV_V_L);
    }else if(js_v_val<JS_V_N-DZ && js_v_val >= JS_V_R+PAD){
      sv_pos_V = map(js_v_val,JS_V_R+PAD,JS_V_N-DZ,SV_V_R,SV_V_N);
    }else if(js_v_val>JS_V_L-PAD){
      sv_pos_V =SV_V_L; 
    }else if(js_v_val<JS_V_R+PAD){
      sv_pos_V =SV_V_R; 
    }
/* JSのDZ対策　終了 */   

  Serial.print(js_h_val);
  Serial.print(",");
  Serial.print(sv_pos_H);
  Serial.print(",");
  Serial.print(js_v_val);
  Serial.print(",");
  Serial.print(sv_pos_V);
  Serial.print(",");

/* 変換後の値をサーボに送信する */
  String sv_h_return, sv_v_return;
  sv_h_return=ics_set_pos(1,sv_pos_H,SV_H);
  sv_v_return=ics_set_pos(2,sv_pos_V,SV_V);
  Serial.print(sv_h_return);
  Serial.print(",");
  Serial.println(sv_v_return);

  
  if(millis()-t0>500){
//      Serial3.print(js_h_val);
//      Serial3.print(",");
      Serial3.print(sv_pos_H);
      Serial3.print(",");
//      Serial3.print(js_v_val);
//      Serial3.print(",");
      Serial3.print(sv_pos_V);
      Serial3.print(",");
      Serial3.print(sv_h_return);
      Serial3.print(",");
      Serial3.println(sv_v_return);

      t0=millis();
  }

}


/// 
/// 送受信する
///
bool Synchronize(byte *txBuff, size_t txLength, byte *rxBuff, size_t rxLength, int svSel){
  int size; //受信したbyte数

  if(svSel == SV_H){
    if (Serial1 == false) return false;
    enTX(svSel);
    Serial1.write(txBuff, txLength);
    Serial1.flush();   //送信が終わるのを待つ
    enRX(svSel);
    size = Serial1.readBytes(rxBuff, rxLength);
    Serial1.flush();
  }else if(svSel == SV_V){
    if (Serial2 == false) return false;
    enTX(svSel);
    Serial2.write(txBuff, txLength);
    Serial2.flush();   //送信が終わるのを待つ
    enRX(svSel);
    size = Serial2.readBytes(rxBuff, rxLength);
    Serial2.flush();
  }else{
    return false;
  }

  if (size != rxLength) return false; //指定した受信数かどうか確認
    
  return true;
}

///
/// ポジションコマンドを送る
///
int ics_set_pos(byte id,unsigned short pos,int svSel){
  byte tx_data[3];
  byte rx_data[3];
  bool flag;
  int rAngle;   //受信した角度データ
  /// 送信コマンドを作成
  tx_data[0] = ICS_POS_CMD + id;
  tx_data[1] = (byte)((pos & 0x3F80) >> 7);
  tx_data[2] = (byte)(pos & 0x007F);

  //送受信を行う
  flag = Synchronize(tx_data,3,rx_data,3,svSel);

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
bool ics_set_st(byte id,byte stData,int svSel){
  byte tx_data[3];
  byte rx_data[3];
  bool flag;
  /// 送信コマンドを作成
  tx_data[0] = ICS_PARA_WRITE_COMMND + id;
  tx_data[1] = SUB_ST_COMMND;
  tx_data[2] = stData;

  //送受信を行う
  flag = Synchronize(tx_data,3,rx_data,3,svSel);

  if(flag == false) //失敗した場合は-1を返す
  {
    return -1;
  }

  return flag;  
}

///
/// スピードを変更する
///
bool ics_set_sp(byte id,byte spData,int svSel){
  byte tx_data[3];
  byte rx_data[3];
  bool flag;
  /// 送信コマンドを作成
  tx_data[0] = ICS_PARA_WRITE_COMMND + id;
  tx_data[1] = SUB_SP_COMMND;
  tx_data[2] = spData;

  //送受信を行う
  flag = Synchronize(tx_data,3,rx_data,3,svSel);

  if(flag == false) //失敗した場合は-1を返す
  {
    return -1;
  }  
  return flag;  
}

///
/// IDを変更する
///
void ics_set_id(byte id,int svSel){
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
  flag = Synchronize(tx_data,4,rx_data,1,svSel);
}

///
/// 温度を取得する
///
int ics_get_tmp(byte id,int svSel){
  byte tx_data[2];
  byte rx_data[3];
  bool flag;
  int rTemp;   //受信した温度データ
  /// 送信コマンドを作成
  tx_data[0] = ICS_PARA_READ_COMMND + id;
  tx_data[1] = SUB_TMP_COMMND;

  //送受信を行う
  flag = Synchronize(tx_data,2,rx_data,3,svSel);

  if(flag == false) //失敗した場合は-1を返す
  {
    return -1;
  }

  //rx_data[2]=60 -> T=30℃
  //rx_data[2]=30 -> T=100℃
  //温度=(-7/3)rx_data[2]+170
  rTemp =  rx_data[2];
  //rTemp = (-7/3)*(double)rx_data[2]+170.0;

  return rTemp;  
}

//トライステートバッファ制御
void enTX(int svSel){
  if(svSel==SV_H)  digitalWrite(EN_RX_H,HIGH);
  if(svSel==SV_V)  digitalWrite(EN_RX_V,HIGH);
}
void enRX(int svSel){
  if(svSel==SV_H)  digitalWrite(EN_RX_H,LOW);
  if(svSel==SV_V)  digitalWrite(EN_RX_V,LOW);
}

void setup (){
  //トライステートバッファ制御用ピン
  pinMode(EN_RX_H,OUTPUT);
  pinMode(EN_RX_V,OUTPUT);

  //LOG
  Serial3.begin(9600);
  Serial.begin(9600);
  Serial.print ("Initializing...\n");
  Serial3.print ("Initializing...\n");

  //SV
  Serial1.begin(115200, SERIAL_8E1);  //UARTの通信設定
  Serial2.begin(115200, SERIAL_8E1);




  //タイムアウトの設定
  Serial.setTimeout(100);
  Serial1.setTimeout(100);
  Serial2.setTimeout(100);
  Serial3.setTimeout(100);

  delay(1000);
  ics_set_id(1,SV_H);
  ics_set_id(2,SV_V);
  delay(1000);
  ics_set_sp(2,127,SV_V);
  delay(1000);
  ics_set_st(2,127,SV_V);
  delay(1000);  

  Serial.print ("Finished setup\n");
  Serial3.print ("Finished setup\n");
}

void loop (){  
  //Serial.println(ics_set_pos(1,8092,SV_H));
  //Serial.println(ics_set_pos(2,6225,SV_V));
  //delay(500);
  //Serial.println(ics_set_pos(1,8092,SV_H));
  //Serial.println(ics_set_pos(2,6699,SV_V));
  //delay(500);
  
//  for(int i=0;i<=3;i++){
//    Serial.print(analogRead(i));
//    Serial.print(",");
//  }
  
 // Serial.println(ics_set_pos(1,0,SV_H));
//  Serial.print(",");
//  Serial.println(ics_set_pos(2,0,SV_V));

//Serial.println(ics_set_pos(1,SV_H_N,SV_H));
/*
  for(int i=0;i<=3;i++){
    Serial.print(analogRead(i));
    Serial.print(",");
  }
  Serial.print("\n");
  */
//
//  Serial.print(analogRead(1));
//  Serial.print(',');
//  Serial.println(analogRead(2));
  servoMove(analogRead(1),analogRead(2));
}
