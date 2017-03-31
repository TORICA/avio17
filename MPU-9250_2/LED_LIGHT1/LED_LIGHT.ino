#define LED_PIN1 2
#define LED_PIN4 3
#define LED_PIN5 4
#define LED_PIN6 5
#define LED_PIN9 6
#define LED_PIN10 7
#define LED_PIN13 8
#define LED_PIN14 9
#define LED_PIN15 10
#define LED_PIN18 11
#define LED_PIN19 12
#define LED_PIN20 13
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN4, OUTPUT);
  pinMode(LED_PIN5, OUTPUT);
  pinMode(LED_PIN6, OUTPUT);
  pinMode(LED_PIN9, OUTPUT);
  pinMode(LED_PIN10, OUTPUT);
  pinMode(LED_PIN13, OUTPUT);
  pinMode(LED_PIN14, OUTPUT);
  pinMode(LED_PIN15, OUTPUT);
  pinMode(LED_PIN18, OUTPUT);
  pinMode(LED_PIN19, OUTPUT);
  pinMode(LED_PIN20, OUTPUT);
}

void loop() {
  // put your main code hereto run repeatedly:
 driveLED(6);
 
 
 
 
 
 int i;
 for(i=0;i<13;i++){
  driveLED(i);
  delay(50);
 }
 
 
 
}
void driveLED(int led) {
    /*  digitalWrite(LED_PIN1, LOW);
      digitalWrite(LED_PIN4, HIGH);
      digitalWrite(LED_PIN5, HIGH);
      digitalWrite(LED_PIN6, LOW);
      digitalWrite(LED_PIN9,HIGH);
      digitalWrite(LED_PIN10,HIGH); 
      digitalWrite(LED_PIN13,HIGH);
      digitalWrite(LED_PIN14,HIGH);
      digitalWrite(LED_PIN15,LOW);
      digitalWrite(LED_PIN18,HIGH);
      digitalWrite(LED_PIN19,HIGH);
      digitalWrite(LED_PIN20,LOW);
      */
  switch (led) {
    case 1:
      digitalWrite(LED_PIN1, HIGH);
      break;
    case 2:
      // varが2のとき実行される
      digitalWrite(LED_PIN4, LOW);
      digitalWrite(LED_PIN5, HIGH);
      break;
    case 3:
      digitalWrite(LED_PIN4, HIGH);
      digitalWrite(LED_PIN5, LOW);
      // どのcaseにも一致しなかったとき実行される
      // (defaultは省略可能)
      break;
    case 4:
       digitalWrite(LED_PIN6,HIGH);
       break;
    case 5:
        digitalWrite(LED_PIN9, LOW);
        digitalWrite(LED_PIN10, HIGH);
        break;
    case 6:
        digitalWrite(LED_PIN9, HIGH);
        digitalWrite(LED_PIN10, LOW);
        break;
    case 7:
        digitalWrite(LED_PIN13, LOW);
        digitalWrite(LED_PIN14, HIGH);
        break;
    case 8:
        digitalWrite(LED_PIN13,HIGH);
        digitalWrite(LED_PIN14, LOW);
        break;
    case 9:
       digitalWrite(LED_PIN15,HIGH);
       break;
    case 10:
        digitalWrite(LED_PIN18, LOW);
        digitalWrite(LED_PIN19, HIGH);
        break;
    case 11:
        digitalWrite(LED_PIN18, HIGH);
        digitalWrite(LED_PIN19, LOW);
        break;
    case 12:
        digitalWrite(LED_PIN20,HIGH);
        break;
    
  }
}

