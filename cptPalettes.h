#ifndef __Cpt_Palettes_H__
#define __Cpt_Palettes_H__

#include <FastLED.h>

// Gradient palette "bhw1_01_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_01.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_01_gp ) {
	0, 227,101,  3,
	117, 194, 18, 19,
	255,  92,  8,192};

// Gradient palette "bhw1_04_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_04.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_04_gp ) {
	0, 229,227,  1,
	15, 227,101,  3,
	142,  40,  1, 80,
	198,  17,  1, 79,
	255,   0,  0, 45};


// Gradient palette "purplepassion1_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/pj/5/tn/purplepassion1.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.

DEFINE_GRADIENT_PALETTE( purplepassion1_gp ) {
	0,  21,  4,132,
	53,  33,  4,100,
	89,  50,  1,100,
	107,  71,  1, 74,
	135,  97,  1, 74,
	160,  19,  5, 21,
	211,  50,  1,100,
	255,  21,  4,132};

// Gradient palette "anharmi_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/pj/4/tn/anharmi.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( anharmi_gp ) {
	0,  75, 18,182,
	56, 128, 10,103,
	109, 132,175,203,
	163,  47,  7,180,
	209,  10, 30,158,
	255,   5, 31,102};


// Gradient palette "bhw1_w00t_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_w00t.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw1_w00t_gp ) {
	0,   3, 13, 43,
	104,  78,141,240,
	188, 255,  0,  0,
	255,  28,  1,  1};


DEFINE_GRADIENT_PALETTE( bw_pedals ) {
	0, 0,0,0,
	32, 16,16,16,
	64, 48,48,48,
	255, 255,255,255};

void randomPalette(CRGBPalette16 &pal) {
	switch (random8() % 4) {
		case 0: pal = bhw1_01_gp; break;
		case 1: pal = bhw1_04_gp; break;
		case 2: pal = purplepassion1_gp; break;
		case 3: pal = anharmi_gp; break;
	}
}

void owlEyePalette(CRGBPalette16 &pal) {
	switch (random8() % 3) {
		case 0: pal = bhw1_04_gp; break;
		case 1: pal = purplepassion1_gp; break;
		case 2: pal = bhw1_01_gp; break;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Green Pedal Palettes

// Gradient palette "bhw2_turq_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_turq.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_turq_gp ) {
	0,   1, 33, 95,
	38,   1,107, 37,
	76,  42,255, 45,
	127, 255,255, 45,
	178,  42,255, 45,
	216,   1,107, 37,
	255,   1, 33, 95};


// Gradient palette "bhw2_10_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_10.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_10_gp ) {
	0,   0, 12,  0,
	61, 153,239,112,
	127,   0, 12,  0,
	165, 106,239,  2,
	196, 167,229, 71,
	229, 106,239,  2,
	255,   0, 12,  0};

// Gradient palette "bhw2_52_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_52.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_52_gp ) {
	0,   1, 55,  1,
	130, 255,255,  8,
	255,  42, 55,  0};


void greenPedalPalette(CRGBPalette16 &pal) {
	switch (random8() % 3) {
		case 0: pal = bhw2_turq_gp; break;
		case 1: pal = bhw2_10_gp; break;
		case 2: pal = bhw2_52_gp; break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Orange Pedal Palettes


// Gradient palette "bhw2_07_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_07.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 24 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_07_gp ) {
	0,  92,  1,  1,
	26, 153, 20,  5,
	79, 232, 72, 12,
	127, 220,231, 89,
	173, 232, 72, 12,
	255,  92,  1,  1};

// Gradient palette "bhw2_13_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_13.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_13_gp ) {
	0, 121,  0,  0,
	74, 173, 15,  1,
	132, 234, 70,  1,
	202,  38, 15,  1,
	255,   0,  0,  0};

// Gradient palette "bhw2_22_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_22.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE( bhw2_22_gp ) {
	0,   0,  0,  0,
	99, 227,  1,  1,
	130, 249,199, 95,
	155, 227,  1,  1,
	255,   0,  0,  0};


void orangePedalPalette(CRGBPalette16 &pal) {
	switch (random8() % 3) {
		case 0: pal = bhw2_07_gp; break;
		case 1: pal = bhw2_13_gp; break;
		case 2: pal = bhw2_22_gp; break;
	}
}


#endif