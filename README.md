# # DeskPet - Masaüstü Evcil Robot

Bu proje, BOZ214 Fiziksel Programlama dersi kapsamında geliştirilmiştir. Amaç, ilkokul ve ortaokul düzeyindeki çocuklara yönelik eğlenceli, interaktif bir masaüstü robot tasarlamak ve hayvan sevgisini geliştirmektir.

## 📌 Özellikler

- Mesafe sensörü ile kullanıcı algılama  
- RGB LED ile ruh hali gösterimi (mavi, yeşil, kırmızı)  
- Servo motor ile kol hareketi  
- OLED ekran ile yüz ifadeleri ve saat gösterimi  
- RTC modülü ile gerçek zamanlı saat takibi  
- Buzzer ile sesli uyarılar  
- Buton ile saat gösterme modu  

## 📌 Çalışma Prensibi

- Robot normalde **mavi** ışıkta durgun bekler.  
- Kullanıcı 5 cm mesafeden yaklaştığında **yeşil** ışığa geçer, gözlerini kapatır, kolunu kaldırır.  
- 10 dakika boyunca hiç temas algılanmazsa **kırmızı** ışığa geçer, üzgün göz gösterir ve 1 saniyede bir bip sesi verir.  
- Durgun haldeyken butona basılırsa, OLED ekranda saat ve dakika bilgisi gösterilir.  

## 📌 Bağlantı Şeması

- HC-SR04 mesafe sensörü: Trig D9, Echo D10  
- Servo motor: D11  
- RGB LED: R D3, G D5, B D6  
- Buzzer: D8  
- Buton: D7  
- OLED I2C: SDA A4, SCL A5  
- RTC I2C: SDA A4, SCL A5  

## 📌 Kullanılan Malzemeler

- Arduino Uno  
- HC-SR04 mesafe sensörü  
- SG90 servo motor  
- 0.96” I2C OLED ekran  
- RGB LED (ortak anot)  
- RTC DS3231 modülü  
- Buzzer  
- 4 pinli push buton  
- Breadboard ve jumper kablolar  

## 📌 Katkıda Bulunanlar

Berfe Çimen 23040019 - BOZ214 Proje Öğrencisi


