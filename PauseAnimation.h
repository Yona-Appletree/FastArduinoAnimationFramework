#ifndef __Pause_ANIMATION_H__
#define __Pause_ANIMATION_H__

#include "FastArduinoAnimationFramework.h"

void pauseAnimationStep(
	AnimationStep* step,
	CRGBPalette16& palette,
	uint16_t timeMs,
	uint16_t startLed,
	uint16_t endLed,
	CRGB* ledData,
    uint16_t ledCount
) {}

void nopPalette(CRGBPalette16 &pal) {}

template<uint16_t durationMs> AnimationStep* pauseAnimation() {
	static AnimationStep params;

	params.animationFunc = &pauseAnimationStep;
	params.commonParams = commonParams<0, &nopPalette, durationMs, 1>();

	return &params;
}


#endif