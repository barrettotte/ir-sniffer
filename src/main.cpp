// Quick and dirty 38kHz IR sniffer

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRac.h>
#include <IRutils.h>
#include <Wire.h>

#define IR_PIN D7
#define LED_PIN D6

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define IR_DEBOUNCE_MS 300
#define LED_FEEDBACK_MS 75

// Large buffer for decoding things like air conditioner remote codes
#define IR_BUFFER_SIZE 1024

// Milliseconds of "no more data" before message is considered ended.
// Some devices send multiple packets in quick succession (like air conditioner remotes)
//
// Large timeouts can cause issues with simpler protocols. For example, when a button is held down
// we could accidentally capture 2-3 messages.
//
// Don't exceed max timeout => 130ms
#define IR_TIMEOUT_MS 50

// Set smallest "UNKNOWN" message packets that we care about.
// Helps reduce false-positives from IR background noise.
// IR noise detection increases with length of IR_TIMEOUT_MS.
//
// Set higher when falsely receiving random short UNKNOWN messages.
#define IR_MIN_UNKNOWN_SIZE 12

// Tolerance given to incoming signals in order to match it. Normally, don't need to adjust. 
// But, set higher if library detects message sometimes, but not all the time.
#define TOLERANCE_PERCENTAGE 25

struct ezTimer {
    bool trigger;
    unsigned long currentMs;
    unsigned long prevMs;
};

/*** globals ***/

Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, -1);
decode_results irDecoded;
IRrecv irrecv(IR_PIN, IR_BUFFER_SIZE, IR_TIMEOUT_MS);

struct ezTimer irTimer;
struct ezTimer ledTimer;

/*** utils ***/

void resetDisplay() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.setTextSize(WHITE);
}

/*** main ***/

void setup() {
    Serial.begin(115200);
    while(!Serial) {}
    Serial.println("\n* * * START * * *");

    pinMode(LED_PIN, OUTPUT);

    // init display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed.");
        while(1) {}
    }
    delay(500);
    resetDisplay();
    display.println("Ready for IR Signals!");
    display.display();

    // init IR
    irrecv.setUnknownThreshold(IR_MIN_UNKNOWN_SIZE);
    irrecv.setTolerance(TOLERANCE_PERCENTAGE);
    irrecv.enableIRIn();

    Serial.println("Setup done.");
}

void loop() {
    ledTimer.currentMs = millis();
    if ((ledTimer.currentMs - ledTimer.prevMs) > LED_FEEDBACK_MS) {
        ledTimer.prevMs = ledTimer.currentMs;
        ledTimer.trigger = false;
        digitalWrite(LED_PIN, 0);
    }

    irTimer.currentMs = millis();

	if ((irTimer.currentMs - irTimer.prevMs) > IR_DEBOUNCE_MS && irrecv.decode(&irDecoded)) {

        if (!ledTimer.trigger) {
            ledTimer.trigger = true;
            digitalWrite(LED_PIN, 1);
        }
        Serial.print(resultToHumanReadableBasic(&irDecoded));

        String acDescription = IRAcUtils::resultAcToString(&irDecoded);
        if (acDescription.length()) {
            Serial.println(D_STR_MESGDESC ": " + acDescription);
        }
        // Serial.println("\nAs Source Code:");
        // Serial.println(resultToSourceCode(&irDecoded));
        Serial.println("-----------------------------------------------------------");

        resetDisplay();
        display.printf("TYPE:%s\n", typeToString(irDecoded.decode_type, irDecoded.repeat).c_str());
        display.printf("CMD:%d\n", irDecoded.command);
        display.printf("ADDR:%d BITS:%d\n", irDecoded.address, irDecoded.bits);
        display.printf("DATA:%s\n", resultToHexidecimal(&irDecoded).c_str());
        display.display();

        irrecv.resume();
    }
    delay(100);
}
