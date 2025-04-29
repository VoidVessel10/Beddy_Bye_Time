//Used https://www.instructables.com/DS1307-Real-Time-Clock-RTC-With-Arduino/ to get RTC to work
#include <Wire.h>
#include <DS1307.h>

DS1307 rtc;

int redLedPin = 11;
int buttonPin = 9;

int buttonState;

int buzzerPin = 8;
void setup() {
  Serial.begin(9600);

  Serial.println("Init RTC...");
  rtc.begin();

  //only set the date+time one time
  //rtc.set(0, 39, 0, 4, 29, 2025); //sec, min, hour, month, day, year


  //If need to stop
  //rtc.stop();
  rtc.start();

  pinMode(redLedPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  showRTC();
  setTime(15, 42, 40);
  resetButton();
}

void buzzer() {
  tone(buzzerPin, 2500);
}

void resetButton() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    digitalWrite(redLedPin, LOW);
    noTone(buzzerPin);
    delay(500);
  }
}
void setTime(int aHour, int aMin, int aSec) {
  uint8_t sec, min, hour, day, month;
  uint16_t year;

  rtc.get(&sec, &min, &hour, &month, &day, &year);

  if (aHour == hour && aMin == min && aSec == sec) {
    digitalWrite(redLedPin, HIGH);
    delay(4000);
    buzzer();
  }
}
void showRTC() {
  uint8_t sec, min, hour, day, month;
  uint16_t year;

  //get time from RTC
  rtc.get(&sec, &min, &hour, &month, &day, &year);

  //serial output
  Serial.print("\nTime: ");
  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.print(min, DEC);
  Serial.print(":");
  Serial.print(sec, DEC);

  Serial.print("\nDate: ");
  Serial.print(month, DEC);
  Serial.print(".");
  Serial.print(day, DEC);
  Serial.print(".");
  Serial.print(year, DEC);

  //wait a second
  delay(1000);
}
