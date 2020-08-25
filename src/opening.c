#include "common.h"

static uint8_t selection;


const char * const TEXT_JOIN_THE_NAVY_INFO[4] = { 
	"Each time you successfully destroy an\n"
	"armada, you get promoted one rank.\n"
	"If you withdraw, or the time expires,\n"
	"you get demoted one rank.\n\n"
	"You start as an Ensign, \n"
	"   try to reach the Navy's top rank: \n"
	"              Admiral of the Navy!\n\n"
	, 
	"Cada vez que destruyes una armada\n"
	"subes  un rango militar.\n"
	"Si te rindes, o el tiempo acaba,\n"
	"pierdes un rango.\n\n"
	"Empiezas como Alferez, \n"
	"   intenta llegar al rango mas alto: \n"
	"              Almirante de la Armada!\n\n"
	, 
	"Cada vegada que destrueixes una armada\n"
	"pujes  un rang militar.\n"
	"Si et rendeixes, o el tempos s'esgota,\n"
	"perds un rang.\n\n"
	"Comences com Alferes, \n"
	"   intenta arribar al rang superior: \n"
	"              Almirall de l'Armada!\n\n"
	,
	"Elke keer dat je een armada met succes\n"
    "vernietigt, krijg je een rang.\n"
    "Als je je terugtrekt of de tijd \n"
    "verstrijkt, krijg je een lagere rang.\n"
    "Je begint als een Ensign, probeer de \n"
    "hoogste rang van de marine te bereiken:\n"
	"              Admiraal ter Vloot!\n\n"
};


const char * const TEXT_INSTRUCTIONS_FULL[4] = { 
	"An armada of battle ships is hidden in\n"
	"a square grid of 10 by 10 cells.\n"
	"Each ship occupies contiguous cells\n"
	"arranged horizontally or vertically.\n"
	"The ships are placed so that no ship\n"
	"touches other ships, even diagonally.\n"
	"The goal is to find where are the ships.\n"
	"Each row and column has a number\n"
	"indicating the number of cells occupied\n"
	"by ships in that row or column."
	, 
	"Una armada de barcos de guerra esta\n"
	"oculta en una matriz de 10 por 10 celdas.\n"
	"Cada barco ocupa celdas contiguas en\n"
	"horizontal o vertical, no diagonal.\n"
	"Los barcos estan dispuestos de manera\n"
	"que no se tocan entre ellos.\n"
	"La meta es encontrar los barcos.\n"
	"Cada fila y columna tiene un numero\n"
	"que indica cuantas celdas ocupadas por\n"
	"barcos hay en la fila o la columna."	
	, 
	"Una armada de vaixells de guerra esta\n"
	"amagada en una graella de 10x10.\n"
	"Cada vaixell ocupa caselles contigues,\n"
	"de forma vertical o horitzontal.\n"
	"Els vaixells no es toquen entre si,\n"
	"ni tant sols diagonalment.\n"
	"L'objectiu es trobar tots els vaixells.\n"
	"Cada fila i columna te nu numero que\n"
	"indica el nombre de caselles ocupades\n"
	"per vaixells en la casella o columna."
	,
	"Aen armada van slagschepen verbor-\n"
    "gen in een vierkant rooster van 10x10\n"
    "cellen. Elk schip heeft een aantal\n"
    "aaneengesloten vierkanten op de grid,\n"
    "geordend horizontaal of verticaal. De\n"
    "boten zijn geplaatst zodat geen boot\n"
    "een andere boot raakt, zelfs niet\n"
    "diagonaal. Het doel is om de schepen te\n"
    "vinden. Elke rij en kolom heeft ook een\n"
    "aantal ernaast, met vermelding van\n"
    "het aantal vakjes dat bezet \n"
    "wordt door scheepsonderdelen."
};


const char * const TEXT_INSTRUCTIONS_FULL_2[4] = { 
	"GAMEPLAY:\n"
	"You can mark cells as water, ship\n"
	"part, or leave them empty.\n"
	"For a ship to take form, you need to\n"
	"mark the cells and also the water \n"
	"around it.\n"
	"Once all row and column numbers are\n"
	"green, and the ship left count at\n"
	"the bottom row is all zeros, the armada\n"
	"will be automatically destroyed.\n"
	"You can undo, reset the board, or if\n"
	"you find no solution, surrender.\n"
	, 
	"FORMA DE JUEGO:\n"
	"Puedes marcar las celdas como agua,\n"
	"barco, o dejarlas libres.\n"
	"Para formar un barco, necesitas\n"
	"marcar las celulas del barco, y\n"
	"marcar el agua de alrededor.\n"
	"Cuando todos los numeros de fila,\n"
	"columna, y tipo de barco sean\n"
	"de color verde, la armada se\n"
	"destruira automaticamente.\n"
	"Puedes deshacer movimientos,\n"
	"Resetear el tablero, o, si no\n"
	"encuentras solucion, rendirte.\n"
	, 
	"COM JUGAR:\n"
	"Pots marcar les caselles com aigua,\n"
	"vaixell, o deixar-les en blanc.\n"
	"Per formar un vaixell, cal marcar\n"
	"les caselles del vaixell, i\n"
	"tambe l'aigua del voltant.\n"
	"Quan totes les xifres de fila,\n"
	"columna, i tipus de vaixell\n"
	"siguin verdes, l'armada es destruira.\n"
	"Pots desfer moviments, resetejar\n"
	"el taulell, o, si no trobes\n"
	"solucio, rendir-te.\n"
	,
	"SPEELWIJZE:\n"
    "Je kunt cellen markeren als water of\n"
    "onderdeel van een schip, of leeg laten.\n"
    "Om een schip te maken moet je cellen \n"
    "als zodanig markeren, en ook het water\n"
    "er omheen. Zodra de nummers van de\n"
    "rijen en kolommen allemaal groen zijn\n"
    "en de teller op de onderste rij die het\n"
    "aantal overgebleven schepen aangeeft\n"
    "op nul staat, zal de invasievloot auto-\n"
    "matisch vernietigd worden. Het is mo-\n"
    "gelijk om een zet terug te nemen, het\n"
    "bord te resetten en ook, als je geen\n"
    "oplossing kunt vinden, je over te geven."
};


const char * const TEXT_SOTANO[4] = { 
	"GET IT FROM: SOTANOMSXBBS.ORG:23"
	, 
	"PILLALO EN: SOTANOMSXBBS.ORG:23"
	, 
	"AGAFA'L A: SOTANOMSXBBS.ORG:23"
	,
	"HAAL HET VAN: SOTANOMSXBBS.ORG:23"
};

static void opening_isr() {
	
	IN_MODULE(psg, PAGE_C, {
		PSG_init();    
		if (!ayr_spin()) ayr_restart();
		ayFX_spin();
		PSG_syncRegisters();
	});
	
	if (selection<10) {
		
		uint8_t tx = 128-95-8;
		uint8_t ty = 96-32 + 16*selection;
		uint8_t cy = ((uint8_t)(SA[0].y+1) + ty) >> 1;
		
		if (cy == ty+1) cy = ty;
		if (cy == ty-1) cy = ty;
		cy-=1;
		
		SA[0].pattern = 6<<2;
		SA[0].x = tx;
		SA[0].y = cy;
		SA[0].color = BGray;   
   }

    uint8_t i = (upkeep_index+=7);
	if        (i<0x18) { SA[0].x+= 0;
	} else if (i<0x28+3) { SA[0].x+= 1;
	} else if (i<0x38+2) { SA[0].x+= 2;
	} else if (i<0x48) { SA[0].x+= 3;
	} else if (i<0x58-2) { SA[0].x+= 4;
	} else if (i<0x68-3) { SA[0].x+= 5;
	} else if (i<0x78) { SA[0].x+= 6;
	} else if (i<0xA0) { SA[0].x+= 7;
	} else if (i<0xB0+3) { SA[0].x+= 6;
	} else if (i<0xC0+2) { SA[0].x+= 5;
	} else if (i<0xD0) { SA[0].x+= 4;
	} else if (i<0xE0-2) { SA[0].x+= 3;
	} else if (i<0xF0-3) { SA[0].x+= 2;
	} else             { SA[0].x+= 1;}

}

uint8_t language;
static uint8_t next_language;
uint8_t rank;
uint8_t game_type;


static void draw_title() {
	
	if (language==ENGLISH) return;

	textProperties.font_segment = MODULE_SEGMENT(font_newsgeek,PAGE_D);
    textProperties.font_pts = font_newsgeek_pts;
    textProperties.font_pos = font_newsgeek_pos;
    textProperties.font_len = font_newsgeek_len;
    textProperties.faster = true;

    rectangle(0,0,255,26,0x00,FBlack+BGray);
    rectangle(160,0,255,34,0x00,FBlack+BGray);

	textProperties.sz = 2;
	
	textProperties.x = 5;
	textProperties.y = 2;
	writeText(TEXT_ANCHORS_AWEIGH[language]); 
	textProperties.x = 6;
	textProperties.y = 2;
	writeText(TEXT_ANCHORS_AWEIGH[language]); 
	textProperties.x = 5;
	textProperties.y = 3;
	writeText(TEXT_ANCHORS_AWEIGH[language]); 
	textProperties.x = 6;
	textProperties.y = 3;
	writeText(TEXT_ANCHORS_AWEIGH[language]); 
}

static void bgm_menu() {
    
    
    int8_t playlist_idx = 0;
    int8_t song_idx = 0;

	rectangle(128-80,96-24,127+80,95+24,0x00,FWhite+BBlack);

	write_message_2(128-74, 96-30+8, "BGM MENU", FWhite+BBlack);
    
    while (true) {

		IN_MODULE(music, PAGE_D, 

			if (song_idx >= playlists[playlist_idx].N) {
				playlist_idx++;
				song_idx=0;
			} 
			if (song_idx < 0) {
				playlist_idx--;
			} 
			
			if (playlist_idx < 0) playlist_idx = N_PLAYLISTS-1; 
			if (playlist_idx >= N_PLAYLISTS) playlist_idx = 0; 
		
			if (song_idx < 0) {
				song_idx = playlists[playlist_idx].N-1;
			}
		
			start_playlist_song(&playlists[playlist_idx], song_idx); 
		    
			rectangle(128-80,96-8,127+80,95+24,0x00,FWhite+BBlack);
			
			char msg[32];
			memcpy(msg, playlists[playlist_idx].name, 31);
			msg[31]=0;
			write_message_2(128-74, 96-14+8,  playlists[playlist_idx].name, FWhite+BBlack);

			memcpy(msg, playlists[playlist_idx].songs[song_idx].name, 31);
			write_message_2(128-74, 96+2+8, playlists[playlist_idx].songs[song_idx].name, FWhite+BBlack);
		);

		bool refresh = false;
		while (!refresh) {

			wait_frame();
			uint8_t key = msxhal_getch();
//			wait_frame();
//			while (msxhal_getch()!=0);
			
			if (key!=0) {

				if (key == 0x1D) {
					song_idx--;
					refresh = true;
				} else if (key == 0x1C) {
					song_idx++;
					refresh = true;
				} else if (key == ' ' || key == '\n' || key == 'q') {
					return;
				}
			}
		}
	}
}

static bool draw_opening() {

    initCanvas();

	TMS99X8.blankScreen = 0;
	TMS99X8_syncRegister(1);

	initInfoSprites();

    mapper_load_module(logo_color, PAGE_D);
	TMS99X8_memcpy(MODE2_ADDRESS_CT + 0x0000, &logo_color[0x0000], 0x0800);    
	yield();
	TMS99X8_memcpy(MODE2_ADDRESS_CT + 0x0800, &logo_color[0x0800], 0x0800);    
	yield();
	TMS99X8_memcpy(MODE2_ADDRESS_CT + 0x1000, &logo_color[0x1000], 0x0800);    
	yield();
    mapper_load_module(logo_pattern, PAGE_D);
	TMS99X8_memcpy(MODE2_ADDRESS_PG + 0x0000, &logo_pattern[0x0000], 0x0800);    
	yield();
	TMS99X8_memcpy(MODE2_ADDRESS_PG + 0x0800, &logo_pattern[0x0800], 0x0800);    
	yield();
	TMS99X8_memcpy(MODE2_ADDRESS_PG + 0x1000, &logo_pattern[0x1000], 0x0800);    
	yield();

//    mapper_load_module(join_color, PAGE_D);
//	TMS99X8_memcpy(MODE2_ADDRESS_CT + 0x0000, &join_color[0x0000], 0x1800);    
//   mapper_load_module(join_pattern, PAGE_D);
//	TMS99X8_memcpy(MODE2_ADDRESS_PG + 0x0000, &join_pattern[0x0000], 0x1800);    

	draw_title();

    if (SOTANO_EDITION) {

        textProperties.font_segment = MODULE_SEGMENT(font_tiny,PAGE_D);
        textProperties.font_pts = font_tiny_pts;
        textProperties.font_pos = font_tiny_pos;
        textProperties.font_len = font_tiny_len;
        textProperties.faster = true;
        textProperties.x = 0;
        textProperties.y = 186;
        textProperties.sz = 1;
        writeText(TEXT_SOTANO[language]);     
        rectangle(0,185,textProperties.x-1,191,0x00,FWhite+BBlack);
        textProperties.x = 0;
        writeText(TEXT_SOTANO[language]);     
    }
    


	TMS99X8.blankScreen = 1;
	TMS99X8_syncRegister(1);

	textProperties.font_segment = MODULE_SEGMENT(font_didone,PAGE_D);
    textProperties.font_pts = font_didone_pts;
    textProperties.font_pos = font_didone_pos;
    textProperties.font_len = font_didone_len;
    textProperties.faster = true;


	paged_isr.seg = MODULE_SEGMENT(opening, PAGE_B);
	paged_isr.f = opening_isr;

	selection = 255;
    
    {
		uint8_t c;
		while ((c=msxhal_getch())==0) wait_frame();
		if (c=='M') { bgm_menu(); return true; }
	}
    
    rectangle(128-104,96-32,127+104,95+32,0x00,FWhite+BBlack);

    
    write_message_2(128-74, 96-30, TEXT_JOIN_THE_NAVY[language], FWhite+BBlack);
    
    write_message_2(128-74, 96-14, TEXT_FREE_PLAY[language][rank], FWhite+BBlack);

    write_message_2(128-74, 96+2, TEXT_INSTRUCTIONS[language], FWhite+BBlack);

	next_language = language;
    write_message_2(128-74, 96+18, TEXT_LANGUAGE[language][next_language], FWhite+BBlack);

	selection = 0;
	SA[0].y = 96-30 + 16*selection;
	
    while (msxhal_getch()) { }
    while (true) {
		
		rand16();

		uint8_t key = msxhal_getch();
		while (msxhal_getch()!=0);
		
		if (key!=0) {

			if (key == 0x1D) {
				if (selection==1) {
					if (rank>0) {
						rank--;
						rectangle(128-104,96-14,127+104,95-14+14,0x00,FWhite+BBlack);
						write_message_2(128-74, 96-14, TEXT_FREE_PLAY[language][rank], FWhite+BBlack);
					}
				}
				if (selection==3) {
					if (next_language>0) {
						next_language--;
						rectangle(128-104,96+18,127+104,95+18+14,0x00,FWhite+BBlack);
						write_message_2(128-74, 96+18, TEXT_LANGUAGE[language][next_language], FWhite+BBlack);
					}
				}
			} 
			if (key == 0x1C) {
				if (selection==1) {
					if (rank<3) {
						rank++;
						rectangle(128-104,96-14,127+104,95-14+14,0x00,FWhite+BBlack);
						write_message_2(128-74, 96-14, TEXT_FREE_PLAY[language][rank], FWhite+BBlack);
					}
				}
				if (selection==3) {
					if (next_language<3) {
						next_language++;
						rectangle(128-104,96+18,127+104,95+18+14,0x00,FWhite+BBlack);
						write_message_2(128-74, 96+18, TEXT_LANGUAGE[language][next_language], FWhite+BBlack);
					}
				}
			}
			if (key == 0x1E) {
				if (selection) {
					selection--;
					upkeep_index = 0;
				}
			}
			if (key == 0x1F) {
				if (selection < 3) {
					selection++;
					upkeep_index = 0;
				}
			}
			
			if (key == ' ' || key == '\n') {
				if (selection==3) {
					language =  next_language;
					return true;
				}
				if (selection==2) {
					selection = -1;
					SA[0].y = 209;
					TMS99X8_writeSpriteAttributes(0,SA);	
					rectangle(0,0,255,192,0x00,FWhite+BBlack);
					
					textProperties.font_segment = MODULE_SEGMENT(font_didone,PAGE_D);
					textProperties.font_pts = font_didone_pts;
					textProperties.font_pos = font_didone_pos;
					textProperties.font_len = font_didone_len;
					textProperties.space_between_lines = 14;
					textProperties.faster = true;
					
					write_message_2(0,   0, TEXT_INSTRUCTIONS_FULL[language], FWhite+BBlack);

					write_message_2(50, 192-14, TEXT_INSTRUCTIONS_POINTER[language], FWhite+BBlack);
					
					IN_MODULE(qrcodegen, PAGE_D, {
					
						qrcodegen(TEXT_WIKIPEDIA[language]);
					
						static union {
							struct {
								uint8_t x;
								uint8_t y;
							};
							uint16_t xy;
						} coords;

						for (coords.x=0; coords.x<QRSIZE+2; coords.x++) {
							for (coords.y=0; coords.y<QRSIZE+2; coords.y++) {
								if (qr(coords.xy)) {                        
									setPointFG(coords.xy + (256-(QRSIZE+2))*256 + (192-(QRSIZE+2)));
								}
							}
						}
					});
					
					wait_frame();
				    while (msxhal_getch()) { }
					while (!msxhal_getch()) wait_frame();;

					rectangle(0,0,255,192,0x00,FWhite+BBlack);
                    if (language==3) textProperties.space_between_lines = 13;
                    
					write_message_2(0,   0, TEXT_INSTRUCTIONS_FULL_2[language], FWhite+BBlack);

					wait_frame();
				    while (msxhal_getch()) { }
					while (!msxhal_getch()) wait_frame();;
					return true;
				}
				if (selection==1) {
					selection = -1;
					SA[0].y = 209;
					TMS99X8_writeSpriteAttributes(0,SA);	
					rectangle(0,0,255,192,0x00,FWhite+BBlack);
					
					textProperties.font_segment = MODULE_SEGMENT(font_didone,PAGE_D);
					textProperties.font_pts = font_didone_pts;
					textProperties.font_pos = font_didone_pos;
					textProperties.font_len = font_didone_len;
					textProperties.space_between_lines = 14;
					textProperties.faster = true;
					
					write_message_2(0,   0, TEXT_FREE_PLAY_INFO[language], FWhite+BBlack);

				    while (msxhal_getch()) { }
					while (!msxhal_getch()) wait_frame();;

					game_type = FREE_PLAY;
					if (rank==1) {
						rank=2;
					} else if (rank==2) {
						rank=4;
					} else if (rank==3) {
						rank=5;
					}
					
					return false;
				}
				if (selection==0) {
					selection = -1;
					SA[0].y = 209;
					TMS99X8_writeSpriteAttributes(0,SA);	
					rectangle(0,0,255,192,0x00,FWhite+BBlack);
					
					textProperties.font_segment = MODULE_SEGMENT(font_didone,PAGE_D);
					textProperties.font_pts = font_didone_pts;
					textProperties.font_pos = font_didone_pos;
					textProperties.font_len = font_didone_len;
					textProperties.space_between_lines = 14;
					textProperties.faster = true;
					
					write_message_2(0,   0, TEXT_JOIN_THE_NAVY_INFO[language], FWhite+BBlack);

				    while (msxhal_getch()) { }
					while (!msxhal_getch()) wait_frame();;

					game_type = CAMPAIGN;
					rank = ENSIGN;

					return false;
				}
			}           
		}
		TMS99X8_writeSpriteAttributes(0,SA);	
		wait_frame();
	 }
    
    return false;
}


uint8_t cheater;
uint8_t used_seconds;
uint8_t used_minutes;
uint8_t used_hours;
    
void start_opening() {
	
	cheater = false;
	used_seconds = 0;
	used_minutes = 0;
	used_hours = 0;
	
	rank = ENSIGN;
	
	IN_MODULE(psg, PAGE_C, {
		ayr_init();
		ayFX_init();
		ayr_play(&anchors_aweigh_mid);
	});

	while (draw_opening()); 

	paged_isr.f = nullptr;

	wait_frame();
	
	{
		IN_MODULE(psg, PAGE_C, {
			ayr_fade_out(+2);
		});
		bool isGood = true;
		while (isGood) {
			IN_MODULE(psg, PAGE_C, {
				PSG_init();    
				isGood  = ayr_spin();
				PSG_syncRegisters();
			});
			wait_frame();
		}
	}
	
}
	

