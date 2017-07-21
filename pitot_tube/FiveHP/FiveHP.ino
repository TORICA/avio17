double pi,yi,ti;
double p,y,t;
double pk,yk,tk;

unsigned long t0=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  pi=analogRead(0);
  yi=analogRead(1);
  ti=analogRead(7);

  pk=0.5;yk=-0.5;tk=0.5;
}

void loop() {
  // put your main code here, to run repeatedly:
  while(millis()-t0<1000){
      p=(analogRead(0)-pi)*pk;
      y=(analogRead(1)-yi)*yk;
      t=(analogRead(7)-ti)*tk;
      myLPF(p);
      myLPF2(y);
      myLPF3(t);
  }
  t0=millis();
  
  Serial.print(myLPF(p));
  Serial.print(',');
  Serial.print(myLPF(y));
  Serial.print(',');
  Serial.println(myLPF(t));
}
const int samplingnum=40;
double vals[samplingnum];
int count=0;
double myLPF(double val){
  
  vals[count]=val;
  
  if(count<=samplingnum-2){
    count++;
  }else{
    count=0;
  }
  double sum=0.0;
  for(int i=0;i<=samplingnum-1;i++){
    //Serial.print(vals[i]);
    //Serial.print(",");
    sum+=vals[i];
  }
  //Serial.println("");
  return ((float)sum)/((float)samplingnum);
}

const int samplingnum2=40;
double vals2[samplingnum];
int count2=0;
double myLPF2(double val){
  
  vals2[count]=val;
  
  if(count2<=samplingnum2-2){
    count2++;
  }else{
    count2=0;
  }
  double sum=0.0;
  for(int i=0;i<=samplingnum2-1;i++){
    //Serial.print(vals[i]);
    //Serial.print(",");
    sum+=vals2[i];
  }
  //Serial.println("");
  return ((float)sum)/((float)samplingnum2);
}


const int samplingnum3=40;
double vals3[samplingnum];
int count3=0;
double myLPF3(double val){
  
  vals3[count]=val;
  
  if(count3<=samplingnum3-2){
    count3++;
  }else{
    count3=0;
  }
  double sum=0.0;
  for(int i=0;i<=samplingnum3-1;i++){
    //Serial.print(vals[i]);
    //Serial.print(",");
    sum+=vals3[i];
  }
  //Serial.println("");
  return ((float)sum)/((float)samplingnum3);
}
