#include "M5Cardputer.h"
#include "NotoSansBold15.h"
#include "NotoSansBold36.h"

M5Canvas sprite(&M5Cardputer.Display);

const int TRIG_G1_PIN = 1;
const int ECHO_G2_PIN = 2;

void setup() {
  pinMode(TRIG_G1_PIN, OUTPUT);
  pinMode(ECHO_G2_PIN, INPUT);

  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setBrightness(70);
  
  sprite.createSprite(240,135);
  sprite.setTextDatum(TL_DATUM);

  drawHeader("---");
  sprite.pushSprite(0,0);
}

void loop() {  
  drawSensorData();
  delay(100);
}

void drawSensorData() {
  sprite.drawString("         ", 60, 65);
  
  digitalWrite(TRIG_G1_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_G1_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_G1_PIN, LOW);

  float duration = pulseIn(ECHO_G2_PIN, HIGH);
  float distance = (duration*.0343)/2;
  
  distance = distance > 800 ? 0 : distance;

  String distStr = String(distance, 0);
  if(distance < 10) {
    distStr = " "+distStr;
  }
  if(distance < 100) {
    distStr = "  "+distStr;
  }

  sprite.setTextColor(TFT_SILVER, TFT_BLACK);
  sprite.drawString(distStr, 60, 65);
  sprite.drawString("cm", 130, 65);
  
  sprite.pushSprite(0,0);
  
}

void drawHeader(String placeholder) {

  sprite.fillSprite(BLACK);
  sprite.loadFont(NotoSansBold15);
  sprite.setTextColor(TFT_WHITE,TFT_BLACK);
  
  sprite.setTextColor(TFT_SILVER, TFT_BLACK);
  sprite.drawString(" DISTANCE ",4,4);
  sprite.setTextColor(TFT_SILVER, TFT_BLACK);
  sprite.drawString(" SENSOR ", 4,20);
  
  sprite.unloadFont();
  sprite.loadFont(NotoSansBold36);
  sprite.setTextColor(TFT_GREENYELLOW,TFT_BLACK);
  sprite.drawString("HC-SR04", 86, 4);

  sprite.drawString(placeholder, 60, 66);
}