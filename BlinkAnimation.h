#ifndef __BLINK_ANIMATION_H__
#define __BLINK_ANIMATION_H__

#include "FastArduinoAnimationFramework.h"

struct BlinkAnimationStep : public AnimationStep {
	uint8_t aMs;
	uint8_t bMs;
};

void blinkAnimationStep(
	BlinkAnimationStep * step,
	CRGBPalette16& palette,
	uint16_t timeMs,
	uint16_t startLed,
	uint16_t endLed,
	CRGB* ledData,
	uint16_t ledCount
) {
	uint16_t cycleTime = step->aMs + step->bMs;
	uint16_t partTime = timeMs % cycleTime;

	CRGB color = ColorFromPalette(palette, partTime < step->aMs ? 0 : 127);

	CRGB* led = &ledData[startLed];
	for (uint16_t i=startLed; i<endLed; i++, led++) {
		*led = color;
	}
}

template<uint16_t transitionMs, const TProgmemRGBPalette16& palette, uint16_t durationMs, uint8_t repetitions, uint8_t aMs, uint8_t bMs>
AnimationStep* blinkAnimation() {
	static BlinkAnimationStep params;
	params.animationFunc = (AnimationSequenceStep) &blinkAnimationStep;
	params.commonParams = commonParams<transitionMs, palette, durationMs, repetitions>();
	params.aMs = aMs;
	params.bMs = bMs;

	return &params;
}

#endif