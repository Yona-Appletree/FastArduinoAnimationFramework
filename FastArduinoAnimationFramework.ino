#include <FastLED.h>
#include "FastArduinoAnimationFramework.h"
#include "BlinkAnimation.h"
#include "FadeAnimation.h"
#include "SwipeAnimation.h"
#include "CylonAnimation.h"
#include "FireAnimation.h"
#include <colorpalettes.h>


CRGB strip1[150];
AnimationStep* steps1[] = {
	//blinkAnimation<400, ForestColors_p, 2000, 1, /* aMs */100, /* bMs */500>(),
	//fadeAnimation<400, RainbowColors_p, 2000, 1, /* reps */2>(),
	//fadeAnimation<200, RainbowStripeColors_p, 5000, 1, /* reps */1>(),
	//fadeAnimation<200, HeatColors_p, 5000, 1, /* reps */1>(),

	//      transition  color palette    time rep animation specific params
	swipeAnimation<500, RainbowColors_p, 1000, 1, /*ltr*/ false, /*color1*/255*0/6, /*color2*/255*1/6>(),
	swipeAnimation<  0, RainbowColors_p, 1000, 1, /*ltr*/ false, /*color1*/255*1/6, /*color2*/255*2/6>(),
	swipeAnimation<  0, RainbowColors_p, 1000, 1, /*ltr*/ false, /*color1*/255*2/6, /*color2*/255*3/6>(),
	swipeAnimation<  0, RainbowColors_p, 1000, 1, /*ltr*/ false, /*color1*/255*3/6, /*color2*/255*4/6>(),
	swipeAnimation<  0, RainbowColors_p, 1000, 1, /*ltr*/ false, /*color1*/255*4/6, /*color2*/255*5/6>(),
	swipeAnimation<  0, RainbowColors_p, 1000, 1, /*ltr*/ false, /*color1*/255*5/6, /*color2*/255*6/6>(),

	//fadeAnimation< 0,  ForestColors_p, 1000, 1, /* reps */1>(),
//	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(1*255)/6, /*flags*/CYLON_BOUNCE | CYLON_REVERSE | CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),
//	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(2*255)/6, /*flags*/CYLON_BOUNCE | CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),
//	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(3*255)/6, /*flags*/CYLON_BOUNCE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),
//	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(3*255)/6, /*flags*/CYLON_BOUNCE | CYLON_SHOW_PALETTE>(),
//	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(3*255)/6, /*flags*/CYLON_BOUNCE>(),
//	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(3*255)/6, /*flags*/CYLON_REVERSE | CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),
	cylonAnimation<500, RainbowColors_p, 2500, 1, /*swipes*/4, /*width*/255/2, /*color*/(3*255)/6, /*flags*/CYLON_FADE | CYLON_ROTATE_COLORS | CYLON_SHOW_PALETTE>(),
	fireAnimation< 500, HeatColors_p, 5000, 1, /*size*/64, /*cooling*/85, /*sparking*/64>(),
	NULL
};
LedAnimation animation1(steps1, strip1, 150);
//LedAnimation animation2(steps1, strip1+150, 150);
//LedAnimation animation3(steps1, strip1+300, 150);


//template<int s> struct CompileSizeOf;
//CompileSizeOf<sizeof(AnimationStep)> wow;

void setup() {
	Serial.begin(115200);
	FastLED.setCorrection(TypicalSMD5050);
	FastLED.addLeds<WS2811Controller800Khz, 3, GRB>(strip1, 150);
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