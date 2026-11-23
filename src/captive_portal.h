#pragma once
#include <Arduino.h>


void captivePortalBegin(const char *ssid = "esp-captive");
void captivePortalLoop();
bool captivePortalGetSubmission(String &name, String &proficiency);