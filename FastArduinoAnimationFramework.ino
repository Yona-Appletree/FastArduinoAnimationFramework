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
#include <colorpalettes.h>

#define LED_COUNT 28

CRGB strip1[LED_COUNT]; // Right Eye

Button fadeButton(12, true, false, 20);
Button paletteButton(6, true, false, 20);

AnimationStep* testSteps[] = {
	fadeAnimation<1000, &paletteFromSet, 5000, 1, /* reps */1>(),
	fadeAnimation<1000, &paletteFromSet, 7000, 1, /* reps */1>(),
	fadeAnimation<1000, &paletteFromSet, 8000, 1, /* reps */1>(),
	NULL
};
LedAnimation animation1(testSteps, strip1, LED_COUNT, 0);

//template<int s> struct CompileSizeOf;
//CompileSizeOf<sizeof(AnimationStep)> wow;

void setup() {
	FastLED.setCorrection(TypicalSMD5050);

	FastLED.addLeds<WS2811Controller800Khz, 10, GRB>(strip1, LED_COUNT);
	FastLED.setMaxRefreshRate(30, true);
}

uint8_t brightnessIndex = 2;
uint8_t brightnesses[] = {
	0, 64, 128
};

void checkButtons() {
	fadeButton.read();
	paletteButton.read();

	if (fadeButton.wasReleased() || fadeButton.wasPressed()) {
		brightnessIndex++;
	}

	if (paletteButton.wasReleased() || paletteButton.wasPressed()) {
		if (brightnessIndex == 0) {
			brightnessIndex ++;
		} else {
			nextPaletteSet();
			animation1.nextStep(false);
		}
	}

	if (brightnessIndex >= sizeof(brightnesses)) {
		brightnessIndex = 0;
	}

	FastLED.setDither(BINARY_DITHER);
}

void loop() {
	checkButtons();
	animation1.loop();

	FastLED.setBrightness(brightnesses[brightnessIndex]);
	FastLED.show();
	FastLED.delay(30);
}