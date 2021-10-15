#include <IRremote.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int startSW = 0; //시작스위치

int ledW = 1;
int led[] = {2, 3, 4, 5, 6, 7};


int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results decodedSignal;

decode_results results;

int HEART = 3, SCORE = 0;
int randumNum = random(16716015, 16743045);
// int randNum = random(0, 5);

LiquidCrystal_I2C lcd(0x27, 16, 2);

int i, j;

void setup() {

  // 스타트 버튼
  pinMode(startSW, INPUT_PULLUP);

  // LED 6개 설정
  for(i = 0; i < 6; i++) {
    pinMode(led[i], OUTPUT);
  }
  
  // LCD 설정
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);

  // 리모콘, 시리얼모니터 설정
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(RECV_PIN, INPUT);
  
}


void before_LCD() {
  lcd.setCursor(2, 0);
  lcd.print("PRESS BUTTON");
  delay(1000);
  lcd.clear();
  delay(1000);
}

void playing_LCD() {
  lcd.setCursor(2,0);
  lcd.print("NOW PLAYING");
  delay(1000);
  lcd.clear();
  delay(500);
  lcd.setCursor(1,0);
  lcd.print("HEART : ");
  lcd.print(HEART);
  lcd.setCursor(1,1);
  lcd.print("SCORE : ");
  lcd.print(SCORE);
  delay(3000);
}

void finish_LCD() {
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("GAME OVER");
  delay(5000);
  lcd.clear();
  delay(500);
}

void LED_RANDOM() {
  int randNum = random(0, 5);
  Serial.println(randumNum);
  if (randumNum == 0) { // 1 // 16724175
    digitalWrite(led[0], HIGH);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], LOW);
    digitalWrite(led[4], LOW);
    digitalWrite(led[5], LOW);
    }
  else if (randNum == 1) { // 2 // 16718055
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], HIGH);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], LOW);
    digitalWrite(led[4], LOW);
    digitalWrite(led[5], LOW);
    }
  else if (randNum == 2) { // 3 // 16743045
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], HIGH);
    digitalWrite(led[3], LOW);
    digitalWrite(led[4], LOW);
    digitalWrite(led[5], LOW);
    }
  else if (randNum == 3) { // 4 // 16716015
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], HIGH);
    digitalWrite(led[4], LOW);
    digitalWrite(led[5], LOW);
    }
  else if (randNum == 4) { // 5 //16726215
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], LOW);
    digitalWrite(led[4], HIGH);
    digitalWrite(led[5], LOW);
    }
  else if (randNum == 5) { // 6 // 16734885
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], LOW);
    digitalWrite(led[4], LOW);
    digitalWrite(led[5], HIGH);
    }
}

void game() {
  if (HEART == 0) {
    finish_LCD();
    }
  else {
/*    if (irrecv.decode(&results)){  // 적외선 리모컨의 신호를 받을 때
    switch (results.value) {
      case 0x00FF5AA5:     // +  버튼을 눌렀을 때
        if (digitalRead(led[4])==HIGH) { // LED가 켜져있을때
            SCORE += 5;
            digitalWrite(led[4], LOW);
          }
          else {
            HEART--;
          break;
        }
    }
    }
  }*/
   if (irrecv.decode(&decodedSignal) == true) {
    Serial.println(decodedSignal.value,DEC);
    switch (decodedSignal.value) {
        case 0x00FF6897:
          Serial.println("Press '0'");
          HEART--;
          break;
        case 0x00FF30CF: // 16724175
          Serial.println("Press '1'");
          // if를 해서 rannum과 같으면 score +5, 아니면 heart-1
          if (randumNum == 16724175) {
            SCORE += 5;
            digitalWrite(led[0], LOW);
          }
          else
            HEART--;
          break;
        case 0x00FF18E7:
          Serial.println("Press '2'"); // 16718055
          // if를 해서 rannum과 같으면 score +5, 아니면 heart-1
          if (randumNum == 16718055) {
            SCORE += 5;
            digitalWrite(led[1], LOW);
          }
          else
            HEART--;
          break;
        case 0x00FF7A85:
          Serial.println("Press '3'"); // 16743045
          // if를 해서 rannum과 같으면 score +5, 아니면 heart-1
          if (randumNum == 16743045) {
            SCORE += 5;
            digitalWrite(led[2], LOW);
          }
          else
            HEART--;
          break;
        case 0x00FF10EF:
          Serial.println("Press '4'"); // 16716015
          // if를 해서 rannum과 같으면 score +5, 아니면 heart-1
          if (randumNum == 16716015) {
            SCORE += 5;
            digitalWrite(led[3], LOW);
          }
          else
            HEART--;
          break;
        case 0x00FF38C7:
          Serial.println("Press '5'"); // 16726215
          // if를 해서 rannum과 같으면 score +5, 아니면 heart-1
          if (randumNum == 16726215) {
            SCORE += 5;
            digitalWrite(led[4], LOW);
          }
          else
            HEART--;
          break;
        case 0x00FF5AA5:   
          Serial.println("Press '6'"); // 16734885
          // if를 해서 rannum과 같으면 score +5, 아니면 heart-1
          if (randumNum == 16734885) {
            SCORE += 5;
            digitalWrite(led[5], LOW);
          }
          else
            HEART--;
          break;
        case 0x00FF42BD:
          Serial.println("Press '7'");
          HEART--;
          break;
        case 0x00FF4AB5:
          Serial.println("Press '8'");
          HEART--;
          break;                          
        case 0x00FF52AD:
          Serial.println("Press '9'");
          HEART--;
          break;                          
        default:
        HEART--;
          break;                                                      
      }
    }
  }
    irrecv.resume();
  }

void fnd (unsigned char n) {
  switch(n) {
    case 0:
  before_LCD();
    lcd.clear();
    break;
    
    case 1:
  playing_LCD();
  LED_RANDOM();
  delay(3000);
  game();
//  playing_LCD();
//    digitalWrite(led[0], LOW);
//    digitalWrite(led[1], LOW);
//    digitalWrite(led[2], LOW);
//    digitalWrite(led[3], LOW);
//    digitalWrite(led[4], LOW);
//    digitalWrite(led[5], LOW);
//    delay(1000);
//  LED_RANDOM();
//  delay(300);
//  game();
    break;
    }
  }

void loop() {
//  int r = 0;
//  fnd (r);
//    if (!digitalRead(0)) {
//      fnd(1);
//      }

  playing_LCD();
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
    digitalWrite(led[3], LOW);
    digitalWrite(led[4], LOW);
    digitalWrite(led[5], LOW);
    delay(1000);
  LED_RANDOM();
  delay(300);
  game();
}