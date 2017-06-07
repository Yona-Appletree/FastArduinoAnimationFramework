#include <FastLED.h>
#include "FastArduinoAnimationFramework.h"
#include "BlinkAnimation.h"
#include "FadeAnimation.h"
#include "SwipeAnimation.h"
#include "CylonAnimation.h"
#include "FireAnimation.h"
#include "PauseAnimation.h"
#include "cptPalettes.h"
#include "Button.h"

#define LED_COUNT 200

#define MODE_SWITCH_PIN 2
#define COLOR_SWITCH_PIN 3
#define BRIGHT_SWITCH_PIN 4

CRGB strip1[LED_COUNT];

AnimationStep* fadeSteps[] = {
	fadeAnimation<0, &paletteFromSet, /* dur */ 2000, /* reps */ 3, /* cycles */8, /* frac */ 255>(),
	NULL
};

LedAnimation animation1(fadeSteps, strip1, LED_COUNT, 0);
//LedAnimation animation2(fadeSteps, strip1+60, 31, 0);
//LedAnimation animation2(fadeSteps, strip2, LED_COUNT, 0);

uint8_t brightnessIndex = 2;
uint8_t brightnesses[] = {
	0, 32, 255
};

void setup() {
	pinMode(0, OUTPUT);

	FastLED.setCorrection(TypicalSMD5050);
	//FastLED.addLeds<APA102, SPI_DATA, SPI_CLOCK, GRB, DATA_RATE_MHZ(8)>(strip1, LED_COUNT);
	FastLED.addLeds<WS2811Controller800Khz, 3, GRB>(strip1, LED_COUNT);
	//FastLED.addLeds<WS2811Controller800Khz, 5, GRB>(strip1, LED_COUNT);

	FastLED.setDither(BINARY_DITHER);
	FastLED.setBrightness(255);

	Serial.begin(115200);
	Serial.println("START");
}

void checkButtons();
void loop() {
	uint32_t start = millis();

	FastLED.setBrightness(brightnesses[brightnessIndex]);

	animation1.loop();
	//animation2.loop();
	FastLED.show();

	uint32_t duration = millis() - start;
	FastLED.delay(duration > 33 ? 0 : 33 - duration);
}
