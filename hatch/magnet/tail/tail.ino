//tail.ino

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
	int valz=analogRead(0);
	int valy=analogRead(1);
	int valx=analogRead(2);
	float gx=((float)valx/1023*5-1.65)/0.66;
	float gy=((float)valy/1023*5-1.65)/0.66;
	float gz=((float)valz/1023*5-1.65)/0.66;
	float pitch=atan(gx/sqrt(square(gy)+square(gz)))/M_PI*180;
	float roll=atan(gy/gz)/M_PI*180;
   /*
  Serial.print(gx);
  Serial.print(",");
  Serial.print(gy);
  Serial.print(",");
  Serial.println(gz);
 */ 
  Serial.print(pitch);
  Serial.print(",");
  Serial.println(roll);
  
}