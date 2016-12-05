//tail.ino

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
	int valx1=analogRead(0);
	int valy1=analogRead(1);
	int valz1=analogRead(2);
  int valx2=analogRead(3);
  int valy2=analogRead(4);
  int valz2=analogRead(5);
	float gx1=((float)valx1/1023*5-1.65)/0.66;
	float gy1=((float)valy1/1023*5-1.65)/0.66;
	float gz1=((float)valz1/1023*5-1.65)/0.66;
  float gx2=((float)valx2/1023*5-2.50);
  float gy2=((float)valy2/1023*5-2.50);
  float gz2=((float)valz2/1023*5-2.50);
	float pitch1=acos(gx1/sqrt(square(gy1)+square(gz1)))/M_PI*180;
	float roll1=atan(gx1/gy1)/M_PI*180;
  float pitch2=acos(gy2/sqrt(square(-gx2)+square(gz2)))/M_PI*180;
  float roll2=atan(gy2/(-gx2))/M_PI*180;
   /*
   /*
  Serial.print(gx);
  Serial.print(",");
  Serial.print(gy);
  Serial.print(",");
  Serial.println(gz);
 
  Serial.print(pitch1);
  Serial.print(",");
  Serial.println(roll1);
  Serial.print(",");
  Serial.print(pitch2);
  Serial.print(",");
  Serial.println(roll2);
  */
  Serial.print(pitch1-pitch2-1.05644*pitch1);
  Serial.print(",");
  Serial.print(roll1);
  Serial.print(",");
  Serial.println(roll2);

}