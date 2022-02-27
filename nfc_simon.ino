#define DEBUG true
#define DEBUG_SERIAL if(DEBUG)Serial

// OLED
#include <U8g2lib.h>
#include <SPI.h>
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

// NFC
#include <MFRC522.h>
#include <SPI.h>
#define RST_PIN 5
#define SS_PIN 10
byte readCard[4];
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// dfplayer
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(6, 7); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// button
#include <Bounce2.h>

#define PreviousButton 2
#define NextButton 3
#define PauseButton 4
#define VolDownButton 8
#define VolUpButton 9

Bounce PreviousDebouncer = Bounce();
Bounce NextDebouncer = Bounce();
Bounce PauseDebouncer = Bounce();
Bounce VolDownDebouncer = Bounce();
Bounce VolUpDebouncer = Bounce();

bool isPaused = false;

void setup() {
  DEBUG_SERIAL.begin(115200);
  // OLED
  u8g2.enableUTF8Print();
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_lubI18_tf);
  u8g2.setCursor(30,31);
  u8g2.print(F("Simon"));
//  u8g2.print(F("Siloé"));
  u8g2.sendBuffer();

  // Button
  pinMode(PreviousButton,INPUT_PULLUP);
  PreviousDebouncer.attach(PreviousButton);
  PreviousDebouncer.interval(5); // interval in ms
  pinMode(NextButton,INPUT_PULLUP);
  NextDebouncer.attach(NextButton);
  NextDebouncer.interval(5); // interval in ms
  pinMode(PauseButton,INPUT_PULLUP);
  PauseDebouncer.attach(PauseButton);
  PauseDebouncer.interval(5); // interval in ms
  pinMode(VolDownButton,INPUT_PULLUP);
  VolDownDebouncer.attach(VolDownButton);
  VolDownDebouncer.interval(5); // interval in ms
  pinMode(VolUpButton,INPUT_PULLUP);
  VolUpDebouncer.attach(VolUpButton);
  VolUpDebouncer.interval(5); // interval in ms

  // NFC
  SPI.begin();
  mfrc522.PCD_Init();
  if (DEBUG) { mfrc522.PCD_DumpVersionToSerial(); }

  // dfplayer
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  delay(500);
  u8g2.setPowerSave(1);
  myDFPlayer.randomAll();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
myDFPlayer.volumeDown();
Serial.println(myDFPlayer.readVolume());
}

void loop() {
  PreviousDebouncer.update();
  if ( PreviousDebouncer.fell()) {
    DEBUG_SERIAL.print(F("Previous"));
    myDFPlayer.next();
  }
  PauseDebouncer.update();
  if ( PauseDebouncer.fell()) {
    if ( ! isPaused) {
      DEBUG_SERIAL.print(F("Pause"));
      isPaused = !isPaused;
      myDFPlayer.pause();
    } else {
      DEBUG_SERIAL.print(F("Reprise"));
      isPaused = !isPaused;
      myDFPlayer.start();
    }
  }
  NextDebouncer.update();
  if ( NextDebouncer.fell()) {
    DEBUG_SERIAL.print(F("next"));
    myDFPlayer.previous();
  }
  VolDownDebouncer.update();
  if ( VolDownDebouncer.fell()) {
    DEBUG_SERIAL.print(F("vol -"));
    myDFPlayer.volumeDown();
  }
  VolUpDebouncer.update();
  if ( VolUpDebouncer.fell()) {
    DEBUG_SERIAL.print(F("vol +"));
    myDFPlayer.volumeUp();
  }

  if ( ! mfrc522.PICC_IsNewCardPresent()) { return; }
  if ( ! mfrc522.PICC_ReadCardSerial()) { return; }
  if (mfrc522.uid.uidByte[1] == 76 && mfrc522.uid.uidByte[2] == 32 && mfrc522.uid.uidByte[3] == 14 && mfrc522.uid.uidByte[4] == 112) {
    // 4 76 32 14 112 // robot bleu
    DEBUG_SERIAL.println(F(" Lalala "));
    u8g2.setPowerSave(0);
    u8g2.clearBuffer();
    u8g2.setCursor(20,31);
    u8g2.print(F("Lalala"));
    u8g2.sendBuffer();
    myDFPlayer.loopFolder(1);
    delay(1000);
    u8g2.setPowerSave(1);
  } else if (mfrc522.uid.uidByte[1] == 21 && mfrc522.uid.uidByte[2] == 145 && mfrc522.uid.uidByte[3] == 122 && mfrc522.uid.uidByte[4] == 76) {
    // 4 21 145 122 76 // Peach
    DEBUG_SERIAL.println(F(" Henri Dès "));
    u8g2.setPowerSave(0);
    u8g2.clearBuffer();
    u8g2.setCursor(0,31);
    u8g2.print(F("Henri Dès"));
    u8g2.sendBuffer();
    myDFPlayer.loopFolder(2);
    delay(1000);
    u8g2.setPowerSave(1);
  } else if (mfrc522.uid.uidByte[1] == 21 && mfrc522.uid.uidByte[2] == 145 && mfrc522.uid.uidByte[3] == 202 && mfrc522.uid.uidByte[4] == 70) {
    // 4 21 145 202 70 // Dinosaure
    DEBUG_SERIAL.println(F(" Aldebert "));
    u8g2.setPowerSave(0);
    u8g2.clearBuffer();
    u8g2.setCursor(10,31);
    u8g2.print(F("Aldebert"));
    u8g2.sendBuffer();
    myDFPlayer.loopFolder(3);
    delay(1000);
    u8g2.setPowerSave(1);
  } else if (mfrc522.uid.uidByte[1] == 31 && mfrc522.uid.uidByte[2] == 236 && mfrc522.uid.uidByte[3] == 14 && mfrc522.uid.uidByte[4] == 112) {
    // 4 1 12 14 112 // DonkeyKong
    // 4 31 236 14 112 // Wario
    DEBUG_SERIAL.println(F(" Boumboum "));
    u8g2.setPowerSave(0);
    u8g2.clearBuffer();
    u8g2.setCursor(0,31);
    u8g2.print(F("BoumBoum"));
    u8g2.sendBuffer();
    myDFPlayer.loopFolder(4);
    delay(1000);
    u8g2.setPowerSave(1);
  } else if (mfrc522.uid.uidByte[1] == 67 && mfrc522.uid.uidByte[2] == 158 && mfrc522.uid.uidByte[3] == 15 && mfrc522.uid.uidByte[4] == 112) {
    // 4 67 158 15 112 // Toad
    DEBUG_SERIAL.println(F(" Tout aléatoire "));
    u8g2.setPowerSave(0);
    u8g2.clearBuffer();
    u8g2.setCursor(8,31);
    u8g2.print(F("Tout"));
    u8g2.sendBuffer();
    myDFPlayer.randomAll();
    delay(1000);
    u8g2.setPowerSave(1);
  } else {
    if (DEBUG) {
      Serial.print(mfrc522.uid.uidByte[0]);
      Serial.print(F(" "));
      Serial.print(mfrc522.uid.uidByte[1]);
      Serial.print(F(" "));
      Serial.print(mfrc522.uid.uidByte[2]);
      Serial.print(F(" "));
      Serial.print(mfrc522.uid.uidByte[3]);
      Serial.print(F(" "));
      Serial.println(mfrc522.uid.uidByte[4]);
      delay(500);
    }
  }
} // loop()
