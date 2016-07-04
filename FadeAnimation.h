#ifndef __Fade_ANIMATION_H__
#define __Fade_ANIMATION_H__

#include "FastArduinoAnimationFramework.h"

struct FadeAnimationStep : public AnimationStep {
	uint8_t cycles;
};

void fadeAnimationStep(
	FadeAnimationStep* step,
	CRGBPalette16& palette,
	void* state,
	uint16_t timeMs,
	uint16_t startLed,
	uint16_t endLed,
	CRGB* ledData,
    uint16_t ledCount
) {
	uint16_t durationMs = step->durationMs();

	CRGB* led = &ledData[startLed];

	if (step->cycles == 0) {
		CRGB color = ColorFromPalette(palette, ((uint32_t)timeMs<<8) / durationMs);
		for (uint16_t i = startLed; i < endLed; i++, led++) {
			*led = color;
		}
	} else {
		uint8_t startFrac = ((uint32_t)timeMs<<8) / durationMs;

		for (uint16_t i = startLed; i < endLed; i++, led++) {
			*led = ColorFromPalette(palette, startFrac + (((uint32_t)i << 8)/ ledCount) * step->cycles);
		}
	}
}

AnimationSequenceStep fadeAnimationSetup(
	AnimationStep* stepInfo,
	void* state
) {
	return (AnimationSequenceStep) &fadeAnimationStep;
}


template<uint16_t transitionMs, const TProgmemRGBPalette16& palette, uint16_t durationMs, uint8_t repetitions, uint8_t cycles>
FadeAnimationStep* fadeAnimation() {
	static FadeAnimationStep params;

	params.animationFunc = &fadeAnimationSetup;
	params.commonParams = commonParams<transitionMs, palette, durationMs, repetitions>();
	params.cycles = cycles;

	return &params;
}

#endif