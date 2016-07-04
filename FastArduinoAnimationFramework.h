#ifndef __FAST_ARDUINO_ANIMATION_FRAMEWORK_H__
#define __FAST_ARDUINO_ANIMATION_FRAMEWORK_H__

#include <inttypes.h>
#include <FastLED.h>
#include <avr/pgmspace.h>

const int animationStepStateSize = 4;

struct AnimationPlanStep;
struct AnimationPlan;

typedef void (*AnimationSequenceStep)(
	AnimationPlanStep* step,
	CRGBPalette16& palette,
	void* state,
	fract16 timeMs,
	uint16_t startLed,
	uint16_t endLed,
	CRGB* ledData,
	uint16_t ledCount
);
typedef AnimationSequenceStep (*AnimationSequenceSetup)(AnimationPlanStep* stepInfo, void* state);


struct AnimationPlanStep {
	AnimationSequenceSetup animationFunc;
	void* animationParams;
	const TProgmemRGBPalette16& palette;

	uint16_t durationMs;
	uint16_t transitionMs;
	uint8_t repetitions;
};



class LedAnimation {
public:
	LedAnimation(
		AnimationPlanStep** steps,
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

		AnimationPlanStep* step = steps[currentStepIndex];

		if (now < transitionEndMs) {
			uint8_t transitionAmount = ((uint32_t)(step->transitionMs - (transitionEndMs - millis())) << 8) / step->transitionMs;

			currentStepFunc(
				step,
				currentPalette,
				currentStepState,
				step->durationMs - remainingMs,
				0,
				scale8(ledCount, transitionAmount),
				ledData,
				ledCount
			);

//			const uint8_t bufferSize = 16;
//			CRGB prevBuffer[bufferSize];
//			uint8_t chunkCount = ledCount/bufferSize + (ledCount%bufferSize==0 ? 0 : 1);
//
//			AnimationPlanStep* oldStep = * prevStep;
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
			currentStepFunc(
				step,
				currentPalette,
				currentStepState,
				step->durationMs - remainingMs,
				0,
				ledCount,
				ledData,
				ledCount
			);
		}
	}

private:
	void nextStep(bool first) {
		if (remainingReps > 0) {
			currentStepEndMs = millis() + steps[currentStepIndex]->durationMs;
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

			AnimationPlanStep* step = steps[currentStepIndex];

			transitionEndMs = first ? 0 : (millis() + step->transitionMs);

			currentStepFunc = step->animationFunc(step, currentStepState);
			currentStepEndMs = millis() + step->durationMs;
			currentPalette = step->palette;
			remainingReps = max(1, step->repetitions) - 1;
		}
	}

private:
	AnimationPlanStep** steps;

	CRGB* ledData;
	uint16_t ledCount;

	AnimationSequenceStep currentStepFunc = NULL;
	CRGBPalette16 currentPalette;
	uint8_t currentStepIndex;
	uint8_t currentStepState[animationStepStateSize];
	uint32_t currentStepEndMs = 0;
	uint32_t transitionEndMs = 0;
	uint8_t remainingReps = 0;

//	CRGBPalette16 prevPalette;
//	AnimationPlanStep** prevStep = NULL;
//	AnimationSequenceStep prevStepFunc = NULL;
//	uint8_t prevStepState[animationStepStateSize];
};

#endif