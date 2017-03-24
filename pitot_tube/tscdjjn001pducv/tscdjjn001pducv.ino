//tscdjjn001pducv.ino

unsigned long  t_0;

const int OFFSET=27;//[ADB_count]
const int SEN=1;//[V/Pa]
const double RHO=1.205;//[kg/m^3]
const double K=0.64;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  double reading=analogRead(0)-OFFSET;
  //Serial.print(myLPF(reading));
  //Serial.print(',');
  //Serial.println(reading);
  Serial.println(calcV(myLPF(reading)));

   //double v= sqrt(abs(2*((int)val-OFFSET)/SEN/RHO));

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

/*double calcV(double adc_val){
	return (3.85+sqrt(14.8-7.32*adc_val))/3.66;
}*/
double calcV(double adc_val){
	if(adc_val<0){
		return 0;
	}else{
		return sqrt(adc_val*K);
	}
}