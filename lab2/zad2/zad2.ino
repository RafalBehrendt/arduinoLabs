#include <LiquidCrystal.h> //Dołączenie bilbioteki
#define ADC_PIN A0
#define BUTTON_PIN 2
#define LED_BACKLIGHT 7

LiquidCrystal lcd(12, 13, 8, 9, 10, 11); //Informacja o podłączeniu nowego wyświetlacza
int readValue = 0;
char data[100];
char str_vol[6];
int lastVal = 0;
bool isBacklightOn = false;
bool lastBtnState = HIGH;

void backLight(){
  digitalWrite(LED_BACKLIGHT, HIGH);
  isBacklightOn = true;
}

void noBackLight(){
  digitalWrite(LED_BACKLIGHT, LOW);
  isBacklightOn = false;
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BACKLIGHT, OUTPUT);
  backLight();
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(0, 0); //Ustawienie kursora
  lcd.print("Miernik A"); //Wyświetlenie tekstu
  lcd.print((int)ADC_PIN - A0);
}

void loop() {
  bool currentBtnState = digitalRead(BUTTON_PIN);
  if (lastBtnState != currentBtnState) {
      if (digitalRead(BUTTON_PIN) == LOW) {
        if (isBacklightOn) {
          noBackLight();
        }
        else {
          backLight();
        }
      }
    lastBtnState = currentBtnState;
  }

  lcd.setCursor(0, 1); //Ustawienie kursora
  readValue = analogRead(ADC_PIN);
  if (abs(readValue - lastVal) > 4) {
    lastVal = readValue;
    float voltage = readValue * (5.0 / 1024.0);
    dtostrf(voltage, 3, 2, str_vol);
    sprintf(data, "V=%s  ADC=%4d", str_vol, readValue);
    lcd.print(data);
  }
  Serial.print(lastVal * (5.0 / 1024.0));
  Serial.print("\t");
  Serial.print(isBacklightOn);
  Serial.println("");
  delay(200);
}
