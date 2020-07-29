#include <common.h>

#ifdef MSX
inline static void get_char_and_joystick_placeholder(void) {
	
	__asm
	_get_char_and_joystick::
		
		in a,(#0xAA)
		and #0xF0       ; only change bits 0-3
		or #8           ; row 8
		out (#0xAA),a
		in a,(#0xA9)    ; read row into A
		xor #0xFF
		ld l,a

		ret
	__endasm;
}

#else
    char get_char_and_joystick() {
        return msxhal_getch();
    }
#endif

