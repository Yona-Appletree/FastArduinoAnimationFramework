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

#define BODY_LED_COUNT 120
#define BASKET_LED_COUNT 60
#define AUX_LED_COUNT 20

#define MODE_SWITCH_PIN 2
#define COLOR_SWITCH_PIN 3
#define BRIGHT_SWITCH_PIN 4

CRGB strip1[BODY_LED_COUNT]; // Body and Handlebars
CRGB strip2[BASKET_LED_COUNT]; // Basket
CRGB strip3[AUX_LED_COUNT]; // Unused

Button modeButton(MODE_SWITCH_PIN, true, true, 100);
Button colorButton(COLOR_SWITCH_PIN, true, true, 100);
Button brightButton(BRIGHT_SWITCH_PIN, true, true, 100);

template <AnimationStep* ... steps> AnimationStep** animationArray() {
	static AnimationStep* values[sizeof...(steps) + 1] = { steps..., NULL };
}

AnimationStep* fadeSteps[] = {
	fadeAnimation<1000, &paletteFromSet, 10000, 1, /* reps */1>(),
	fadeAnimation<1000, &paletteFromSet, 10000, 1, /* reps */1>(),
	NULL
};

AnimationStep* cylonSteps[] = {
	cylonAnimation<1000, &paletteFromSet, 5000, 1, /*swipes*/10, /*width*/255/3, /*color*/(1*255)/6, /*flags*/CYLON_BOUNCE | CYLON_SHOW_PALETTE>(),
	cylonAnimation<1000, &paletteFromSet, 10000, 1, /*swipes*/8, /*width*/255/3, /*color*/(1*255)/6, /*flags*/CYLON_ROTATE_COLORS | CYLON_FADE>(),
	cylonAnimation<1000, &paletteFromSet, 10000, 1, /*swipes*/20, /*width*/255/3, /*color*/(1*255)/6, /*flags*/CYLON_REVERSE | CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),
	NULL
};

AnimationStep* fireSteps[] = {
	fireAnimation< 1000, &paletteFromSet, 10000, 1, /*size*/64, /*cooling*/85, /*sparking*/64>(),
	NULL
};

uint8_t stepSetIndex = 0;
AnimationStep** stepSets[] = {
	fadeSteps,
	cylonSteps,
	fireSteps,
	NULL
};

LedAnimation animation1(fadeSteps, strip1, BODY_LED_COUNT, 0);
LedAnimation animation2(fadeSteps, strip2, BASKET_LED_COUNT, 0);
LedAnimation animation3(fadeSteps, strip3, AUX_LED_COUNT, 0);

//template<int s> struct CompileSizeOf;
//CompileSizeOf<sizeof(AnimationStep)> wow;

uint8_t brightnessIndex = 2;
uint8_t brightnesses[] = {
	0, 32, 255
};

void setup() {
	pinMode(0, OUTPUT);

	FastLED.setCorrection(TypicalSMD5050);
	//FastLED.addLeds<APA102, SPI_DATA, SPI_CLOCK, GRB, DATA_RATE_MHZ(8)>(strip1, LED_COUNT);
	FastLED.addLeds<WS2811Controller800Khz, 6, GRB>(strip1, BODY_LED_COUNT);
	FastLED.addLeds<WS2811Controller800Khz, 7, GRB>(strip1, BASKET_LED_COUNT);
	FastLED.addLeds<WS2811Controller800Khz, 8, GRB>(strip1, AUX_LED_COUNT);

	FastLED.setDither(BINARY_DITHER);

	Serial.begin(115200);
	Serial.println("START");
}

void checkButtons();
void loop() {
	uint32_t start = millis();

	checkButtons();
	FastLED.setBrightness(brightnesses[brightnessIndex]);

	animation1.loop();
	animation2.loop();
	animation3.loop();
	FastLED.show();

	uint32_t duration = millis() - start;
	FastLED.delay(duration > 33 ? 0 : 33 - duration);
}

void checkButtons() {
	modeButton.read();
	colorButton.read();
	brightButton.read();

	if (brightButton.wasReleased()) Serial.println("Bright Pressed");
	if (colorButton.wasReleased()) Serial.println("Color Pressed");
	if (modeButton.wasReleased()) Serial.println("Mode Pressed");

	if (brightButton.wasReleased()) {
		brightnessIndex++;
	}

	if (colorButton.wasReleased()) {
		if (brightnessIndex == 0) {
			brightnessIndex ++;
		} else {
			nextPaletteSet();
			animation1.updatePalette();
		}
	}

	if (modeButton.wasReleased()) {
		if (brightnessIndex == 0) {
			brightnessIndex ++;
		} else {
			stepSetIndex ++;
			if (! stepSets[stepSetIndex]) {
				stepSetIndex = 0;
			}
			animation1.setSteps(stepSets[stepSetIndex]);
			animation2.setSteps(stepSets[stepSetIndex]);
			animation3.setSteps(stepSets[stepSetIndex]);
		}
	}

	if (brightnessIndex >= sizeof(brightnesses)) {
		brightnessIndex = 0;
	}
}