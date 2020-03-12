#define PIN_LED 6

int lastCount = 0;

void executeCommand(String com){
  if (com == "LED ON") LED_ON();
  else if (com == "LED OFF") LED_OFF();
  else if (com == "LED BLINK") LED_BLINK();
  else if (com.substring(0,9) == "LED BLINK"){
    String number = com.substring(10, 12);
    Serial.println(number);
    char num[3];
    number.toCharArray(num, 3);
    LED_BLINK(atoi(num));
  }
  //else Serial.println("Unknown command");
}

void LED_ON(){
  digitalWrite(PIN_LED, HIGH);
}

void LED_OFF(){
  digitalWrite(PIN_LED, LOW);
}

void LED_BLINK(int count){
  lastCount = count;
  LED_BLINK();
}

void LED_BLINK(){
  for(int i = 0; i < lastCount; i++){
    digitalWrite(PIN_LED, HIGH);
    delay(500);
    digitalWrite(PIN_LED, LOW);
    delay(500);
  }
}

void setup() {
  Serial.begin(9600); 
  pinMode(PIN_LED, OUTPUT);
}
 
void loop() {
    if(Serial.available() > 0) {
      String com = Serial.readStringUntil('\n');
      executeCommand(com);
    }
}
