#include <FastLED.h>
#include "FastArduinoAnimationFramework.h"
#include "BlinkAnimation.h"
#include "FadeAnimation.h"
#include <colorpalettes.h>

CRGB strip1[450];
AnimationPlanStep* steps1[] = {
	blinkAnimation</* transition */400, ForestColors_p, /* duration */2000, /* repetitions */1, /* aMs */100, /* bMs */500>(),
	fadeAnimation</* transition */500, ForestColors_p, /* duration */4000, /* repetitions */1, /* reps */2>(),
	fadeAnimation</* transition */1500, RainbowColors_p, /* duration */5000, /* repetitions */1, /* reps */3>(),
	fadeAnimation</* transition */2500, PartyColors_p, /* duration */6000, /* repetitions */1, /* reps */1>(),
    NULL
};
LedAnimation animation1(steps1, strip1, 150);
LedAnimation animation2(steps1, strip1+150, 150);
LedAnimation animation3(steps1, strip1+300, 150);

//template<int s> struct CompileSizeOf;
//CompileSizeOf<sizeof(AnimationPlanStep)> wow;

void setup() {
	Serial.begin(115200);
	FastLED.setCorrection(TypicalSMD5050);
	FastLED.addLeds<WS2811Controller800Khz, 3, RBG>(strip1, 150);
	FastLED.addLeds<WS2811Controller800Khz, 4, RBG>(strip1+150, 150);
	FastLED.addLeds<WS2811Controller800Khz, 5, RBG>(strip1+300, 150);
}

uint8_t c = 0;
void loop() {
	animation1.loop();
	animation2.loop();
	animation3.loop();

	FastLED.show();
	if (c++ == 0) Serial.println(FastLED.getFPS());
}