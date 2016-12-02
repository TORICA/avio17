/*
センサーの受光強度に合わせた音程をスピーカーから出力する

laser:LM-101-A 650nm
sensor:S7183
*/

const int SEN=0;
const int SPK=12;

int val=0;

void setup(){
	Serial.begin(9600);
}
void loop(){
	val=analogRead(SEN);

	tone(SPK, val/2);
	Serial.println(val);
}