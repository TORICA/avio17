//convertFunctionTest.ino

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int x=-512;x<=512;x++){
 	Serial.print(x);
 	Serial.print(',');
 	Serial.println(calcOutput(x,120));
  }
}

/**
*	X ->	axis=0
*	Y ->	axis=1
*/
int calcOutput(int reading, int JS_DEADZONE){
	double x=3.14/(2*(512-JS_DEADZONE))*reading;
	return (int)(reading*(1.0-cos(x)));
}