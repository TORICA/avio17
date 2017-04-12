double pi,yi,ti;
double p,y,t;
double pk,yk,tk;

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
  p=(analogRead(0)-pi)*pk;
  y=(analogRead(1)-yi)*yk;
  t=(analogRead(7)-ti)*tk;
  Serial.print(p);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(t);
    Serial.print(",");
  Serial.print(myLPF(p));
  Serial.print(",");
  Serial.println(myLPF2(y));
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

