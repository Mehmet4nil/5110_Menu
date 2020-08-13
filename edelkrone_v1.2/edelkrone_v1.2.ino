// LCD5110_Graph_Demo
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of most of the functions
// in the library.
//
// This program requires a Nokia 5110 LCD module.
//
// It is assumed that the LCD module is connected to
// the following pins using a levelshifter to get the
// correct voltage to the module.
//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 11
//      CS   - Pin 12
//
#include <LCD5110_Graph.h>

LCD5110 myGLCD(8, 9, 10, 11, 12);

extern uint8_t SmallFont[];
extern uint8_t TinyFont[];
extern uint8_t batt[];
extern uint8_t cell[];

extern uint8_t lft[];
extern uint8_t right[];
extern uint8_t up[];
extern uint8_t down[];
extern uint8_t s_lft[];
extern uint8_t s_right[];
extern uint8_t s_up[];
extern uint8_t s_down[];

extern uint8_t ico[];
extern uint8_t bar[];
extern uint8_t scroll_bar[];
extern uint8_t scroll_line[];
//extern uint8_t scroll_line_down[];

float y;
uint8_t *bm;
int pacy, btnI = 0, btnII = 0, btnIII = 0, btnPhc = 1, btnSet = 0, i = 1, j = 0, scroll = 10,
          cnt = 0, cnt2 = 0, spd = 50, Gspd = 0, acc = 50, Gacc = 0;
float Fspd = 0.0, Facc = 0.0;
// const int ledPin =  4;
const int btnOk = 2;
const int btnUp = 3;
const int btnDown = 4;
const int btnRight = 5;
const int btnLeft = 6;
const int btnOne = 7;
const int btnTwo = 13;
int btnStateOk = 0, btnStateUp = 0, btnStateDown = 0, btnStateRight = 0,
    btnStateLeft = 0, btnStateOne = 0, btnStateTwo = 0;
String Sspd, Sacc;
char *settingStr[] = {"general", "connection", "devices",
                      "brightness", "graphic", "reset", "about"};
void setup() {
  pinMode(btnOk, INPUT);
  pinMode(btnUp, INPUT);
  pinMode(btnDown, INPUT);
  pinMode(btnRight, INPUT);
  pinMode(btnLeft, INPUT);
  pinMode(btnOne, INPUT);
  pinMode(btnTwo, INPUT);
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  randomSeed(analogRead(7));
  myGLCD.drawBitmap(0, 0, ico, 84, 48);

  Fspd = 0.58 * spd;
  Gspd = round(Fspd);
  Facc = 0.58 * acc;
  Gacc = round(Facc);

  myGLCD.update();
  delay(1200);
  myGLCD.clrScr();
}

void loop() {
  btnStateOk = digitalRead(btnOk);
  btnStateUp = digitalRead(btnUp);
  btnStateDown = digitalRead(btnDown);
  btnStateRight = digitalRead(btnRight);
  btnStateLeft = digitalRead(btnLeft);
  btnStateOne = digitalRead(btnOne);
  btnStateTwo = digitalRead(btnTwo);

  myGLCD.setFont(TinyFont);
  myGLCD.clrScr();

  //__________________PAGE  TITLE__________________
  myGLCD.drawBitmap(0, 0, batt, 12, 4);
  myGLCD.drawBitmap(73, 0, cell, 11, 4);
  myGLCD.print("edelkrone", CENTER, 0);
  myGLCD.drawLine(0, 6, 84, 6);
  //__________________SELECT PAGE__________________
  if (btnStateOk == HIGH && cnt2 == 0) {
    btnPhc += 1;
    if (btnPhc > 3) {
      btnPhc = 1;
    }
    cnt2 = 1;
  }
  if (btnStateOk == LOW) {
    cnt2 = 0;
  }
  //__________________PAGES START__________________
  switch (btnPhc) {
  case 1: //________________________PAGE 1_______________________
    myGLCD.print("   PAN", LEFT, 20);
    myGLCD.print("TLT   ", RIGHT, 20);
    myGLCD.drawBitmap(0, 20, lft, 3, 5);
    myGLCD.drawBitmap(32, 20, right, 3, 5);
    myGLCD.drawBitmap(47, 20, up, 5, 3);
    myGLCD.drawBitmap(79, 21, down, 5, 3);
    myGLCD.setFont(SmallFont);
    myGLCD.drawLine(41, 9, 41, 33);
    myGLCD.drawLine(0, 35, 84, 35);
    myGLCD.drawLine(27, 35, 27, 48);
    myGLCD.drawLine(57, 35, 57, 48);
    //-------------POSITION BUTTON------------------

    myGLCD.print("  1 ", LEFT, 39);
    myGLCD.print(" 2 ", CENTER, 39);
    myGLCD.print(" 3  ", RIGHT, 39);

    if (btnStateOne == HIGH) {
      btnI = 1;
    } else if (btnStateTwo == HIGH) {
      btnII = 1;
    } else if (btnStateRight == HIGH) {
      myGLCD.drawBitmap(32, 20, s_right, 3, 5);
    } else if (btnStateLeft == HIGH) {
      myGLCD.drawBitmap(0, 20, s_lft, 3, 5);
    } else if (btnStateUp == HIGH) {
      myGLCD.drawBitmap(47, 20, s_up, 5, 3);
    } else if (btnStateDown == HIGH) {
      myGLCD.drawBitmap(79, 21, s_down, 5, 3);
    }
    //--------------------------------------
    if (btnI == 1) {
      myGLCD.invertText(true);
      myGLCD.print("  1 ", LEFT, 39);
      myGLCD.invertText(false);
    }
    if (btnII == 1) {
      myGLCD.invertText(true);
      myGLCD.print(" 2 ", CENTER, 39);
      myGLCD.invertText(false);
    }
    /*
      myGLCD.print(" 3  ", RIGHT, 39);
      myGLCD.invertText(false);
    */
    myGLCD.update();
    break;

  case 2: //________________________PAGE 2_________________________

    Sspd = String(spd);
    Sacc = String(acc);
    myGLCD.setFont(TinyFont);
    myGLCD.print("   SPD", LEFT, 20);
    myGLCD.print("ACC   ", RIGHT, 20);
    myGLCD.drawBitmap(0, 20, lft, 3, 5);
    myGLCD.drawBitmap(32, 20, right, 3, 5);
    myGLCD.drawBitmap(47, 20, up, 5, 3);
    myGLCD.drawBitmap(79, 21, down, 5, 3);
    myGLCD.drawLine(41, 9, 41, 33);
    myGLCD.drawLine(0, 35, 84, 35);
    myGLCD.print("SPD", LEFT, 37);
    myGLCD.print("ACC", LEFT, 43);
    myGLCD.print(Sspd, RIGHT, 37);
    myGLCD.print(Sacc, RIGHT, 43);
    myGLCD.drawBitmap(12, 37, bar, 60, 11);
    myGLCD.drawLine(13, 39, 13 + Gspd, 39);
    myGLCD.drawLine(13, 45, 13 + Gacc, 45);
    // myGLCD.drawLine(13, 45, 71, 45);  71-13 = 58

    if (btnStateRight == HIGH && spd >= 0 && spd < 100) {
      myGLCD.drawBitmap(32, 20, s_right, 3, 5);
      spd += 1;
      Fspd += 0.58;
      Gspd = round(Fspd);
      delay(50);
    } else if (btnStateLeft == HIGH && spd > 0 && spd <= 100) {
      myGLCD.drawBitmap(0, 20, s_lft, 3, 5);
      spd += -1;
      Fspd += -0.58;
      Gspd = round(Fspd);
      delay(50);
    } else if (btnStateUp == HIGH && acc >= 0 && acc < 100) {
      myGLCD.drawBitmap(47, 20, s_up, 5, 3);
      acc += 1;
      Facc += 0.58;
      Gacc = round(Facc);
      delay(50);
    } else if (btnStateDown == HIGH && acc > 0 && acc <= 100) {
      myGLCD.drawBitmap(79, 21, s_down, 5, 3);
      acc += -1;
      Facc += -0.58;
      Gacc = round(Facc);
      delay(50);
    }

    myGLCD.update();
    break;
  case 3: //________________________PAGE 3 (SETTINGS)_________________________
    myGLCD.clrScr();
    myGLCD.drawBitmap(0, 0, batt, 12, 4);
    myGLCD.drawBitmap(73, 0, cell, 11, 4);
    myGLCD.print("settings", CENTER, 0);
    myGLCD.drawLine(0, 6, 84, 6);
    myGLCD.drawBitmap(79, 7, scroll_line, 5, 41);
    myGLCD.drawBitmap(79, scroll, scroll_bar, 5, 11);
    myGLCD.setFont(SmallFont);
    //-----------------settings slide function----------------
    if (btnStateDown == HIGH && btnSet < 6) {
      btnSet += 1;
      if (i < 5) {
        i += 1;
      }
      if (btnSet > 4 && btnSet < 7) {
        j += 1;
      }
      scroll += 4;
      delay(150);
    } else if (btnStateUp == HIGH && btnSet > 0) {
      btnSet -= 1;
      if (i > 1) {
        i -= 1;
      }
      if (btnSet < 2 && btnSet > -1) {
        j -= 1;
      }
      scroll -= 4;
      delay(150);
    }
    //------------------------------------------------
    myGLCD.print(settingStr[j], CENTER, 8);
    myGLCD.print(settingStr[j+1], CENTER, 16);
    myGLCD.print(settingStr[j+2], CENTER, 24);
    myGLCD.print(settingStr[j+3], CENTER, 32);
    myGLCD.print(settingStr[j+4], CENTER, 40);

    myGLCD.invertText(true);
    myGLCD.print(settingStr[btnSet], CENTER, i * 8);
    myGLCD.invertText(false);

    myGLCD.update();
    break;
  }

  //__________________PAGES END__________________
}
