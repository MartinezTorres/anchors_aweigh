#include "common.h"


static const Song playlist_title[] = {
	{ "Anchors Aweigh!", &anchors_aweigh_mid}
};

static const Song playlist_gameplay_slow[] = {

// OKISH, NEEDS REWORK.
    { "Battle Cry", &batlcry_mid},
// ITS NICE, RELAXING; GAMEPLAY
	{ "Come All", &comeall_mid},
// ITS NICE, RELAXING; GAMEPLAY
	{ "Potomac", &potomac_mid},
// OKISH, NEEDS REWORK.
    { "Grieg Mountain King", &grieg_mountain_king_mid},
// ITS NICE, MEH - RELAXING; GAMEPLAY
	{ "Down Valley", &downvaly_mid},
// UNKNOWN, SOUNDS LIKE A CHURCH;
	{ "Navy Hymn", &navyhymn_mid},
};

static const Song playlist_gameplay_mid[] = {
// THIS IS GOOD; GAMEPLAY.
	{ "America the Beautiful", &america_the_beautiful_mid},
// ITS NICE, RELAXING; GAMEPLAY
	{ "Auralee", &auralee_mid},
// BROKEN VOLUME?
//	{ "Drill", &drill_mid},
// THIS IS GOOD; GAMEPLAY.
	{ "Colonel Bogey", &colonel_bogeyPNO_mid},
// NICE, BUT NEEDS MAJOR REWORK.
    { "Battle Hymn", &battle_hymn_PNO_mid},
// THIS IS GOOD; GAMEPLAY POSIBLE.
    { "Johnny Maching In", &johnny_marching_PNO_mid},
};

static const Song playlist_gameplay_fast[] = {
//	{ "Cotton Eye Joe", &cotton_eye_joe_2_e_mid},
// THIS IS GOOD; GAMEPLAY.
	{ "Oh Susanna!", &susanna_mid},
};

static const Song playlist_achievements[] = {
// THIS IS NICE; FOR THE LEVEL ENDINGS; NEEDS SOME MINOR REWORKS
    { "Semper Fidelis", &semper_fidelisBN_mid },
};

static const Song playlist_promotion[] = {
// THIS IS GOOD; GAMEPLAY. SUPERSHORT. ACHIEVEMENT?
	{ "Yankee Doodle", &yankeedoodle_PNO_mid},
// THIS IS NICE; FOR THE LEVEL ENDINGS; NEEDS VERY MINOR REWORKS
    { "Washington Post", &washington_postPNO_mid, },
// THIS IS NICE; FOR THE LEVEL ENDINGS; NEEDS SOME MINOR REWORKS / MAY WORK FOR START OF A LEVEL
    { "The Thunderer", &The_Thunderer_mid, },
};

static const Song playlist_demotion[] = {
// THIS IS GOOD; LOOSING ON TIME / WITHDRAW;
    { "Marche Slave", &marcheslavePNO_mid, },
};

static const Song playlist_ending[] = {
// THIS IS NICE; FOR THE GOOD ENDING
    { "Star Spangled Banner", &star_spangled_banner_mid},
};


#define NS(a) (sizeof(a)/sizeof(Song)), a
const Playlist playlists[] = {
    { "Title", NS(playlist_title), 0 },
    { "Play Slow", NS(playlist_gameplay_slow), -48 },
    { "Play Mid", NS(playlist_gameplay_mid), -32 },
    { "Play Fast", NS(playlist_gameplay_fast), -16 },
    { "Achievement", NS(playlist_achievements), 0 },
    { "Promotion", NS(playlist_promotion), 0 },
    { "Demotion", NS(playlist_demotion), 0 },
    { "Ending", NS(playlist_ending), 0 }
};

const int8_t N_PLAYLISTS = (sizeof(playlists)/sizeof(Playlist));

int8_t start_playlist_song(Playlist const *playlist, int8_t n) {
    
    int8_t N  = playlist->N;
    
	while (n >= N) n -= N;
	while (n < 0) n += N;

	IN_MODULE(psg, PAGE_C, {
		ayr_init();
		ayFX_init();
		ayr_play(playlist->songs[n].ayr);
        ayr_set_volume(playlist->volume);
	});
    
    return n;
}
