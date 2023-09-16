#include <Arduino.h>

int confLedPin    = D5; // Configurable - Default External LED Pin
int confButtonPin = D6; // Configurable - Default Button Pin
int runningMode   =  1; // Runtime - Define Running Mode (0=Normal; 1=Debug; 2=Config)
int buttonState   =  0; // Runtime - Define Current Button State
int brightness    =  0;
int fadeAmount    =  1;

void setup() {
  Serial.begin(115200);
  Serial.println("\nYuniq Technologies - ESP8266 Pushover Doorbell");
  Serial.println("Release Version: !Pre-Release");
  pinMode(confButtonPin, INPUT_PULLUP); //TODO: Configurable - Need to make it so this value pulls from a file instead
  pinMode(confLedPin, OUTPUT); //TODO: Configurable - Need to make it so this value pulls from a file instead
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("Running Mode: " + runningMode);
  if (runningMode==0){Serial.println(" - Normal Mode");}
  if (runningMode==1){Serial.println(" - DEBUG Mode\nIn Debug Mode - Things may run slower as we're writing everything to Serial!");}
  if (runningMode==2){Serial.println(" - CONFIGURATION Mode\nPlease connect to the Wireless Hotspot to configure this device.");}
}

void loop() {
  //if (runningMode==1){Serial.println("Started Loop");}
  int buttonState = digitalRead(confButtonPin);
  if (buttonState == HIGH) {
    if (runningMode==1){Serial.print("Button Pressed!\nRaw Analog Value was: ");Serial.println(analogRead(confButtonPin));}
    int loops = 0;
    while (loops <= 5) {
      digitalWrite(LED_BUILTIN, HIGH); digitalWrite(confLedPin, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW); digitalWrite(confLedPin, LOW);
      delay(100);
      loops = loops + 1;}
    brightness = 0;
    fadeAmount = 1;
  } else {
    analogWrite(LED_BUILTIN, brightness);
    analogWrite(confLedPin, brightness);}
    brightness = brightness + fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
  delay(5);
  //if (runningMode==1){Serial.println("Finished Loop");}
}