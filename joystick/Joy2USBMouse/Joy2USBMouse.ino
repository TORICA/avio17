//Joy2USBMouse.ino
const int JS_X_PIN=A1;
const int JS_Y_PIN=A0;

//反応しない領域（アソビ）の設定
const int JS_DEADZONE_X=120;
const int JS_DEADZONE_Y=120;

int JS_originX=512;
int JS_originY=512;

void setup() {
  // put your setup code here, to run once:

  //JSのニュートラル位置を設定する
  delay(100);
  JS_originX=analogRead(JS_X_PIN);
  JS_originY=analogRead(JS_Y_PIN);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //JSのニュートラル位置との差をreadingX,Yに格納
  int readingX=analogRead(JS_X_PIN)-JS_originX;
  int readingY=analogRead(JS_Y_PIN)-JS_originY;

  //各軸の出力がアソビの範囲なら0に置き換える
  if(-JS_DEADZONE_X<=readingX && readingX<=JS_DEADZONE_X){
  	readingX=0;
  }
  if(-JS_DEADZONE_Y<=readingY && readingY<=JS_DEADZONE_Y){
  	readingY=0;
  }

  //アソビ領域の辺を0とする対応に置き換える
  if(readingX>0){
  	readingX=readingX-JS_DEADZONE_X;
  }else if(readingX<0){
  	readingX=readingX+JS_DEADZONE_X;
  }
  if(readingY>0){
  	readingY=readingY-JS_DEADZONE_Y;
  }else if(readingY<0){
  	readingY=readingY+JS_DEADZONE_Y;
  }

  //出力
  /*
  Serial.print(readingX);
  Serial.print(',');
  Serial.print(readingY);
  Serial.print(',');
  */
  Serial.print(calcOutput(readingX,0));
  Serial.print(',');
  Serial.println(calcOutput(readingY,1));

  delay(20);
}

/**
*	X ->	axis=0
*	Y ->	axis=1
*/
int calcOutput(int reading, int axis){
	int JS_DEADZONE=100;
	if(axis==0){
		JS_DEADZONE=JS_DEADZONE_X;
	}else{
		JS_DEADZONE=JS_DEADZONE_Y;
	}
	double x=3.14/(2*(512-JS_DEADZONE))*reading;
	return (int)(reading*(1.0-cos(x)));
}