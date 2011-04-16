// $Id$

#ifndef ROMTYPES_HH
#define ROMTYPES_HH

namespace openmsx {

enum RomType {
	ROM_GENERIC_8KB  = 0,
	ROM_GENERIC_16KB = 1,
	ROM_KONAMI       = 2,
	ROM_KONAMI_SCC   = 3,
	ROM_ASCII8       = 4,
	ROM_ASCII16      = 5,
	ROM_R_TYPE       = 6,
	ROM_CROSS_BLAIM  = 7,
	ROM_MSX_AUDIO    = 8,
	ROM_HARRY_FOX    = 9,
	ROM_HALNOTE      = 10,
	ROM_ZEMINA80IN1  = 11,
	ROM_ZEMINA90IN1  = 12,
	ROM_ZEMINA126IN1 = 13,
	ROM_HOLY_QURAN   = 14,
	ROM_MIRRORED     = 15,
	ROM_NORMAL       = 16,
	ROM_FSA1FM1      = 17,
	ROM_FSA1FM2      = 18,
	ROM_DRAM         = 19,
	ROM_PADIAL8      = 20,
	ROM_PADIAL16     = 21,
	ROM_SUPERLODERUNNER = 22,
	ROM_MSXDOS2      = 23,
	ROM_MANBOW2      = 24,
	ROM_MEGAFLASHROMSCC = 25,
	ROM_MATRAINK     = 26,
	ROM_HOLY_QURAN2  = 27,
	ROM_ARC          = 28,
	ROM_MEGAFLASHROMSCCPLUS = 29,
	ROM_DOOLY          = 30,

	ROM_PAGE0        = 32 + 1,
	ROM_PAGE1        = 32 + 2,
	ROM_PAGE01       = 32 + 3,
	ROM_PAGE2        = 32 + 4,
	ROM_PAGE02       = 32 + 5,
	ROM_PAGE12       = 32 + 6,
	ROM_PAGE012      = 32 + 7,
	ROM_PAGE3        = 32 + 8,
	ROM_PAGE03       = 32 + 9,
	ROM_PAGE13       = 32 + 10,
	ROM_PAGE013      = 32 + 11,
	ROM_PAGE23       = 32 + 12,
	ROM_PAGE023      = 32 + 13,
	ROM_PAGE123      = 32 + 14,
	ROM_PAGE0123     = 32 + 15,

	ROM_MIRRORED0000 = 48 + 0,
	ROM_MIRRORED2000 = 48 + 1,
	ROM_MIRRORED4000 = 48 + 2,
	ROM_MIRRORED6000 = 48 + 3,
	ROM_MIRRORED8000 = 48 + 4,
	ROM_MIRROREDA000 = 48 + 5,
	ROM_MIRROREDC000 = 48 + 6,
	ROM_MIRROREDE000 = 48 + 7,

	ROM_NORMAL0000   = 56 + 0,
	ROM_NORMAL2000   = 56 + 1,
	ROM_NORMAL4000   = 56 + 2,
	ROM_NORMAL6000   = 56 + 3,
	ROM_NORMAL8000   = 56 + 4,
	ROM_NORMALA000   = 56 + 5,
	ROM_NORMALC000   = 56 + 6,
	ROM_NORMALE000   = 56 + 7,

	ROM_ASCII8_8     = 64 + 0,
	ROM_ASCII16_2    = 64 + 1,
	ROM_GAME_MASTER2 = 64 + 2,
	ROM_PANASONIC    = 64 + 3,
	ROM_NATIONAL     = 64 + 4,
	ROM_KOEI_8       = 64 + 5,
	ROM_KOEI_32      = 64 + 6,
	ROM_WIZARDRY     = 64 + 7,

	ROM_MAJUTSUSHI   = 128 + 0,
	ROM_SYNTHESIZER  = 128 + 1,
	ROM_PLAYBALL     = 128 + 2,
	ROM_KBDMASTER    = 128 + 3,
	ROM_NETTOU_YAKYUU= 128 + 4,

	ROM_UNKNOWN      = 256
};

} // namespace openmsx

#endif
