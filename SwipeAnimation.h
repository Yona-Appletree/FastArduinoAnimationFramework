#ifndef __Swipe_ANIMATION_H__
#define __Swipe_ANIMATION_H__

#include "FastArduinoAnimationFramework.h"

enum SwipeAnimationMode {
	SolidSwipeLeftToRight,
	SolidSwipeRightToLeft,
	GradientSwipeIn,
	GradientSwipeOut,
};

struct SwipeAnimationStep : public AnimationStep {
	SwipeAnimationMode mode;
	uint8_t color1;
	uint8_t color2;
};

void swipeAnimationStep(
	SwipeAnimationStep* step,
	CRGBPalette16& palette,
	uint16_t timeMs,
	uint16_t startLed,
	uint16_t endLed,
	CRGB* ledData,
    uint16_t ledCount
) {
	uint16_t durationMs = step->durationMs();
	uint8_t startFrac = ((uint32_t)timeMs<<8) / durationMs;

	if (step->mode == SolidSwipeRightToLeft || step->mode == GradientSwipeOut)
		startFrac = 255 - startFrac;

	uint8_t changeLed = scale8(ledCount, startFrac)+1;


	if (step->mode == SolidSwipeLeftToRight || step->mode == SolidSwipeRightToLeft) {
		CRGB color1 = ColorFromPalette(palette, step->color1);
		CRGB color2 = ColorFromPalette(palette, step->color2);

		CRGB *led = ledData + startLed;
		for (uint16_t i = startLed; i < endLed; i++, led++) {
			*led = i < changeLed ? color2 : color1;
		}
	} else {
		CRGB *led = ledData + startLed;
		for (uint16_t i = startLed; i < endLed; i++, led++) {
			*led = i < changeLed ? ColorFromPalette(palette, i*255/ledCount+step->color1) : CRGB::Black;
		}
	}
}

template<
	uint16_t transitionMs,
	AnimationPalettePopulator paletteFunc,
	uint16_t durationMs,
	uint8_t repetitions,
	SwipeAnimationMode mode,
	uint8_t color1,
	uint8_t color2
>
SwipeAnimationStep* swipeAnimation() {
	static SwipeAnimationStep params;

	params.animationFunc = (AnimationSequenceStep) &swipeAnimationStep;
	params.commonParams = commonParams<transitionMs, paletteFunc, durationMs, repetitions>();
	params.mode = mode;
	params.color1 = color1;
	params.color2 = color2;

	return &params;
}

#endif