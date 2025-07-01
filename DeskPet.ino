#include <Wire.h>
#include <Servo.h>
#include <U8g2lib.h>
#include "RTClib.h"

// Mesafe sensörü
#define trigPin 9
#define echoPin 10

// RGB LED
#define redPin 3
#define greenPin 5
#define bluePin 6

// Buzzer
#define buzzerPin 8

// Buton
#define buttonPin 7

// Servo
Servo myservo;

// OLED
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// RTC
RTC_DS3231 rtc;

// zaman yönetimi
unsigned long lastSevmeZamani = 0;
unsigned long suankiZaman = 0;

// mod
// 0 = durgun (mavi)
// 1 = seviliyor (yeşil)
// 2 = hiç sevilmiyor 10dk (kırmızı)
int mood = 0;

// buton basımı
bool buttonPressed = false;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  myservo.attach(11);

  u8g2.begin();
  rtc.begin();

  // SAAT AYARI - bir kereye mahsus
  // rtc.adjust(DateTime(2025, 7, 1, 6, 7, 45));  // güncel saati gir
  // ayarladıktan sonra bu satırı yoruma almayı unutma:
  // rtc.adjust(DateTime(2025, 7, 1, 2, 10, 0));

  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);  // mavi başlangıç
  mood = 0;

  lastSevmeZamani = millis(); // açılış zamanı
}

void loop() {
  suankiZaman = millis();

  // mesafe ölç
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Mesafe: ");
  Serial.print(distance);
  Serial.println(" cm");

  // buton kontrolü
  if (digitalRead(buttonPin) == LOW) {
    buttonPressed = true;
  } else {
    buttonPressed = false;
  }

  // SEVİLİYOR (5cm ve altı)
  if (distance <= 5) {
    mood = 1;
    lastSevmeZamani = millis();  // zamanı resetle
  }
  // 10 dk boyunca sevilmeme durumu
  else if ((suankiZaman - lastSevmeZamani) >= 600000) {  // 10 dakika = 600000ms
    mood = 2;
  }
  // ara mod (mavi)
  else {
    mood = 0;
  }

  // mood davranışları
  if (mood == 0) {
    // durgun
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);  // mavi
    myservo.write(0); // kol aşağı
    digitalWrite(buzzerPin, LOW);

    // OLED göz
    u8g2.clearBuffer();
    if (buttonPressed) {
      // sadece durgun halde butona basınca saat göster
      DateTime now = rtc.now();
      char saat[9];
      sprintf(saat, "%02d:%02d", now.hour(), now.minute());
      u8g2.setFont(u8g2_font_ncenB08_tr);
      u8g2.drawStr(20, 35, saat);
    } else {
      // normal göz
      u8g2.setFont(u8g2_font_ncenB14_tr);
      u8g2.drawStr(30, 35, "o_o");
    }
    u8g2.sendBuffer();
  }
  else if (mood == 1) {
    // seviliyor
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    myservo.write(90); // kol yukarı
    digitalWrite(buzzerPin, LOW);

    // OLED göz kapalı
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(30, 35, "-_-");
    u8g2.sendBuffer();
  }
  else if (mood == 2) {
    // 10 dk boyunca hiç sevilmemiş
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    myservo.write(0); // kol aşağı

    // OLED üzgün göz
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(30, 35, "T_T");
    u8g2.sendBuffer();

    // buzzer 1sn aralıkla
    static unsigned long buzzerTime = 0;
    if (millis() - buzzerTime >= 1000) {
      buzzerTime = millis();
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
    }
  }

  delay(100);
}