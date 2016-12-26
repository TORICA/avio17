/*
 * ピトー管実験装置回転速度検出
 * 立ち上がり検出
 * 
 * digitalReadで
 */
unsigned long t_0=0;
unsigned long t_c=0;

boolean isHIGH=false;

const double RA=0.1;

double getV(unsigned long t_c){
  return 1000.0*RA*PI/(double)t_c/4.0;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(7, INPUT);
  
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(7)){
    if(!isHIGH){
      unsigned long t_now=micros();
      t_c=t_now-t_0;
      t_0=t_now;
      /*
        ↓だと上手くいかない
        t_c=micros()-t_0;
        t_0=micros();
       */
      isHIGH=true;
    }
  }else{
    isHIGH=false;
  }
  Serial.print(t_0);
  Serial.print(',');
  Serial.println(t_c);
  //Serial.println(pt_val);
  //Serial.println(getV(t_c));
}
