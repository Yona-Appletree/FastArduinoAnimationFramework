#ifndef __Cylon_ANIMATION_H__
#define __Cylon_ANIMATION_H__

#include "FastArduinoAnimationFramework.h"

#define CYLON_BOUNCE (1<<0)
#define CYLON_FADE (1<<1)
#define CYLON_ROTATE_COLORS (1<<2)
#define CYLON_SHOW_PALETTE (1<<3)
#define CYLON_REVERSE (1<<4)

struct CylonAnimationStep : public AnimationStep {
	uint8_t swipes;
	uint8_t width;
	uint8_t color;

	uint8_t flags;
};

void cylonAnimationStep(
	CylonAnimationStep* step,
	CRGBPalette16& palette,
	uint16_t timeMs,
	uint16_t startLed,
	uint16_t endLed,
	CRGB* ledData,
    uint16_t ledCount
) {
	bool bounceFlag = (step->flags & CYLON_BOUNCE) != 0;
	bool fadeFlag = (step->flags & CYLON_FADE) != 0;
	bool rotateColorsFlag = (step->flags & CYLON_ROTATE_COLORS) != 0;
	bool showPaletteFlag = (step->flags & CYLON_SHOW_PALETTE) != 0;

	uint8_t timeFrac = (((uint32_t)timeMs*255) / step->durationMs());

	uint8_t baseBarFrac = bounceFlag
		? cos8((uint16_t)timeFrac * step->swipes / 2)
		: (uint16_t)timeFrac * step->swipes / 2;

	if (step->flags & CYLON_REVERSE) {
		baseBarFrac = 255 - baseBarFrac;
	}

	uint8_t barCenterFrac = bounceFlag
		? step->width / 2 + scale8(255 - step->width, baseBarFrac)
		: baseBarFrac;

	uint16_t barLedCount = scale16by8(ledCount, step->width);
	uint16_t centerBarLed = scale16by8(ledCount + (bounceFlag ? 0 : barLedCount*2), barCenterFrac);

	uint16_t firstBarLed = centerBarLed - min(centerBarLed, barLedCount/2);
	uint16_t lastBarLed = centerBarLed + barLedCount/2;

	int16_t barCenterLedShift = bounceFlag ? 0 : barLedCount/2;

	CRGB* led = ledData + startLed;
	for (int16_t i=startLed; i<endLed; i++, led++) {
		int16_t b = i + barCenterLedShift;

		if (b >= firstBarLed && b <= lastBarLed) {
			uint8_t colorIndex = step->color;

			if (rotateColorsFlag) {
				colorIndex += timeFrac;
			}

			if (showPaletteFlag) {
				colorIndex += i * 255 / ledCount;
			}

			CRGB color = ColorFromPalette(palette, colorIndex);

			if (fadeFlag) {
				color.fadeToBlackBy(abs((int32_t)b - centerBarLed) * 255 / (barLedCount/2));
			}

			*led = color;
		} else {
			*led = CRGB::Black;
		}
	}
}

template<
	uint16_t transitionMs,
	BuildAnimationPalette paletteFunc,
	uint16_t durationMs,
	uint8_t repetitions,
	uint8_t swipes,
	uint8_t width,
	uint8_t color,
	uint8_t flags
>
CylonAnimationStep* cylonAnimation() {
	static CylonAnimationStep params;

	params.animationFunc = (AnimationSequenceStep) &cylonAnimationStep;
	params.commonParams = commonParams<transitionMs, paletteFunc, durationMs, repetitions>();
	params.swipes = swipes;
	params.width = width;
	params.color = color;
	params.flags = flags;

	return &params;
}

#endif