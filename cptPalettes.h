#ifndef __Cpt_Palettes_H__
#define __Cpt_Palettes_H__

#include <FastLED.h>
#include <colorpalettes.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define GRADIENT_SET(...) if (1) { \
		static TProgmemRGBGradientPalette_bytes pals[] = { __VA_ARGS__ };\
		if (paletteSetIndex == p++) { Serial.print("Using Palset: "); Serial.println(p-1); pal = pals[random8() % ARRAY_SIZE(pals)]; return; } \
	}

#define PAL16_SET(...) if (1) { \
		static const TProgmemRGBPalette16* pals[] = { __VA_ARGS__ };\
		if (paletteSetIndex == p++) { Serial.print("Using Palset: "); Serial.println(p-1); pal = *pals[random8() % ARRAY_SIZE(pals)]; return; } \
	}

// Gradient palette "pjs_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/pj/classic/tn/pjs.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 48 bytes of program space.
DEFINE_GRADIENT_PALETTE( pjs_gp ) {
	0, 201,  0,132,
	21, 227,  0, 23,
	22, 255,  0,  0,
	45, 255, 53,  0,
	63, 255,246,  0,
	99,   1,118,  6,
	140,   0,211,255,
	172,   0, 46,138,
	193,   0,  1, 61,
	214,  32,  1, 92,
	239, 201,  0,132,
	255, 201,  0,132};



// Gradient palette "revchak_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/pj/classic/tn/revchak.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 48 bytes of program space.
DEFINE_GRADIENT_PALETTE( revchak_gp ) {
	0, 237,  1,  9,
	13, 244,  8, 19,
	35, 249, 21, 34,
	54, 150,  6, 83,
	73,  78,  1,156,
	107,  16, 13,255,
	140,   1,156,186,
	168,   9,144, 36,
	198, 242,217,  1,
	224, 239, 57,  1,
	249, 239,  8,  5,
	255, 239,  8,  5};


// Gradient palette "passionata_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/pj/classic/tn/passionata.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.
DEFINE_GRADIENT_PALETTE( passionata_gp ) {
	0, 217,  4,102,
	66, 217,  4, 61,
	122, 217,  4,  5,
	186, 161,  4,219,
	255,  78,  4,219};



// Gradient palette "sunlitwave_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/sunlitwave.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.
DEFINE_GRADIENT_PALETTE( sunlitwave_gp ) {
	0,   5,  9, 84,
	45,  37, 24,111,
	81,  16,  5, 59,
	112,  24,  1, 20,
	150,  34,  1,  2,
	198, 175, 36,  7,
	237, 208,104, 16,
	255, 239,211,158};


// Gradient palette "trove_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/trove.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 84 bytes of program space.
DEFINE_GRADIENT_PALETTE( trove_gp ) {
	0,  12, 23, 11,
	12,   8, 52, 27,
	25,  32,142, 64,
	38,  55, 68, 30,
	51, 190,135, 45,
	63, 201,175, 59,
	76, 186, 80, 20,
	89, 220, 79, 32,
	101, 184, 33, 14,
	114, 137, 16, 15,
	127, 118, 20, 27,
	140,  79, 16, 35,
	153,  67,  8, 26,
	165,  22,  9, 42,
	178,  11,  3, 34,
	191,  58, 31,109,
	204, 186, 49, 83,
	216, 182, 25, 55,
	229,  39, 90,100,
	242,  15, 81,132,
	255,  68,135, 52};


// Gradient palette "Sunset_Real_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Real.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.


DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
	0, 120,  0,  0,
	22, 179, 22,  0,
	51, 255,104,  0,
	85, 167, 22, 18,
	135, 100,  0,103,
	198,  16,  0,130,
	255,   0,  0,160};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEFINE_GRADIENT_PALETTE( Red_Flat_1_gp ) {
	0, 255,  1,  0,
	255, 255,  1,  0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEFINE_GRADIENT_PALETTE( White_Flat ) {
	0, 255,  255,  255,
	255, 255,  255,  255};



static uint8_t paletteSetIndex = 0;
void paletteFromSet(CRGBPalette16 &pal) {
	uint8_t p = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Palette Definitions

	//GRADIENT_SET(pjs_gp, revchak_gp, passionata_gp, sunlitwave_gp, trove_gp, Sunset_Real_gp);
	//GRADIENT_SET(sunlitwave_gp, trove_gp, Sunset_Real_gp);
	PAL16_SET(&RainbowColors_p, &PartyColors_p);
	PAL16_SET(&CloudColors_p, &LavaColors_p, &OceanColors_p, &ForestColors_p);
	PAL16_SET(&HeatColors_p);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	paletteSetIndex = 0;
	paletteFromSet(pal);
}
void nextPaletteSet() {
	paletteSetIndex ++;
}

#endif