#ifndef __FAST_ARDUINO_ANIMATION_FRAMEWORK_H__
#define __FAST_ARDUINO_ANIMATION_FRAMEWORK_H__

#include <inttypes.h>
#include <FastLED.h>
#include <avr/pgmspace.h>

/**
 * Macros for packing millisecond values into 8-bit integers. Each second is represented as 8 units, allowing for a total
 * of 32 seconds to be represented. Used for animation durations, where that level of precision is acceptable.
 */
#define FAF_PACK_MS(ms) (uint8_t)((ms * 8)/1000)
#define FAF_UNPACK_MS(ms) (((uint16_t)ms * 1000)/8)

struct AnimationStep;
struct AnimationPlan;

typedef void (*BuildAnimationPalette)(
	CRGBPalette16& palette
);

template<const TProgmemRGBPalette16& palette> void usePalette(CRGBPalette16 &pal) {
	pal = palette;
}

template<const CRGB a, const CRGB b> void useColors(CRGBPalette16 &pal) {
	pal[0] = a;
	pal[1] = a;
	pal[2] = a;
	pal[3] = a;
	pal[4] = a;
	pal[5] = a;
	pal[6] = a;
	pal[7] = a;

	pal[8] = a;
	pal[9] = a;
	pal[10] = a;
	pal[11] = a;
	pal[12] = a;
	pal[13] = a;
	pal[14] = a;
	pal[15] = a;
}

typedef void (*AnimationSequenceStep)(
	AnimationStep* step,
	CRGBPalette16& palette,
	fract16 timeMs,
	uint16_t startLed,
	uint16_t endLed,
	CRGB* ledData,
	uint16_t ledCount
);

struct AnimationStepCommonParams {
	BuildAnimationPalette paletteFunc;

	uint8_t durationPackedMs;
	uint8_t transitionPackedMs;
	uint8_t repetitions;
};

struct AnimationStep {
	AnimationSequenceStep animationFunc;
	AnimationStepCommonParams* commonParams;

	inline uint16_t durationMs() {
		return FAF_UNPACK_MS(commonParams->durationPackedMs);
	}
	inline uint16_t transitionMs() {
		return FAF_UNPACK_MS(commonParams->transitionPackedMs);
	}
};

template<uint16_t transitionMs, const BuildAnimationPalette paletteFunc, uint16_t durationMs, uint8_t repetitions>
AnimationStepCommonParams* commonParams() {
	static AnimationStepCommonParams params = {
		.paletteFunc = paletteFunc,
		.durationPackedMs = FAF_PACK_MS(durationMs),
		.transitionPackedMs = FAF_PACK_MS(transitionMs),
		.repetitions = repetitions
	};

	return &params;
}

class LedAnimation {
public:
	LedAnimation(
		AnimationStep** steps,
		CRGB* ledData,
		uint16_t ledCount
	): steps(steps),
	   currentStepIndex(0),
	   ledData(ledData),
	   ledCount(ledCount)
	{
		nextStep(true);
	}

	void loop() {
		uint32_t now = millis();

		if (now >= currentStepEndMs) {
			nextStep(false);
		}

		uint16_t remainingMs = currentStepEndMs - now;

		AnimationStep* step = steps[currentStepIndex];

		if (now < transitionEndMs) {
			uint8_t transitionAmount = ((uint32_t)(step->transitionMs() - (transitionEndMs - millis())) << 8) / step->transitionMs();

			step->animationFunc(
				step,
				currentPalette,
				step->durationMs() - remainingMs,
				0,
				scale8(ledCount, transitionAmount),
				ledData,
				ledCount
			);

//			const uint8_t bufferSize = 16;
//			CRGB prevBuffer[bufferSize];
//			uint8_t chunkCount = ledCount/bufferSize + (ledCount%bufferSize==0 ? 0 : 1);
//
//			AnimationStep* oldStep = * prevStep;
//
//			uint16_t ledStart = 0;
//			for (uint8_t i=0; i<chunkCount; i++, ledStart += bufferSize) {
//				prevStepFunc(
//					oldStep,
//					prevPalette,
//					prevStepState,
//					oldStep->durationMs - remainingMs,
//					ledStart,
//					min(ledStart + bufferSize, ledCount),
//					ledData,
//					ledCount
//				);
//
//				for (uint16_t p = ledStart, j = 0; p < ledCount, j < bufferSize; p++, j++) {
//					prevBuffer[j] = ledData[p];
//				}
//
//				currentStepFunc(
//					step,
//					currentPalette,
//					currentStepState,
//					step->durationMs - remainingMs,
//					ledStart,
//					min(ledStart + bufferSize, ledCount),
//					ledData,
//				    ledCount
//				);
//
//				for (uint16_t p = ledStart, j = 0; p < ledCount, j < bufferSize; p++, j++) {
//					ledData[p] = prevBuffer[p].lerp8(ledData[j], transitionAmount);
//				}
//			}
		} else {
			step->animationFunc(
				step,
				currentPalette,
				step->durationMs() - remainingMs,
				0,
				ledCount,
				ledData,
				ledCount
			);
		}
	}

private:
	void nextStep(bool first) {
		if (remainingReps > 0 || (!first && currentStepIndex == 0 && !steps[currentStepIndex+1])) {
			currentStepEndMs = millis() + steps[currentStepIndex]->durationMs() - 1;
			remainingReps --;
		} else {
//			prevStep = currentStep;
//			prevPalette = currentPalette;
//			prevStepFunc = currentStepFunc;
//			memcpy8(prevStepState, currentStepState, animationStepStateSize);

			if (! first) {
				currentStepIndex++;
				if (!steps[currentStepIndex]) {
					currentStepIndex = 0;
				}
			}

			AnimationStep* step = steps[currentStepIndex];

			transitionEndMs = first ? 0 : (millis() + step->transitionMs());

			currentStepEndMs = millis() + step->durationMs();
			step->commonParams->paletteFunc(currentPalette);
			remainingReps = max(1, step->commonParams->repetitions) - 1;
		}
	}

private:
	AnimationStep** steps;

	CRGB* ledData;
	uint16_t ledCount;

	CRGBPalette16 currentPalette;
	uint8_t currentStepIndex;
	uint32_t currentStepEndMs = 0;
	uint32_t transitionEndMs = 0;
	uint8_t remainingReps = 0;

//	CRGBPalette16 prevPalette;
//	AnimationStep** prevStep = NULL;
//	AnimationSequenceStep prevStepFunc = NULL;
//	uint8_t prevStepState[animationStepStateSize];
};

#endif