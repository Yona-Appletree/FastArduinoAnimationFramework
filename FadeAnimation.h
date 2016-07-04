#ifndef __Fade_ANIMATION_H__
#define __Fade_ANIMATION_H__

#include "FastArduinoAnimationFramework.h"

struct FadeAnimationParams {
	uint8_t cycles;
};

void fadeAnimationStep(
	AnimationPlanStep* step,
	CRGBPalette16& palette,
	void* state,
	uint16_t timeMs,
	uint16_t startLed,
	uint16_t endLed,
	CRGB* ledData,
    uint16_t ledCount
) {
	FadeAnimationParams* params = (FadeAnimationParams*) step->animationParams;

	CRGB* led = &ledData[startLed];

	if (params->cycles == 0) {
		CRGB color = ColorFromPalette(palette, ((uint32_t)timeMs<<8) / step->durationMs);
		for (uint16_t i = startLed; i < endLed; i++, led++) {
			*led = color;
		}
	} else {
		uint8_t startFrac = ((uint32_t)timeMs<<8) / step->durationMs;

		for (uint16_t i = startLed; i < endLed; i++, led++) {
			*led = ColorFromPalette(palette, startFrac + (((uint32_t)i << 8)/ ledCount) * params->cycles);
		}
	}
}

AnimationSequenceStep fadeAnimationSetup(
	AnimationPlanStep* stepInfo,
	void* state
) {
	return &fadeAnimationStep;
}


template<uint16_t transitionMs, const TProgmemRGBPalette16& palette, uint16_t durationMs, uint8_t repetitions, uint8_t cycles>
AnimationPlanStep* fadeAnimation() {
	static FadeAnimationParams params = {
		.cycles = cycles
	};

	static AnimationPlanStep step = {
		.animationFunc = &fadeAnimationSetup,
		.animationParams = &params,
		.palette = palette,
		.durationMs = durationMs,
		.transitionMs = transitionMs,
		.repetitions = repetitions
	};

	return &step;
}

#endif