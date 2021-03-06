#include <FastLED.h>
#include "FastArduinoAnimationFramework.h"
#include "BlinkAnimation.h"
#include "FadeAnimation.h"
#include "SwipeAnimation.h"
#include "CylonAnimation.h"
#include "FireAnimation.h"
#include "PauseAnimation.h"
#include "cptPalettes.h"
#include <colorpalettes.h>

#define LED_COUNT 5

CRGB strip1[LED_COUNT]; // Right Eye

AnimationStep* testSteps[] = {
	//blinkAnimation<400, &usePalette<ForestColors_p>, 2000, 1, /* aMs */100, /* bMs */500>(),
	//fadeAnimation<400, &usePalette<RainbowColors_p>, 2000, 1, /* reps */2>(),
	//fadeAnimation<200, &usePalette<RainbowStripeColors_p>, 5000, 1, /* reps */1>(),
	//fadeAnimation<200, &usePalette<HeatColors_p>, 5000, 1, /* reps */1>(),

	//      transition  color &usePalette<   time rep animation specific params

//	swipeAnimation<1000, &randomPalette, 5000, 1, GradientSwipeIn, 0, 16>(),
//    pauseAnimation<1000>(),
//	swipeAnimation<1000, &randomPalette, 5000, 1, GradientSwipeOut, 0, 16>(),

	fadeAnimation<1000, &randomPalette, 5000, 1, /* reps */1>(),
	//fadeAnimation<1000, &randomPalette, 3000, 1, /* reps */3>(),
	//fadeAnimation<1000, &randomPalette, 5000, 1, /* reps */2>(),

	cylonAnimation<1000, &randomPalette, 5000, 1, /*swipes*/10, /*width*/255/2, /*color*/(1*255)/6, /*flags*/CYLON_BOUNCE | CYLON_SHOW_PALETTE>(),
	cylonAnimation<1000, &randomPalette, 5000, 1, /*swipes*/8, /*width*/255/2, /*color*/(1*255)/6, /*flags*/CYLON_ROTATE_COLORS>(),
//	cylonAnimation<1000, &owlEyePalette, 10000, 1, /*swipes*/20, /*width*/255/2, /*color*/(1*255)/6, /*flags*/CYLON_REVERSE | CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),

	//fadeAnimation<1000, &randomPalette, 7000, 2, /* reps */1>(),

//	fireAnimation< 500, &usePalette<HeatColors_p>, 10000, 1, /*size*/32, /*cooling*/85, /*sparking*/64>(),
//	fireAnimation< 500, &usePalette<ForestColors_p>, 5000, 1, /*size*/32, /*cooling*/50, /*sparking*/90>(),
	NULL
};
LedAnimation animation1(testSteps, strip1, LED_COUNT, 0);


//template<int s> struct CompileSizeOf;
//CompileSizeOf<sizeof(AnimationStep)> wow;

void setup() {
	FastLED.setCorrection(TypicalSMD5050);

	//FastLED.setBrightness(64);

	FastLED.addLeds<WS2811Controller800Khz, 3, GRB>(strip1, LED_COUNT);

	FastLED.setMaxRefreshRate(30, true);
}

uint8_t c = 0;
void loop() {
	animation1.loop();

//	strip1[74] = CRGB::Red;
//	strip2[74] = CRGB::Red;
//	strip3[74] = CRGB::Red;

//	mirrorLeds(st

//	for (uint8_t i=0; i<150; i++) {
//		strip1[i] = CRGB::Red;
//		strip2[i] = CRGB::Green;
//		strip3[i] = CRGB::Blue;
//	}

	FastLED.show();
}