// Quick and dirty 38kHz IR sniffer that ouputs to mini OLED

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define IR_PIN D5
#define LED_PIN D6

/*** globals ***/
Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, -1);

/*** main ***/

void setup() {
    Serial.begin(9600);
    while(!Serial) {}
    Serial.println("\n* * * START * * *");

    pinMode(LED_PIN, OUTPUT);

    // init display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed.");
        while(1) {}
    }
    delay(500);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 16);
    display.println("hello world");
    display.display();
    
    Serial.println("\nSetup done.");
}

void loop() {
	digitalWrite(LED_PIN, 1);
    delay(1000);
    digitalWrite(LED_PIN, 0);
    delay(1000);
}
