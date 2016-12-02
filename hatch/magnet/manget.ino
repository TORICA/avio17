//manget.ino
/*
ホール素子HG-166Aの信号をアナログピンに直接接続
部室にある秋月のダイナミックスピーカを近づけてみたが1~3　LSBほどしか変化がなかった。
また、極性も区別できない。
*/

const int SEN=0;

int val=0;

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
	val=analogRead(SEN);
	Serial.println(val);
}