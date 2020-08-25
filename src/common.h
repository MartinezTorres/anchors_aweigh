#pragma once

// If DEBUG is defined, the function debugBorder changes the border color, otherwise it does nothing.
//#define DEBUG TRUE 

#include <msxhal.h>
#include <tms99X8.h>

#include <rand.h>

#include <psg.h>
USING_MODULE(psg, PAGE_C);

#include <resources.h>

#define SOTANO_EDITION 0


////////////////////////////////////////////////////////////////////////
// SOUND
USING_MODULE(test_afb,PAGE_D);


////////////////////////////////////////////////////////////////////////
// TEXT
extern const char *const TEXT_ANCHORS_AWEIGH[4];
extern const char *const TEXT_JOIN_THE_NAVY[4];
extern const char *const TEXT_FREE_PLAY[4][4];
extern const char *const TEXT_INSTRUCTIONS[4];
extern const char *const TEXT_LANGUAGE[4][4];
extern const char *const TEXT_INSTRUCTIONS_FULL[4];
extern const char *const TEXT_INSTRUCTIONS_POINTER[4];
extern const char *const TEXT_WIKIPEDIA[4];
extern const char *const TEXT_FREE_PLAY_INFO[4];
extern const char *const TEXT_JOIN_THE_NAVY_INFO[4];
extern const char *const TEXT_RANKS[4][11];
extern const char *const TEXT_RANKS_SHORT[4][11];
extern const char *const TEXT_TIME_LEFT[4];
extern const char *const TEXT_TIME_OVER[4];
extern const char *const TEXT_UNDO[4];
extern const char *const TEXT_SOLVE[4];
extern const char *const TEXT_RESET[4];
extern const char *const TEXT_CONFIRM[4];
extern const char *const TEXT_YES[4];
extern const char *const TEXT_NO[4];
extern const char *const TEXT_CURRENT_RANK[4];
extern const char *const TEXT_PRESS_ANY_KEY[4];
extern const char *const TEXT_PROMOTION[4];
extern const char *const TEXT_DEMOTION[4];
extern const char *const TEXT_ACHIEVEMENT_0[4];
extern const char *const TEXT_ACHIEVEMENT_1[4];
extern const char *const TEXT_ACHIEVEMENT_2[4];
extern const char *const TEXT_ACHIEVEMENT_3[4];
extern const char *const TEXT_ACHIEVEMENT_4[4];
extern const char *const TEXT_SHARE[4];
extern const char *const TEXT_GOOD_ENDING[4];
extern const char *const TEXT_BAD_ENDING[4];


////////////////////////////////////////////////////////////////////////
// GRAPHICS
#include <graphics/graphics.h>
USING_MODULE(graphics, PAGE_C);

extern const uint8_t logo_pattern[];
USING_MODULE(logo_pattern, PAGE_D);
extern const uint8_t logo_color[];
USING_MODULE(logo_color, PAGE_D);

extern const uint8_t join_pattern[];
USING_MODULE(join_pattern, PAGE_D);
extern const uint8_t join_color[];
USING_MODULE(join_color, PAGE_D);

extern const uint16_t font_newsgeek_pts[];
extern const uint16_t font_newsgeek_pos[];
extern const uint8_t font_newsgeek_len[];
USING_MODULE(font_newsgeek, PAGE_D);

extern const uint16_t font_didone_pts[];
extern const uint16_t font_didone_pos[];
extern const uint8_t font_didone_len[];
USING_MODULE(font_didone, PAGE_D);


extern const uint16_t font_tiny_pts[];
extern const uint16_t font_tiny_pos[];
extern const uint8_t font_tiny_len[];
USING_MODULE(font_tiny, PAGE_D);

extern const uint16_t font_thin_pts[];
extern const uint16_t font_thin_pos[];
extern const uint8_t font_thin_len[];
USING_MODULE(font_thin, PAGE_D);

////////////////////////////////////////////////////////////////////////
// QR CODE GENERATOR
#include <qr/qrcodegen.h>


////////////////////////////////////////////////////////////////////////
// TIMER
extern uint8_t time_remaining_minutes_10;
extern uint8_t time_remaining_minutes_1;
extern uint8_t time_remaining_seconds_10;
extern uint8_t time_remaining_seconds_1;
extern uint8_t time_remaining_frames;
extern bool timer_must_update;

void timer_init_int(uint16_t seconds);
bool timer_update_int();
const char *timer_get_string_int();
void write_timer_int(uint8_t color) __z88dk_fastcall;
void write_no_timer_int(uint8_t color) __z88dk_fastcall;
USING_MODULE(timer, PAGE_C);
INLINE void timer_init(uint16_t seconds) { IN_MODULE(timer, PAGE_C, timer_init_int(seconds);); }
INLINE bool timer_update() { bool r; IN_MODULE(timer, PAGE_C, r=timer_update_int();); return r;}
INLINE const char * timer_get_string() { const char *r; IN_MODULE(timer, PAGE_C, r=timer_get_string_int();); return r; }
INLINE void write_timer(uint8_t color) { IN_MODULE(timer, PAGE_C, write_timer_int(color);); }
INLINE void write_no_timer(uint8_t color) { IN_MODULE(timer, PAGE_C, write_no_timer_int(color);); }
////////////////////////////////////////////////////////////////////////
// SPRITEs
void initInfoSprites_int();
USING_MODULE(sprites, PAGE_D);
INLINE void initInfoSprites() { IN_MODULE(sprites, PAGE_D, initInfoSprites_int();); }

////////////////////////////////////////////////////////////////////////
// INPUTs
char get_char_and_joystick();

////////////////////////////////////////////////////////////////////////
// MUSIC
USING_MODULE(music, PAGE_D);
typedef struct { 
    const char * name; 
    const AYR * ayr; 
} Song;

typedef struct { 
    const char *name; 
    int8_t N; 
    const Song *songs; 
    int8_t volume;
} Playlist;

typedef enum {
	PL_TITLE = 0,
	PL_SLOW = 1,
	PL_MID = 2,
	PL_FAST = 3,
	PL_ACHIEVEMENT = 4,
	PL_PROMOTION = 5,
	PL_DEMOTION = 6,
	PL_ENDING = 7,
} PLAYLISTS;

extern const Playlist playlists[];
extern const int8_t N_PLAYLISTS;

int8_t start_playlist_song(const Playlist *playlist, int8_t n);

////////////////////////////////////////////////////////////////////////
// MAP GENERATOR
USING_MODULE(map, PAGE_D);
typedef enum {
	EMPTY = 0,
	WATER = 1,
	SHIP_UNDEFINED = 2,
	SHIP_SUB = 3,
	SHIP_TOP = 4,
	SHIP_CENTER_VERTICAL = 5,
	SHIP_BOTTOM = 6,
	SHIP_LEFT = 7,
	SHIP_CENTER_HORIZONTAL = 8,
	SHIP_RIGHT = 9,
	SHIP_SUB_LEGEND = 10,
	SHIP_LEFT_LEGEND = 11,
	SHIP_CENTER_HORIZONTAL_LEGEND = 12,
	SHIP_RIGHT_LEGEND = 13,
	SHIP_EXPLOSION = 14,
} CELL_TYPES;

typedef struct {
	uint8_t o, x, y, sz;
} SHIP;

typedef enum {
	ENSIGN,
	LIUTENANT_JUNIOR,
	LIUTENANT,
	LIUTENANT_COMMANDER,
	COMMANDER,
	CAPTAIN,
	REAR_ADMIRAL,
	VICE_ADMIRAL,
	ADMIRAL,
	FLEET_ADMIRAL,
	ADMIRAL_NAVY
} RANKS;

typedef enum {
	ENGLISH,
	SPANISH,
	CATALAN,
	DUTCH,
} LANGUAGES;

typedef enum {
	CAMPAIGN,
	FREE_PLAY,
} GAME_TYPE;

extern uint8_t language;
extern uint8_t game_type;
extern uint8_t rank;

extern uint8_t cheater;
extern uint8_t used_seconds;
extern uint8_t used_minutes;
extern uint8_t used_hours;


extern uint8_t map[12][12];
extern uint8_t map_revealed[12][12];
extern uint8_t map_display[12][12];
extern uint8_t map_correctness[12][12];


void init_map();

////////////////////////////////////////////////////////////////////////
// MISC

typedef enum {
	PLAYING,
	WON,
	LOST
} STATUS;
extern uint8_t status;
extern uint8_t sel_x, sel_y, sel_o, sel_yn;
extern uint8_t upkeep_index;

extern int8_t music_paused;
extern int8_t song_idx;
extern const Playlist *playlist;

void write_message_2(uint8_t x, uint8_t y, const char *msg, uint8_t color);
void write_message_tiny(uint8_t x, uint8_t y, const char *msg, uint8_t color);
USING_MODULE(misc, PAGE_D);
USING_MODULE(miscb, PAGE_B);

void drawCell_int(uint8_t x, uint8_t y, uint8_t type, uint8_t color_scheme);
void update_correctness();
void update_ship_tile(uint8_t i, uint8_t j);

INLINE void drawCell(uint8_t x, uint8_t y, uint8_t type, uint8_t color_scheme) 
{ IN_MODULE(misc, PAGE_D, drawCell_int(x,y,type,color_scheme);); }

void start_level_conclude_campaign();
void start_level_conclude_free_play();
void won_isr();


////////////////////////////////////////////////////////////////////////
// LINK POINTS
USING_MODULE(opening, PAGE_B);
void start_opening();

USING_MODULE(level, PAGE_B);
void start_level();

////////////////////////////////////////////////////////////////////////
// COMMON UTILITIES
extern uint8_t scratchpad[256];

typedef struct {
	uint8_t seg;
	isr_function f;
} Tpaged_isr;
extern Tpaged_isr paged_isr;
