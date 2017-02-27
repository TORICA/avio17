//tscdjjn001pducv.ino

unsigned long  t_0;

const int OFFSET=28;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  double reading=analogRead(0)-OFFSET;
  Serial.print(myLPF(reading));
  Serial.print(',');
  Serial.println(reading);

  /*
  unsigned long t_now=millis();
  Serial.println(t_now-t_0);
  t_0=t_now;
  //1loopに約20[ms]=50[Hz]
  */
}

const int samplingnum=40;
double vals[samplingnum];
int count=0;
double myLPF(double val){
  //Serial.println("");
  
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