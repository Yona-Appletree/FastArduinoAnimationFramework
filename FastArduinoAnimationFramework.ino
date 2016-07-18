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

//#define SMALL_PEDALS
#define ORANGE_PEDALS
//#define WHITE_PEDALS

// USB 20 - Orange Pedals
// USB 30 - White Pedals
// USB 40 - Small and Stamen


#ifdef SMALL_PEDALS
CRGB strip1[150]; // Small Pedals
CRGB strip2[120];  // Stamen 1
CRGB strip3[120];  // Stamen 2
#else
CRGB strip1[150]; // Right Eye
CRGB strip2[150]; // Body
CRGB strip3[150]; // Left Eye
#endif


AnimationStep* stamenBallSteps[] = {
	fadeAnimation<2000, &orangePedalPalette, 10000, 1, /* reps */1>(),
	fadeAnimation<2000, &orangePedalPalette, 12000, 1, /* reps */2>(),

//	cylonAnimation<1000, &randomPalette, 7000, 1, /*swipes*/12, /*width*/255*3/4, /*color*/(1*255)/6, /*flags*/CYLON_FADE | CYLON_ROTATE_COLORS>(),
	NULL
};

AnimationStep* stamenSteps[] = {
	fadeAnimation<2000, &randomPalette, 10000, 1, /* reps */1>(),
	fadeAnimation<2000, &randomPalette, 12000, 1, /* reps */1>(),
	fadeAnimation<2000, &randomPalette, 7000, 1, /* reps */0>(),

//	cylonAnimation<1000, &randomPalette, 7000, 1, /*swipes*/12, /*width*/255*3/4, /*color*/(1*255)/6, /*flags*/CYLON_FADE | CYLON_ROTATE_COLORS>(),
	NULL
};


AnimationStep* greenSteps[] = {
	fadeAnimation<4000, &greenPedalPalette, 12000, 1, /* reps */1>(),
	fadeAnimation<6000, &greenPedalPalette, 17000, 1, /* reps */3>(),
	fadeAnimation<3000, &greenPedalPalette, 13000, 1, /* reps */2>(),

//	cylonAnimation<1000, &greenPedalPalette, 7000, 1, /*swipes*/12, /*width*/255*3/4, /*color*/(1*255)/6, /*flags*/CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),
	NULL
};

////////////////////////////////////////

AnimationStep* whiteSteps[] = {
	fadeAnimation<4000, &randomPalette, 10000, 1, /* reps */0>(),
	fadeAnimation<3000, &randomPalette, 9000, 1, /* reps */1>(),
	fadeAnimation<3000, &randomPalette, 8000, 1, /* reps */2>(),

	//cylonAnimation<2000, &randomPalette, 5000, 1, /*swipes*/4, /*width*/255*1/2, /*color*/(1*255)/6, /*flags*/CYLON_FADE | CYLON_ROTATE_COLORS>(),
	NULL
};

AnimationStep* orangeSteps[] = {
	//blinkAnimation<400, &usePalette<ForestColors_p>, 2000, 1, /* aMs */100, /* bMs */500>(),
	//fadeAnimation<400, &usePalette<RainbowColors_p>, 2000, 1, /* reps */2>(),
	//fadeAnimation<200, &usePalette<RainbowStripeColors_p>, 5000, 1, /* reps */1>(),
	//fadeAnimation<200, &usePalette<HeatColors_p>, 5000, 1, /* reps */1>(),

	//      transition  color &usePalette<   time rep animation specific params

//	swipeAnimation<1000, &randomPalette, 5000, 1, GradientSwipeIn, 0, 16>(),
//    pauseAnimation<1000>(),
//	swipeAnimation<1000, &randomPalette, 5000, 1, GradientSwipeOut, 0, 16>(),

	fadeAnimation<5000, &orangePedalPalette, 10000, 1, /* reps */0>(),
	fadeAnimation<8000, &orangePedalPalette, 16000, 1, /* reps */2>(),
	fadeAnimation<7000, &orangePedalPalette, 14000, 1, /* reps */1>(),

//	cylonAnimation<1000, &orangePedalPalette, 10000, 1, /*swipes*/12, /*width*/255/2, /*color*/(1*255)/6, /*flags*/CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),
//	cylonAnimation<1000, &orangePedalPalette, 10000, 1, /*swipes*/9, /*width*/255/2, /*color*/(1*255)/6, /*flags*/CYLON_BOUNCE | CYLON_FADE | CYLON_ROTATE_COLORS>(),
//	cylonAnimation<1000, &orangePedalPalette, 10000, 1, /*swipes*/7, /*width*/255/2, /*color*/(1*255)/6, /*flags*/CYLON_REVERSE | CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),

	//fadeAnimation<1000, &randomPalette, 7000, 2, /* reps */1>(),

//	fireAnimation< 500, &usePalette<HeatColors_p>, 10000, 1, /*size*/32, /*cooling*/85, /*sparking*/64>(),
//	fireAnimation< 500, &usePalette<ForestColors_p>, 5000, 1, /*size*/32, /*cooling*/50, /*sparking*/90>(),
	NULL
};
#ifdef SMALL_PEDALS
LedAnimation animation1(greenSteps, strip1, 150, 0); // Small Pedals
LedAnimation animation2(stamenSteps, strip2, 110, 1); // Stamen 1
LedAnimation animation3(stamenSteps, strip3, 110, 2); // Stamen 2

LedAnimation animation4(stamenBallSteps, strip2+110, 10, 0); // Stamen 1
LedAnimation animation5(stamenBallSteps, strip3+110, 10, 1); // Stamen 2
#elif defined(WHITE_PEDALS)
LedAnimation animation1(whiteSteps, strip1, 150, 0);
LedAnimation animation2(whiteSteps, strip2, 150, 0);
LedAnimation animation3(whiteSteps, strip3, 150, 0);
#elif defined(ORANGE_PEDALS)
LedAnimation animation1(orangeSteps, strip1, 150, 0);
LedAnimation animation2(orangeSteps, strip2, 150, 1);
LedAnimation animation3(orangeSteps, strip3, 150, 2);
#endif


//template<int s> struct CompileSizeOf;
//CompileSizeOf<sizeof(AnimationStep)> wow;

void setup() {
	FastLED.setCorrection(TypicalSMD5050);

	FastLED.setBrightness(64);

#ifdef SMALL_PEDALS
	FastLED.addLeds<WS2811Controller800Khz, 2, GRB>(strip1, 150);
	FastLED.addLeds<WS2811Controller800Khz, 4, GRB>(strip2, 120);
	FastLED.addLeds<WS2811Controller800Khz, 5, GRB>(strip3, 120);
#else
	FastLED.addLeds<WS2811Controller800Khz, 2, GRB>(strip1, 150);
	FastLED.addLeds<WS2811Controller800Khz, 4, GRB>(strip2, 150);
	FastLED.addLeds<WS2811Controller800Khz, 5, GRB>(strip3, 150);
#endif

	FastLED.setMaxRefreshRate(30, true);
}

uint8_t c = 0;
void loop() {
	animation1.loop();
	animation2.loop();
	animation3.loop();

#ifdef SMALL_PEDALS
	animation4.loop();
	animation5.loop();
#endif

#if defined(ORANGE_PEDALS) || defined(WHITE_PEDALS)
	mirrorLeds(strip1, 0, 75);
	mirrorLeds(strip2, 0, 75);
	mirrorLeds(strip3, 0, 75);
#endif

//	for (uint8_t i=0; i<150; i++) {
//		strip1[i] = CRGB::Red;
//		strip2[i] = CRGB::Green;
//		strip3[i] = CRGB::Blue;
//	}

	FastLED.show();
}