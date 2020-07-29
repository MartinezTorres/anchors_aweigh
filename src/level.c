#include <common.h>

uint8_t map_display[12][12];
uint8_t map_correctness[12][12];

uint8_t status;
uint8_t sel_x, sel_y, sel_o, sel_yn;
uint8_t upkeep_index;

int8_t music_paused;
int8_t song_idx;
const Playlist *playlist;
static void music_isr_helper() {
	
	IN_MODULE(psg, PAGE_C, {
		PSG_init();    
		if (!ayr_spin()) {
			if (!music_paused) {
				song_idx++;
				IN_MODULE(music, PAGE_D, 
					song_idx = start_playlist_song(playlist, song_idx); 
				);
			}
		}
		ayFX_spin();
		PSG_syncRegisters();
	});
}

void won_isr() {
	music_isr_helper();
}

static void preparing_isr() {
	music_isr_helper();
}

static bool timer_expired;

static void playing_isr() {

	timer_expired = timer_update();

	music_isr_helper();
	if (sel_x<10) {
		
		uint8_t tx = 16*sel_x;
		uint8_t ty = 16*sel_y;
		uint8_t cx = (SA[0].x + tx) >> 1;
		uint8_t cy = ((uint8_t)(SA[0].y+1) + ty) >> 1;
		
		if (cx == tx+1) cx = tx;
		if (cx == tx-1) cx = tx;
		if (cy == ty+1) cy = ty;
		if (cy == ty-1) cy = ty;
		
		cy-=1;
		
		SA[0].pattern = 0;
		SA[0].x = cx;
		SA[0].y = cy;
		SA[0].color = BWhite;   
	

		SA[1].pattern = 0;
		SA[1].x = cx;
		SA[1].y = cy;
		SA[1].color = BGray ;    

		SA[2].pattern = 0;
		SA[2].x = cx;
		SA[2].y = cy;
		SA[2].color = BLightGreen ;    

		SA[3].pattern = 5<<2;
		SA[3].x = cx;
		SA[3].y = cy;
		SA[3].color = BBlack ;

		if (map_revealed[sel_y+1][sel_x+1]!=EMPTY) {
			SA[0].color = BLightRed;
			SA[1].color = BLightRed;
			SA[2].color = BDarkRed;
		}

		uint8_t i = (upkeep_index+=6);
		for (uint8_t j=0; j<3; j++) {
			
			if        (i<0x20) { SA[j].pattern+= 0<<2;
			} else if (i<0x40) { SA[j].pattern+= 0<<2;
			} else if (i<0x60) { SA[j].pattern+= 0<<2;
			} else if (i<0x80) { SA[j].pattern+= 0<<2;
			} else if (i<0xA0) { SA[j].pattern+= 1<<2;
			} else if (i<0xC0) { SA[j].pattern+= 2<<2;
			} else if (i<0xD0) { SA[j].pattern+= 3<<2;
			} else             { SA[j].pattern+= 4<<2; }
			
			i-=0x0C;
		}
    }
    

    TMS99X8_writeSpriteAttributes(0,SA);
}

static void draw_legend() {

	
	drawCell_int(1,11,SHIP_LEFT_LEGEND,4);
	drawCell_int(2,11,SHIP_CENTER_HORIZONTAL_LEGEND,4);
	drawCell_int(3,11,SHIP_CENTER_HORIZONTAL_LEGEND,4);
	drawCell_int(4,11,SHIP_RIGHT_LEGEND,4);

	drawCell_int(6,11,SHIP_LEFT_LEGEND,4);
	drawCell_int(7,11,SHIP_CENTER_HORIZONTAL_LEGEND,4);
	drawCell_int(8,11,SHIP_RIGHT_LEGEND,4);

	drawCell_int(10,11,SHIP_LEFT_LEGEND,4);
	drawCell_int(11,11,SHIP_RIGHT_LEGEND,4);

	drawCell_int(13,11,SHIP_SUB_LEGEND,4);
}


static uint8_t undoStart, undoEnd;
typedef struct {
    uint8_t x : 4;
    uint8_t y : 4;
} uint4_tp;

static uint4_tp undoBuffer[256];


static char msg[32];

static uint8_t current_column_color[12];
static void write_column_number(uint8_t col, uint8_t sumY, uint8_t color) {

	yield();
	if (current_column_color[col]==color) return;
	current_column_color[col]=color;

	textProperties.color = color;
	textProperties.sz = 1;
	
	msg[1]=0;
	
	msg[0]='0'+ sumY;
	textProperties.x = 16*col+6-18+1;
	if (sumY==1) textProperties.x +=2;
	textProperties.y = 16*10+3;
	writeText(msg);		
}

static uint8_t current_row_color[12];
static void write_row_number(uint8_t row, uint8_t sumX, uint8_t color) {

	yield();
	if (current_row_color[row]==color) return;
	current_row_color[row]=color;

	textProperties.color = color;
	textProperties.sz = 1;
	
	msg[1]=0;

	msg[0]='0'+ sumX;
	textProperties.x = 16*10+3;
	textProperties.y = 16*row-16+3;
	if (sumX==1) textProperties.x +=1;
	writeText(msg); 
}


static bool update_side_counts(uint8_t i, uint8_t j) {
	
	yield();

	uint8_t sumX=0, sumY=0;
	uint8_t sumDX=0, sumDY=0;
	for (uint8_t k=1; k<11; k++) {
		sumX += (map[i][k]>WATER);
		sumY += (map[k][j]>WATER);
		sumDX += (map_display[i][k]>WATER);
		sumDY += (map_display[k][j]>WATER);
	}
	
	if (sumDX<sumX) {
		write_row_number(i, sumX, FGray + BTransparent);
		
	} else if (sumDX==sumX) {
		write_row_number(i, sumX, FLightGreen + BTransparent);	
	} else {
		write_row_number(i, sumX, FLightRed + BTransparent);	
	}

	if (sumDY<sumY) {
		write_column_number(j, sumY, FGray + BTransparent);
	} else if (sumDY==sumY) {
		write_column_number(j, sumY, FLightGreen + BTransparent);
	} else {
		write_column_number(j, sumY, FLightRed + BTransparent);
	}
	
	return sumDX==sumX && sumDY==sumY;
}



static uint8_t oldShipCount[6];
static bool update_legend_counts() {

	yield();

	uint8_t countShips[11];
	uint8_t countShipsFound[11];

	for (uint8_t i=0; i<6; i++) {
		countShips[i]=0;
		countShipsFound[i]=0;
	}

	for (uint8_t i=1; i<11; i++) {
		for (uint8_t j=1; j<11; j++) {
			uint8_t c = map[i][j];
			if (c<=WATER) continue;
			if (c==SHIP_SUB) {
				countShips[0]++;
				continue;
			}
			if (c==SHIP_TOP) {
				uint8_t s=1;
				while (map[i+s][j]==SHIP_CENTER_VERTICAL) s++;
				if (map[i+s][j]==SHIP_BOTTOM) countShips[s]++;
				continue;
			}
			if (c==SHIP_LEFT) {
				uint8_t s=1;
				while (map[i][j+s]==SHIP_CENTER_HORIZONTAL) s++;
				if (map[i][j+s]==SHIP_RIGHT) countShips[s]++;
				continue;
			}
		}
	}
			
	for (uint8_t i=1; i<11; i++) {
		yield();
		for (uint8_t j=1; j<11; j++) {
			uint8_t c = map_display[i][j];
			if (c<=WATER) continue;
			if (c==SHIP_SUB) {
				countShipsFound[0]++;
				continue;
			}
			if (c==SHIP_TOP) {
				uint8_t s=1;
				while (map_display[i+s][j]==SHIP_CENTER_VERTICAL) s++;
				if (map_display[i+s][j]==SHIP_BOTTOM) countShipsFound[s]++;
				continue;
			}
			if (c==SHIP_LEFT) {
				uint8_t s=1;
				while (map_display[i][j+s]==SHIP_CENTER_HORIZONTAL) s++;
				if (map_display[i][j+s]==SHIP_RIGHT) countShipsFound[s]++;
				continue;
			}
		}
	}

	msg[1]=0;
	
	if (oldShipCount[0] != (countShips[0]-countShipsFound[0])) {
		oldShipCount[0] = countShips[0]-countShipsFound[0];
		rectangle(16*13-8  ,16*11+3, 16*13-8+7,16*11+3+9,0x00,FWhite+BBlack);
		if (countShipsFound[0]<countShips[0]) {
			msg[0] = '0' + countShips[0]-countShipsFound[0];
			
			write_message_2(16*13-8  ,16*11+2, msg, FGray + BTransparent);		
		} else if (countShipsFound[0]==countShips[0]) {
			msg[0] = '0';
			write_message_2(16*13-8  ,16*11+2, msg, FLightGreen + BTransparent);		
		} else {
			msg[0] = '!';
			write_message_2(16*13-8+2  ,16*11+2, msg, FLightRed + BTransparent);		
		}
	}

	if (oldShipCount[1] != (countShips[1]-countShipsFound[1])) {
		oldShipCount[1] = countShips[1]-countShipsFound[1];
		rectangle(16*10-8  ,16*11+3, 16*10-8+7,16*11+3+9,0x00,FWhite+BBlack);
		if (countShipsFound[1]<countShips[1]) {
			msg[0] = '0' + countShips[1]-countShipsFound[1];
			
			write_message_2(16*10-8  ,16*11+2, msg, FGray + BTransparent);		
		} else if (countShipsFound[1]==countShips[1]) {
			msg[0] = '0';
			write_message_2(16*10-8  ,16*11+2, msg, FLightGreen + BTransparent);		
		} else {
			msg[0] = '!';
			write_message_2(16*10-8+2  ,16*11+2, msg, FLightRed + BTransparent);		
		}
	}
	if (oldShipCount[2] != (countShips[2]-countShipsFound[2])) {
		oldShipCount[2] = countShips[2]-countShipsFound[2];
		rectangle(16*6-8  ,16*11+3, 16*6-8+7,16*11+3+9,0x00,FWhite+BBlack);
		if (countShipsFound[2]<countShips[2]) {
			msg[0] = '0' + countShips[2]-countShipsFound[2];
			
			write_message_2(16*6-8  ,16*11+2, msg, FGray + BTransparent);		
		} else if (countShipsFound[2]==countShips[2]) {
			msg[0] = '0';
			write_message_2(16*6-8  ,16*11+2, msg, FLightGreen + BTransparent);		
		} else {
			msg[0] = '!';
			write_message_2(16*6-8+2  ,16*11+2, msg, FLightRed + BTransparent);		
		}
	}
	
	if (oldShipCount[3] != (countShips[3]-countShipsFound[3])) {
		oldShipCount[3] = countShips[3]-countShipsFound[3];
		rectangle(16*1-8  ,16*11+3, 16*1-8+7,16*11+3+9,0x00,FWhite+BBlack);
		if (countShipsFound[3]<countShips[3]) {
			msg[0] = '0' + countShips[3]-countShipsFound[3];
			
			write_message_2(16*1-8  ,16*11+2, msg, FGray + BTransparent);		
		} else if (countShipsFound[3]==countShips[3]) {
			msg[0] = '0';
			write_message_2(16*1-8  ,16*11+2, msg, FLightGreen + BTransparent);		
		} else {
			msg[0] = '!';
			write_message_2(16*1-8+2  ,16*11+2, msg, FLightRed + BTransparent);		
		}
	}

	bool good = true;

	for (uint8_t k=0; k<6; k++) {
		if (countShips[k] != countShipsFound[k]) {
			good = false;
			break;
		}
	}
	
	if (good) {
		for (uint8_t j=1; j<11; j++) {
			if (!update_side_counts(j,j)) {
				good = false;
				break;
			}
		}
	}
		
	return good;	
}

static void set_map() {
	
	for (uint8_t i=0; i<6; i++) {
		oldShipCount[i]=128;
	}
	
	for (uint8_t i=0; i<12; i++) {
		current_column_color[i]=255;
		current_row_color[i]=255;
		for (uint8_t j=0; j<12; j++) {
			map_display[i][j] = WATER;
			map_correctness[i][j] = 1;
		}
	}
		
	for (uint8_t i=1; i<11; i++) {
		for (uint8_t j=1; j<11; j++) {
			map_display[i][j] = map_revealed[i][j];
			
		}
	}
	
    	
	for (uint8_t i=1; i<11; i++) {
		for (uint8_t j=1; j<11; j++) {
			drawCell_int(j-1,i-1,map_display[i][j],map_correctness[i][j]);
		}
	}
	
	for (uint8_t i=1; i<11; i++)
		update_side_counts(i,i);

	update_legend_counts();	
}

static void start_level_prepare() {

	music_paused = false;
	
	mapper_load_module(misc, PAGE_D);
	
	song_idx = ((rand16()>>8) & 0x3F);
	
	IN_MODULE(music, PAGE_D, 
		playlist = &playlists[PL_SLOW];
	);

	paged_isr.seg = MODULE_SEGMENT(level, PAGE_B);
	paged_isr.f = preparing_isr;
	
	IN_MODULE(music, PAGE_D, 
		song_idx = start_playlist_song(playlist, song_idx); 
	);
	
	EI();
	IN_MODULE(map, PAGE_D, init_map() );

    initCanvas();

//	textProperties.font_segment = MODULE_SEGMENT(font_didone,PAGE_D);
//	textProperties.font_pts = font_didone_pts;
//	textProperties.font_pos = font_didone_pos;
//	textProperties.font_len = font_didone_len;
	textProperties.font_segment = MODULE_SEGMENT(font_thin,PAGE_D);
	textProperties.font_pts = font_thin_pts;
	textProperties.font_pos = font_thin_pos;
	textProperties.font_len = font_thin_len;
	textProperties.space_between_lines = 12;
	textProperties.faster = false;
	
	rectangle(0,0,255,191,0x00,FWhite+BBlack);

	set_map();

	write_message_tiny(176, 0, TEXT_TIME_LEFT[language], FGray + BTransparent);

	write_message_2(176, 102, TEXT_CURRENT_RANK[language], FGray + BTransparent);
	write_message_2(176, 126, TEXT_RANKS_SHORT[language][rank], FGray + BTransparent);
	

	write_message_2(176, 22, TEXT_UNDO[language], FGray + BTransparent);
	write_message_2(176, 34, TEXT_RESET[language], FGray + BTransparent);
	write_message_2(176, 46, TEXT_SOLVE[language], FGray + BTransparent);

	write_message_2(176, 58, TEXT_CONFIRM[language], FTransparent + BTransparent);
	write_message_2(180, 70, TEXT_YES[language], FTransparent + BTransparent);
	write_message_2(215, 70, TEXT_NO[language], FTransparent + BTransparent);

	draw_legend();
	
	initInfoSprites();

	DI();
	
	sel_x = 0;
	sel_y = 0;
	status = PLAYING;
	paged_isr.seg = MODULE_SEGMENT(level, PAGE_B);
	paged_isr.f = playing_isr;
}

static void start_level_play() {
	
	////////////////////////
	// PLAY LEVEL	
	timer_init(60*20);
	//timer_init(10);
	timer_expired = false;
	status = PLAYING;
	undoStart = 0;
	undoEnd = 0;
    while (msxhal_getch()) { }
	while (status==PLAYING) {

	if (timer_must_update) {
		
		timer_must_update=false;
		
		if  (game_type == FREE_PLAY) {
			write_no_timer(FGray + BTransparent);			
			timer_init(60*20);
		} else if (time_remaining_minutes_10) {
			write_timer(FLightGreen + BTransparent);
		} else if (time_remaining_minutes_1>8) {
			write_timer(FLightGreen + BTransparent);
		} else if (time_remaining_minutes_1) {
			IN_MODULE(music, PAGE_D, 
				playlist = &playlists[PL_MID];
			);
			write_timer(FLightYellow + BTransparent);
		} else {
			IN_MODULE(music, PAGE_D, 
				playlist = &playlists[PL_FAST];
			);
			write_timer(FLightRed + BTransparent);
		}
		
		if (timer_expired) {
			status = LOST;
			rectangleColor(176,22+0*12,255,33+2*12, FGray + BTransparent);
			rectangle(176,22+3*12,255,33+4*12,0x00, FLightRed + BTransparent);
			write_message_2(176, 70, TEXT_TIME_OVER[language], FLightRed + BTransparent);
		}
	}

	uint8_t key = msxhal_getch();
    
    if (key!=0) {

			if (key == 0x1D) {
				if (sel_x==10) {
					rectangleColor(176,22+sel_o*12,255,33+sel_o*12, FGray + BTransparent);
				}
				
				if (sel_x) {
					sel_x--;
				}
				
			} 
			if (key == 0x1C) {
				if (sel_x<10) {
					sel_x++;
					if (sel_x==10) {
						sel_o=0;
						SA[0].color = BTransparent;
						SA[1].color = BTransparent;
						SA[2].color = BTransparent;
						SA[3].color = BTransparent;
												
						rectangleColor(176,22+sel_o*12,255,33+sel_o*12, FLightGreen+ BTransparent);
					}
				}
			}
			if (key == 0x1E) {
				if (sel_x!=10 && sel_y) {
					sel_y--;
				}
				if (sel_x==10 && sel_o) {
					rectangleColor(176,22+sel_o*12,255,33+sel_o*12, FGray + BTransparent);
					sel_o--;
					rectangleColor(176,22+sel_o*12,255,33+sel_o*12, FLightGreen + BTransparent);
				}
			}
			if (key == 0x1F) {
				if (sel_x!=10 && sel_y<9) { 
					sel_y++;
				}
				if (sel_x==10 && sel_o<2) {
					rectangleColor(176,22+sel_o*12,255,33+sel_o*12, FGray + BTransparent);
					sel_o++;
					rectangleColor(176,22+sel_o*12,255,33+sel_o*12, FLightGreen + BTransparent);
				}
			}
			
			uint8_t i,j;
			if (key==' ') {
				if (sel_x<10) {
					 
					j=sel_x+1;
					i=sel_y+1;
					if (map_revealed[i][j]==EMPTY) {

						undoBuffer[undoEnd].x = sel_x; 
						undoBuffer[undoEnd].y = sel_y;
						undoEnd++;
						if (undoEnd==undoStart) undoStart++;

						if (map_display[i][j]==EMPTY) {
							map_display[i][j]=WATER;
						} else if (map_display[i][j]==WATER) {
							map_display[i][j]=SHIP_UNDEFINED;
						} else {
							map_display[i][j]=EMPTY;
						}
						drawCell_int(j-1,i-1,map_display[i][j],map_correctness[i][j]);

						update_ship_tile(i,j);
						update_ship_tile(i+1,j);
						update_ship_tile(i-1,j);
						update_ship_tile(i,j+1);
						update_ship_tile(i,j-1);

						update_correctness();
						
						update_side_counts(i,j);

						if (update_legend_counts()) {
							status = WON;
						}
					}
				}
			
				if (sel_x==10) {
					if (sel_o==0) {
						key = 'm';
					}
					if (sel_o==1) {
						key = 'r';
					}
					if (sel_o==2) {
						key = 's';
					}
				}
			}                
			
			if (key=='P') {
				for (uint8_t i=1; i<11; i++) {
					for (uint8_t j=1; j<11; j++) {
						map_display[i][j] = map[i][j];
					}
				}
				status = WON;
				cheater = true;
			}

			if (key=='H' && sel_x!=10) {
				uint8_t j=sel_x+1;
				uint8_t i=sel_y+1;
				map_revealed[i][j] = map_display[i][j] = map[i][j];
				cheater = true;

				drawCell_int(j-1,i-1,map_display[i][j],map_correctness[i][j]);

				update_ship_tile(i,j);
				update_ship_tile(i+1,j);
				update_ship_tile(i-1,j);
				update_ship_tile(i,j+1);
				update_ship_tile(i,j-1);

				update_correctness();
				
				update_side_counts(i,j);

				if (update_legend_counts()) {
					status = WON;
				}
			}

			if (key=='T') {
				timer_init(60*60);
				cheater = true;
			}

			if (key=='m') {
				if (undoEnd!=undoStart) {
					undoEnd--;
					j=undoBuffer[undoEnd].x+1;
					i=undoBuffer[undoEnd].y+1;

					if (map_display[i][j]==EMPTY) {
						map_display[i][j]=SHIP_UNDEFINED;
					} else if (map_display[i][j]==WATER) {
						map_display[i][j]=EMPTY;
					} else {
						map_display[i][j]=WATER;
					}
					drawCell_int(j-1,i-1,map_display[i][j],map_correctness[i][j]);

					update_ship_tile(i,j);
					update_ship_tile(i+1,j);
					update_ship_tile(i-1,j);
					update_ship_tile(i,j+1);
					update_ship_tile(i,j-1);

					update_correctness();

					update_side_counts(i,j);

					update_legend_counts();
				}
			}                
		
			if (key == 'r') {
				sel_x=10;
				sel_o=1;
				rectangleColor(176,22+0*12,255,33+2*12, FGray + BTransparent);
				rectangleColor(176,22+sel_o*12,255,33+sel_o*12, FLightGreen + BTransparent);

				rectangleColor(176,22+3*12,255,33+4*12, FGray + BTransparent);

				rectangleColor(176,22+4*12,215,33+4*12, FGray + BTransparent);
				rectangleColor(215,22+4*12,255,33+4*12, FLightGreen + BTransparent);
				
				uint8_t yes_no=1;
				while (true) {
					wait_frame();
					key = msxhal_getch();
					if (key == 0x1D) {
						yes_no = 0;
						rectangleColor(176,22+4*12,215,33+4*12, FLightGreen + BTransparent);
						rectangleColor(215,22+4*12,255,33+4*12, FGray + BTransparent);
					}
					if (key == 0x1C) {
						yes_no = 1;
						rectangleColor(176,22+4*12,215,33+4*12, FGray + BTransparent);
						rectangleColor(215,22+4*12,255,33+4*12, FLightGreen + BTransparent);
					}
					if (key == ' ') {
						if (yes_no==0) {
							key = 'y';
						} else {
							key = 'n';
						}
					}		
					if (key == 'y') {
						rectangleColor(176,22+4*12,215,33+4*12, FLightGreen + BTransparent);
						rectangleColor(215,22+4*12,255,33+4*12, FGray + BTransparent);
						rectangle(0,0,16*10-1,16*10-1,0x00,FWhite+BBlack);
						set_map();
						undoStart = 0;
						undoEnd = 0;
						sel_x=0;
						sel_y=0;
					rectangleColor(176,22+0*12,255,33+2*12, FGray + BTransparent);
						break;						
					} 
					if (key == 'n' || key == 0x1E) {
						rectangleColor(176,22+4*12,215,33+4*12, FGray + BTransparent);
						rectangleColor(215,22+4*12,255,33+4*12, FLightGreen + BTransparent);
						break;						
					}
				}
				rectangleColor(176,22+3*12,255,33+4*12, FTransparent + BTransparent);
			}

			if (key == 's') {
				sel_x=10;
				sel_o=2;
				rectangleColor(176,22+0*12,255,33+2*12, FGray + BTransparent);
				rectangleColor(176,22+sel_o*12,255,33+sel_o*12, FLightGreen + BTransparent);

				rectangleColor(176,22+3*12,255,33+4*12, FGray + BTransparent);

				rectangleColor(176,22+4*12,215,33+4*12, FGray + BTransparent);
				rectangleColor(215,22+4*12,255,33+4*12, FLightGreen + BTransparent);
				
				uint8_t yes_no=1;
				while (true) {
					wait_frame();
					key = msxhal_getch();
					if (key == 0x1D) {
						yes_no = 0;
						rectangleColor(176,22+4*12,215,33+4*12, FLightGreen + BTransparent);
						rectangleColor(215,22+4*12,255,33+4*12, FGray + BTransparent);
					}
					if (key == 0x1C) {
						yes_no = 1;
						rectangleColor(176,22+4*12,215,33+4*12, FGray + BTransparent);
						rectangleColor(215,22+4*12,255,33+4*12, FLightGreen + BTransparent);
					}
					if (key == ' ') {
						if (yes_no==0) {
							key = 'y';
						} else {
							key = 'n';
						}
					}		
					if (key == 'y') {
						rectangleColor(176,22+4*12,215,33+4*12, FLightGreen + BTransparent);
						rectangleColor(215,22+4*12,255,33+4*12, FGray + BTransparent);
						status = LOST;
						rectangleColor(176,22+0*12,255,33+2*12, FGray + BTransparent);
						break;						
					} 
					if (key == 'n' || key == 0x1E) {
						rectangleColor(176,22+4*12,215,33+4*12, FGray + BTransparent);
						rectangleColor(215,22+4*12,255,33+4*12, FLightGreen + BTransparent);
						break;						
					}
				}
				rectangleColor(176,22+3*12,255,33+4*12, FTransparent + BTransparent);
			}		
		}
    	
    	wait_frame();
	}
	
}

void start_level() {
	
	while (true) {
		start_level_prepare();
		start_level_play();
		if (game_type==CAMPAIGN) {
			CALL_B(miscb, start_level_conclude_campaign);
			if (status==LOST) return;
		} else {
			CALL_B(miscb, start_level_conclude_free_play);
		}
	}
}
