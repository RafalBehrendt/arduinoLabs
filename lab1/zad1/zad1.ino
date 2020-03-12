
#define GREEN_BUTTON 4
#define RED_BUTTON 2
#define PIN_LED 6
 
//licznik wcisniecia przycisku
int counter = 0;
bool lastGreenBtnState = HIGH;
bool lastRedBtnState = HIGH;
 
void setup() {
  Serial.begin(9600); 
  pinMode(GREEN_BUTTON, INPUT_PULLUP); 
  pinMode(RED_BUTTON, INPUT_PULLUP); 
  pinMode(PIN_LED, OUTPUT);
}
 
void loop() {
  bool greenBtnState = digitalRead(GREEN_BUTTON);
  bool redBtnState = digitalRead(RED_BUTTON);
  
  if(lastGreenBtnState != greenBtnState || lastRedBtnState != redBtnState){    
    if(redBtnState == LOW && greenBtnState == LOW){      
      delay(170);
      if (redBtnState == LOW && greenBtnState == LOW){
        Serial.println(counter);
        for(int i = 0; i < counter; i++){
          digitalWrite(PIN_LED, HIGH); 
          delay(500);     
          digitalWrite(PIN_LED, LOW);
          delay(500);  
        }
      }
      else{} 
    }
  else if(redBtnState == LOW && greenBtnState == HIGH){   
      delay(170);
      if (redBtnState == LOW && greenBtnState == HIGH){
        counter++;
        Serial.println(counter);
      }
      else{}
  }

  else if(greenBtnState == LOW && redBtnState == HIGH){
      delay(170);
      if (greenBtnState == LOW && redBtnState == HIGH){
        if(counter > 0){
          counter--;
          Serial.println(counter);
        }
      else{}
    }
  }
  lastRedBtnState = redBtnState;
  lastGreenBtnState = greenBtnState;
  }
}
