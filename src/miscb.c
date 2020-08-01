#include <common.h>



static uint8_t add_text(const char *msg, uint8_t pos) {
    while (*msg!=0) {
        if (*msg==' ') {
            scratchpad[pos++]='%';
            scratchpad[pos++]='2';
            scratchpad[pos++]='0';
        } else {
            scratchpad[pos++]=*msg;
        }
        msg++;
    } 
    return pos;
}

static bool test_achievement() {
    
    if (cheater == true) return false;
    if (rank == 5 && used_hours==0 && used_minutes<30) return true;
    if (rank == 7 && used_hours==0) return true;
    if (rank == 8 && used_hours<2) return true;
    if (rank == 9 && used_hours<2) return true;
    if (rank == 10) return true;
    return false;
}

static char msg_minutes[4];
static char msg_seconds[4];

void start_level_conclude_campaign() {

	music_paused = true;
	{
        IN_MODULE(psg, PAGE_C, {
            ayr_fade_out(+2);
        });
    }
	

	paged_isr.seg = MODULE_SEGMENT(level, PAGE_B);
	paged_isr.f = won_isr;

	SA[0].color = BTransparent;
	SA[1].color = BTransparent;
	SA[2].color = BTransparent;
	SA[3].color = BTransparent;
    TMS99X8_writeSpriteAttributes(0,SA);
	
	if (status==WON) {

		for (uint8_t i=1; i<11; i++) {
			for (uint8_t j=1; j<11; j++) {
				if (map_display[i][j] == EMPTY)
					map_display[i][j] = WATER;
				
                IN_MODULE(psg, PAGE_C, ayFX_afb(test_afb, MODULE_SEGMENT(test_afb,PAGE_D), 1, 15,0); );
                
				drawCell_int(j-1,i-1,map_display[i][j], 2);
				wait_frame();
			}
		}
		for (uint8_t i=1; i<11; i++) {
			for (uint8_t j=1; j<11; j++) {

                if (map_display[i][j]>WATER) 
                    IN_MODULE(psg, PAGE_C, ayFX_afb(test_afb, MODULE_SEGMENT(test_afb,PAGE_D), 9, 15,0);  );
				
				drawCell_int(j-1,i-1,map_display[i][j], 3);
				wait_frame();
			}
		}
	} else {
		for (uint8_t i=1; i<11; i++) {
			for (uint8_t j=1; j<11; j++) {
				map_display[i][j] = map[i][j];

                IN_MODULE(psg, PAGE_C, ayFX_afb(test_afb, MODULE_SEGMENT(test_afb,PAGE_D), 1, 15,0); );
				
				drawCell_int(j-1,i-1,map_display[i][j], 2);
				wait_frame();
			}
		}
	}


	write_message_2(176, 82, TEXT_PRESS_ANY_KEY[language], FWhite + BTransparent);

    music_paused = false;
    IN_MODULE(music, PAGE_D, 
        if (status==WON) {
            playlist = &playlists[PL_PROMOTION];
        } else {
            playlist = &playlists[PL_DEMOTION];
        }
    );

	uint8_t count = 0;
	while (msxhal_getch()) { }
    while (true) {
		wait_frame();
		count ++;
		if (count == 31) {
			rectangleColor(176,82,255,82+12, FTransparent + BTransparent);
		}
		if (count == 63) {
			count = 0;
			rectangleColor(176,82,255,82+12, FWhite + BTransparent);
		}
		if (msxhal_getch()) break;
    }
    
    rectangle(128-104,96-24,127+104,95+24,0x00,FWhite+BBlack);
    rectangle(128-104+1,96-24+1,127+104-1,95+24-1,0xFF,FWhite+BBlack);
    rectangle(128-104+2,96-24+2,127+104-2,95+24-2,0x00,FWhite+BBlack);
	if (status==WON) {
		rank++;
		write_message_2(128-100, 96-22, TEXT_PROMOTION[language], FWhite + BTransparent);
	} else {
		if (rank) {
			rank--;
			write_message_2(128-100, 96-22, TEXT_DEMOTION[language], FWhite + BTransparent);
		}
	}
	
	write_message_2(128-100, 96-6, TEXT_CURRENT_RANK[language], FWhite + BTransparent);
	write_message_2(128-100, 96-6+16, TEXT_RANKS[language][rank], FWhite + BTransparent);
    
    while (msxhal_getch()) { }
    while (!msxhal_getch()) wait_frame();
    
    if (status==WON && test_achievement()) { {
        
		IN_MODULE(music, PAGE_D, 
			playlist = &playlists[PL_ACHIEVEMENT];
		);
        
        IN_MODULE(psg, PAGE_C, {
            ayr_fade_out(+2);
        });

        rectangle(128-128,96-32,127+128-(QRSIZE+2),95+32,0x00,FWhite+BBlack);
        rectangle(128-128+1,96-32+1,127+128-1,95+32-1,0xFF,FWhite+BBlack);
        rectangle(128-128+2,96-32+2,127+128-2,95+32-2,0x00,FWhite+BBlack);
        
        {
            uint8_t uh = used_hours;
            uint8_t um = used_minutes;
            uint8_t us = used_seconds;
            
            while (uh--) um +=60;
            msg_minutes[0]='0';
            msg_minutes[1]='0';
            msg_minutes[2]='0';
            msg_minutes[3]=0;

            while (um>=100) {um-=100; msg_minutes[0]++;}
            while (um>= 10) {um-= 10; msg_minutes[1]++;}
            while (um>=  1) {um-=  1; msg_minutes[2]++;}

            msg_seconds[0]='0';
            msg_seconds[1]='0';
            msg_seconds[2]=0;

            while (us>= 10) {us-= 10; msg_seconds[0]++;}
            while (us>=  1) {us-=  1; msg_seconds[1]++;}
            
        }

        write_message_2(128-124, 96-30, TEXT_ACHIEVEMENT_0[language], FWhite + BTransparent);
        write_message_2(128-124, 96-14, TEXT_RANKS[language][0], FWhite + BTransparent);
        write_message_2(0, 255, TEXT_ACHIEVEMENT_1[language], FWhite + BTransparent);
        write_message_2(128-124, 96-14+16, TEXT_RANKS[language][rank], FWhite + BTransparent);
        write_message_2(0, 255, TEXT_ACHIEVEMENT_2[language], FWhite + BTransparent);
        write_message_2(128-124, 96-14+16+16, msg_minutes, FWhite + BTransparent);
        write_message_2(0, 255, TEXT_ACHIEVEMENT_3[language], FWhite + BTransparent);
        write_message_2(0, 255, msg_seconds, FWhite + BTransparent);
        write_message_2(0, 255, TEXT_ACHIEVEMENT_4[language], FWhite + BTransparent);

        write_message_2(253-(QRSIZE+2), 96-30, TEXT_SHARE[language], FWhite + BTransparent);

        IN_MODULE(qrcodegen, PAGE_D, {
        
            uint8_t pos  =  0;
            pos = add_text("https://twitter.com/intent/tweet?hashtags=sotanomsxbbs%2Canchorsaweighmsx&text=",pos);
            pos = add_text(TEXT_RANKS[language][rank],pos);
            pos = add_text(TEXT_ACHIEVEMENT_2[language],pos);
            pos = add_text(msg_minutes,pos);
            pos = add_text(TEXT_ACHIEVEMENT_3[language],pos);
            pos = add_text(msg_seconds,pos);
            pos = add_text(TEXT_ACHIEVEMENT_4[language],pos);
            scratchpad[pos]=0;
        
            qrcodegen((const char *)scratchpad);
        
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
                        setPointFG(coords.xy + (253-(QRSIZE+2))*256 + (95+30-(QRSIZE+2)));
                    }
                }
            }
        });
                        
        while (msxhal_getch()) { }
        while (!msxhal_getch()) wait_frame();
    } }

    if (rank==10) {
        
        {
            IN_MODULE(music, PAGE_D, 
                playlist = &playlists[PL_ENDING];
            );
	
            IN_MODULE(psg, PAGE_C, {
                ayr_fade_out(+2);
            });
        }
		rectangle(0,0,255,192,0x00,FWhite+BBlack);

        textProperties.font_segment = MODULE_SEGMENT(font_didone,PAGE_D);
        textProperties.font_pts = font_didone_pts;
        textProperties.font_pos = font_didone_pos;
        textProperties.font_len = font_didone_len;
        textProperties.space_between_lines = 14;
        textProperties.faster = true;
        
        if (cheater) {
            write_message_2(0,   0, TEXT_BAD_ENDING[language], FWhite+BBlack);
        } else {
            write_message_2(0,   0, TEXT_GOOD_ENDING[language], FWhite+BBlack);
        }
        
        wait_frame();
        while (msxhal_getch()) { }
        while (!msxhal_getch()) wait_frame();;

        mapper_load_module(join_color, PAGE_D);
	    TMS99X8_memcpy(MODE2_ADDRESS_CT + 0x0000, &join_color[0x0000], 0x1800);    
        mapper_load_module(join_pattern, PAGE_D);
	    TMS99X8_memcpy(MODE2_ADDRESS_PG + 0x0000, &join_pattern[0x0000], 0x1800);    

        if (cheater) {
            for (int16_t i=0; i<32; i+=2) {
                TMS99X8_memset(MODE2_ADDRESS_CT + 0x0000+64*i, 0x00, 64);    
                TMS99X8_memset(MODE2_ADDRESS_PG + 0x0000+64*i, 0x00, 64);    
                TMS99X8_memset(MODE2_ADDRESS_CT + 0x0800+64*i, 0x00, 64);    
                TMS99X8_memset(MODE2_ADDRESS_PG + 0x0800+64*i, 0x00, 64);    
                TMS99X8_memset(MODE2_ADDRESS_CT + 0x1000+64*i, 0x00, 64);    
                TMS99X8_memset(MODE2_ADDRESS_PG + 0x1000+64*i, 0x00, 64);    
            }
        }

        wait_frame();
        while (msxhal_getch()) { }
        while (!msxhal_getch()) wait_frame();;
        status = LOST;
    }

	music_paused = true;
	do {
        IN_MODULE(psg, PAGE_C, {
            ayr_fade_out(+2);
        });
    } while (false);
}


void start_level_conclude_free_play() {

	music_paused = true;
	
	IN_MODULE(psg, PAGE_C, {
		ayr_fade_out(+2);
	});
	

	paged_isr.seg = MODULE_SEGMENT(level, PAGE_B);
	paged_isr.f = won_isr;

	SA[0].color = BTransparent;
	SA[1].color = BTransparent;
	SA[2].color = BTransparent;
	SA[3].color = BTransparent;
    TMS99X8_writeSpriteAttributes(0,SA);
	
	if (status==WON) {

		for (uint8_t i=1; i<11; i++) {
			for (uint8_t j=1; j<11; j++) {
				if (map_display[i][j] == EMPTY)
					map_display[i][j] = WATER;

                IN_MODULE(psg, PAGE_C, ayFX_afb(test_afb, MODULE_SEGMENT(test_afb,PAGE_D), 1, 15,0); );
				
				drawCell_int(j-1,i-1,map_display[i][j], 2);
				wait_frame();
			}
		}
		for (uint8_t i=1; i<11; i++) {
			for (uint8_t j=1; j<11; j++) {

                if (map_display[i][j]>WATER) 
                    IN_MODULE(psg, PAGE_C, ayFX_afb(test_afb, MODULE_SEGMENT(test_afb,PAGE_D), 9, 15,0);  );
				
				drawCell_int(j-1,i-1,map_display[i][j], 3);
				wait_frame();
			}
		}
	} else {
		for (uint8_t i=1; i<11; i++) {
			for (uint8_t j=1; j<11; j++) {
				map_display[i][j] = map[i][j];
				
				drawCell_int(j-1,i-1,map_display[i][j], 2);
				wait_frame();
			}
		}
	}


	write_message_2(176, 82, TEXT_PRESS_ANY_KEY[language], FWhite + BTransparent);

    music_paused = false;
    IN_MODULE(music, PAGE_D, 
        if (status==WON) {
			playlist = &playlists[PL_PROMOTION];
        } else {
			playlist = &playlists[PL_DEMOTION];
        }
    );
    
	uint8_t count = 0;
    while (msxhal_getch()) { }
	while (true) {
		wait_frame();
		count ++;
		if (count == 31) {
			rectangleColor(176,82,255,82+12, FTransparent + BTransparent);
		}
		if (count == 63) {
			count = 0;
			rectangleColor(176,82,255,82+12, FWhite + BTransparent);
		}
		if (msxhal_getch()) break;
    }

	music_paused = true;
	{
        IN_MODULE(psg, PAGE_C, {
            ayr_fade_out(+2);
        });
    }
}
