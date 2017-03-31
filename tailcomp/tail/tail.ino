//tail.ino

int sw1;
int sw2;
int val1;
int val2;
float alpha1;
float beta1;

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
 pinMode(3,INPUT_PULLUP);
 pinMode(4,INPUT_PULLUP);
 sw1=0;
 sw2=0;
 val1=1;
 val2=1;
 alpha1=0;
 beta1=0;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  float p1;
  float p2;
  float p3;
  float p4;
  float alpha;
  float beta;
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
  float pitchnew1=(pitch1-alpha1);
  float pitchnew2=(pitch2-beta1);
  if(val1<digitalRead(3)){
    sw1+=1;
  }
  
  if(sw1==1){
    p1=pitchnew1;
  }
  
  if(sw1==2){
    p2=pitchnew1;
    alpha=(p1+p2)/2;
  alpha1=alpha;
   p1=0;
   p2=0;
   alpha=0; 
   sw1=0;
   }
   if(val2<digitalRead(4)){
    sw2+=1;
  }
  
  if(sw2==1){
    p3=pitchnew2;
  }
  
  if(sw2==2){
    p4=pitchnew2;
    beta=(p3+p4)/2;
   beta1=beta;
   p3=0;
   p4=0;
   beta=0; 
   sw2=0;
   }
  val1=digitalRead(3);
  val2=digitalRead(4);
  
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

  Serial.print(pitchnew1);
  Serial.print(",");
  Serial.print(pitchnew2);
  Serial.print(",");
 
 
  Serial.println(pitchnew1-pitchnew2);
/*  Serial.print(",");
  
  Serial.print(roll1);
  Serial.print(","); 
  Serial.print(roll2);
  Serial.print(",");
  
  Serial.print(sw);
  Serial.print(",");
  Serial.println(roll1-roll2);
*/
}
