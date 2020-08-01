#include "common.h"

uint8_t scratchpad[256];
Tpaged_isr paged_isr;

static void main_isr(void) { 
	if (paged_isr.f != nullptr) IN_SEGMENT(paged_isr.seg, PAGE_B, (*paged_isr.f)() ); 
}

int main(void) {

    // Normal initialization routine
    msxhal_init(); // Bare minimum initialization of the msx support 
    DI(); // This game has normally disabled interrupts. 

	rand16_seed(35134,31321);
	
  //msxhal_request60Hz();
    msxhal_enableR800();

    mapper_load_module(graphics, PAGE_C);

    paged_isr.f = nullptr;
    msxhal_install_isr(main_isr);      

	language = ENGLISH;
	language = SPANISH;

	while (true) {
		CALL_B(opening, start_opening);
		CALL_B(level, start_level);
	}

    return 0;
}

void write_message_2(uint8_t x, uint8_t y, const char *msg, uint8_t color) {

	yield();

	textProperties.color = color;
	textProperties.sz = 1;
	
	if(y<255) {
		textProperties.x = x;
		textProperties.y = y;
	}
	writeText(msg); 
}

void write_message_tiny(uint8_t x, uint8_t y, const char *msg, uint8_t color) {

	yield();
	
	const uint8_t font_segment = textProperties.font_segment;
	const uint16_t * font_pts = textProperties.font_pts;
	const uint16_t * font_pos = textProperties.font_pos;
	const uint8_t * font_len = textProperties.font_len;

	textProperties.font_segment = MODULE_SEGMENT(font_tiny, PAGE_D);
	textProperties.font_pts = font_tiny_pts;
	textProperties.font_pos = font_tiny_pos;
	textProperties.font_len = font_tiny_len;
	textProperties.faster = false;


	textProperties.color = color;
	textProperties.sz = 1;
	
	textProperties.x = x;
	textProperties.y = y;
	writeText(msg); 
	
	textProperties.font_segment = font_segment;
	textProperties.font_pts = font_pts;
	textProperties.font_pos = font_pos;
	textProperties.font_len = font_len;
	textProperties.faster = false;
}
