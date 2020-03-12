#include <LiquidCrystal.h> //Dołączenie bilbioteki
#define RED_BUTTON 4
#define GREEN_BUTTON 2
#define LED_BACKLIGHT 7
#define SIZE 10

class StringArray {
  public:
    StringArray(int size) {
      strings = new String[size];
      this->size = size;
      numOfElems = 0;
    }
    ~StringArray() {
      delete[] strings;
    }
    void addElem(String elem) {
      if (numOfElems < size) {
        strings[numOfElems++] = elem;
      }
      else {
        for (int i = 1; i < size; i++) {
          strings[i - 1] = strings[i];
        }
        strings[size - 1] = elem;
      }

    }
    String getElem(int pos) {
      return strings[pos];
    }

    int getNumOfElems() {
      return numOfElems;
    }

  private:

    String * strings;
    int size;
    int numOfElems;
};

LiquidCrystal lcd(12, 13, 8, 9, 10, 11); //Informacja o podłączeniu nowego wyświetlacza
StringArray strings = StringArray(SIZE);
int curPos = 0;
String curStrings[2];
int posOfTexts[2] = {0, 0};

void marquee(String str, int pos) {
  lcd.setCursor(0, pos);
  if (curStrings[pos].length() - posOfTexts[pos] > 16) {
    lcd.print(str.substring(++posOfTexts[pos]));
  }
  else {
    lcd.print(curStrings[pos]);
    posOfTexts[pos] = 0;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(LED_BACKLIGHT, OUTPUT);
  lcd.begin(16, 2); //Deklaracja typu
  lcd.setCursor(0, 0); //Ustawienie kursora
  digitalWrite(LED_BACKLIGHT, HIGH);
}

void loop() {

  lcd.clear();
  marquee(curStrings[0], 0);
  marquee(curStrings[1], 1);

  if (Serial.available() > 0) { //Czy Arduino odebrało dane
    String msg = Serial.readStringUntil('\n');
    lcd.clear();
    strings.addElem(msg);
    curPos = strings.getNumOfElems() - 1;
    if (curPos == 0) {
      lcd.setCursor(0, 0);
      lcd.print(msg);
      curStrings[0] = msg;
      posOfTexts[0] = 0;
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print(strings.getElem(curPos - 1));
      lcd.setCursor(0, 1);
      lcd.print(msg);
      curStrings[0] = strings.getElem(curPos - 1);
      curStrings[1] = msg;
      posOfTexts[1] = 0;
    }
  }

  if (digitalRead(RED_BUTTON) == LOW) {
    if (curPos > 1) {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(strings.getElem(--curPos));
      lcd.setCursor(0, 0);
      lcd.print(strings.getElem(curPos - 1));
      curStrings[0] = strings.getElem(curPos - 1);
      curStrings[1] = strings.getElem(curPos);
      posOfTexts[0] = 0;
      posOfTexts[1] = 0;
      delay(200);
    }
  }

  if (digitalRead(GREEN_BUTTON) == LOW) {
    if (curPos < strings.getNumOfElems() - 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(strings.getElem(curPos));
      lcd.setCursor(0, 1);
      curStrings[0] = strings.getElem(curPos);
      lcd.print(strings.getElem(++curPos));
      curStrings[1] = strings.getElem(curPos);
      posOfTexts[0] = 0;
      posOfTexts[1] = 0;
      delay(200);
    }
  }
  delay(700);
}
