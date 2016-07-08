#ifndef __Fire_ANIMATION_H__
#define __Fire_ANIMATION_H__

#include "FastArduinoAnimationFramework.h"

#define FIRE_DEFAULT_COOLING  55


// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
////
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation,
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking.
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100
#define FIRE_DEFAULT_COOLING  85

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define FIRE_DEFAULT_SPARKING 64

struct FireAnimationStep : public AnimationStep {
	uint8_t cooling;
	uint8_t sparking;
	uint8_t size;
	uint8_t* buffer;
};

void fireAnimationStep(
	FireAnimationStep* step,
	CRGBPalette16& palette,
	uint16_t timeMs,
	uint16_t startLed,
	uint16_t endLed,
	CRGB* ledData,
    uint16_t ledCount
) {
	uint8_t heatCount = step->size;
	uint8_t* heat = step->buffer;
	uint8_t cooling = step->cooling;

	random16_add_entropy(random());

	// Step 1.  Cool down every cell a little
	for( int i = 0; i < heatCount; i++) {
		heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / heatCount) + 2));
	}

	// Step 2.  Heat from each cell drifts 'up' and diffuses a little
	for( int k= heatCount - 1; k >= 2; k--) {
		heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
	}

	// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
	if(random8() < step->sparking ) {
		int y = random8(7);
		heat[y] = qadd8( heat[y], random8(160,255) );
	}

	// Step 4.  Map from heat cells to LED colors
	CRGB* led = ledData + startLed;
	for (uint16_t i = startLed; i < endLed; i++, led++) {
		*led = ColorFromPalette(palette, heat[i * heatCount / ledCount]);
	}
}

template<
	uint16_t transitionMs,
	AnimationPalettePopulator paletteFunc,
	uint16_t durationMs,
	uint8_t repetitions,
	uint8_t size,
	uint8_t cooling,
	uint8_t sparking
>
FireAnimationStep* fireAnimation() {
	static FireAnimationStep params;

	static uint8_t buffer[size];

	params.animationFunc = (AnimationSequenceStep) &fireAnimationStep;
	params.commonParams = commonParams<transitionMs, paletteFunc, durationMs, repetitions>();
	params.size = size;
	params.cooling = cooling == 0 ? FIRE_DEFAULT_COOLING : cooling;
	params.sparking = sparking == 0 ? FIRE_DEFAULT_SPARKING : sparking;
	params.buffer = buffer;

	return &params;
}

#endif