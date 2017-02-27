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
	float gx1=((float)valx1/1023*5-2.50);
	float gy1=((float)valy1/1023*5-2.50);
	float gz1=((float)valz1/1023*5-2.50);
  float gx2=((float)valx2/1023*5-2.50);
  float gy2=((float)valy2/1023*5-2.50);
  float gz2=((float)valz2/1023*5-2.50);
	float pitch1=atan(gx1/sqrt(square(gy1)+square(gz1)))/M_PI*180;
	float roll1=atan(-gy1/gz1)/M_PI*180;
  float pitch2=atan(gx2/sqrt(square(gy2)+square(gz2)))/M_PI*180;
  float roll2=atan(-gy2/gz2)/M_PI*180;
  float pitchnew1=(pitch1+2.2);
  float pitchnew2=(pitch2-3.6);
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


  Serial.print(pitchnew1);
  Serial.print(",");
  Serial.print(pitchnew2);
  Serial.print(",");
*/
  Serial.print(pitchnew1-pitchnew2+0.06875*pitchnew2);
  Serial.print(",");
/*
  Serial.print(roll1);
  Serial.print(",");
  Serial.print(roll2);
  Serial.print(",");
*/
  Serial.println(roll1-roll2);

}

