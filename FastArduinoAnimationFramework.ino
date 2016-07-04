#include <FastLED.h>
#include "FastArduinoAnimationFramework.h"
#include "BlinkAnimation.h"
#include "FadeAnimation.h"
#include "SwipeAnimation.h"
#include "CylonAnimation.h"
#include <colorpalettes.h>


CRGB strip1[150];
AnimationStep* steps1[] = {
	//blinkAnimation<400, ForestColors_p, 2000, 1, /* aMs */100, /* bMs */500>(),
	//fadeAnimation<400, RainbowColors_p, 2000, 1, /* reps */2>(),
	//fadeAnimation<200, RainbowStripeColors_p, 5000, 1, /* reps */1>(),
	//fadeAnimation<200, HeatColors_p, 5000, 1, /* reps */1>(),
//	swipeAnimation<500, RainbowColors_p, 1000, 1, false, (0*255)/6, (1*255)/6>(),
//	swipeAnimation<  0, RainbowColors_p, 1000, 1, false, (1*255)/6, (2*255)/6>(),
//	swipeAnimation<  0, RainbowColors_p, 1000, 1, false, (2*255)/6, (3*255)/6>(),
//	swipeAnimation<  0, RainbowColors_p, 1000, 1, false, (3*255)/6, (4*255)/6>(),
//	swipeAnimation<  0, RainbowColors_p, 1000, 1, false, (4*255)/6, (5*255)/6>(),
//	swipeAnimation<  0, RainbowColors_p, 1000, 1, false, (5*255)/6, (6*255)/6>(),
	//fadeAnimation< 0,  ForestColors_p, 1000, 1, /* reps */1>(),
	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(1*255)/6, /*flags*/CYLON_BOUNCE | CYLON_REVERSE | CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),
	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(2*255)/6, /*flags*/CYLON_BOUNCE | CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),
	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(3*255)/6, /*flags*/CYLON_BOUNCE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),
	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(3*255)/6, /*flags*/CYLON_BOUNCE | CYLON_SHOW_PALETTE>(),
	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(3*255)/6, /*flags*/CYLON_BOUNCE>(),
	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(3*255)/6, /*flags*/CYLON_REVERSE | CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),
	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(3*255)/6, /*flags*/CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),

	NULL
};
LedAnimation animation1(steps1, strip1, 150);
//LedAnimation animation2(steps1, strip1+150, 150);
//LedAnimation animation3(steps1, strip1+300, 150);


//template<int s> struct CompileSizeOf;
//CompileSizeOf<sizeof(AnimationStep)> wow;

void setup() {
	FastLED.setCorrection(TypicalSMD5050);
	FastLED.addLeds<WS2811Controller800Khz, 3, RBG>(strip1, 150);
//	FastLED.addLeds<WS2811Controller800Khz, 4, RBG>(strip1+150, 150);
//	FastLED.addLeds<WS2811Controller800Khz, 5, RBG>(strip1+300, 150);
}

uint8_t c = 0;
void loop() {
	animation1.loop();
	//animation2.loop();
	//animation3.loop();

	FastLED.show();
}