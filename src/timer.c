#include <common.h>

bool timer_must_update;

uint8_t time_remaining_minutes_10;
uint8_t time_remaining_minutes_1;
uint8_t time_remaining_seconds_10;
uint8_t time_remaining_seconds_1;
uint8_t time_remaining_frames;

void timer_init_int(uint16_t seconds) {
    
    time_remaining_minutes_10 = 0;
    time_remaining_minutes_1 = 0;
    time_remaining_seconds_10 = 0;
    time_remaining_seconds_1 = 0;
    time_remaining_frames = 0;

    while (seconds>=600) {
        time_remaining_minutes_10++;
        seconds -= 600;
    }
    while (seconds>=60) {
        time_remaining_minutes_1++;
        seconds -= 60;
    }    
    while (seconds>=10) {
        time_remaining_seconds_10++;
        seconds -= 10;
    }
    time_remaining_seconds_1=seconds;
    timer_must_update = true;
}

bool timer_update_int() {
    
    if (time_remaining_frames==25) {timer_must_update = true; }
    
    if (time_remaining_frames) {
        time_remaining_frames--;
        return false;
    }
    timer_must_update = true;
    time_remaining_frames = (msxhal_get_interrupt_frequency()==MSX_FREQUENCY_60HZ?59:49);

    if (time_remaining_seconds_1) {
        time_remaining_seconds_1--;
        
        used_seconds++;
        if (used_seconds==60) {
            used_minutes++;
            used_seconds=0;
        }
        if (used_minutes==60) {
            used_hours++;
        }
        return false;
    }
    time_remaining_seconds_1=9;

    if (time_remaining_seconds_10) {
        time_remaining_seconds_10--;
        return false;
    }
    time_remaining_seconds_10=5;

    if (time_remaining_minutes_1) {
        time_remaining_minutes_1--;
        return false;
    }
    time_remaining_minutes_1=9;

    if (time_remaining_minutes_10) {
        time_remaining_minutes_10--;
        return false;
    }
    timer_init_int(0);
    return true;
}

static char msg[10];
const char *timer_get_string_int() {
    
    msg[0]='0'+time_remaining_minutes_10;
    msg[1]='0'+time_remaining_minutes_1;
    msg[2]=(time_remaining_frames > 25?':':' ');
    msg[3]='0'+time_remaining_seconds_10;
    msg[4]='0'+time_remaining_seconds_1;
    msg[5]=0;
    
    return msg;
}

static void setPointScratchPad(uint16_t xy) __z88dk_fastcall {
    
    uint8_t x = xy>>8;
    uint8_t y = xy&0xFF;

//    printf("%d %d\n", x, y);
    uint16_t offset = 10*(x/8) + y;
    scratchpad[offset] |= (128>>(x&7));
}


static void writeCharScratchPad(char cr) {
    
    yield();
    IN_MODULE( font_tiny, PAGE_D, {
    
        uint8_t c = cr-32;
        const uint16_t *begin = &font_tiny_pts[font_tiny_pos[c]];
        const uint16_t *end   = &font_tiny_pts[font_tiny_pos[c+1]];
        while (begin != end) {
            uint16_t xy = *begin++;
            setPointScratchPad(xy + ((textProperties.x&0xFF)<<8));
        }
        uint8_t len = font_tiny_len[c];
        textProperties.x += len;
    });
}

void write_timer_int(uint8_t color) __z88dk_fastcall {
    
    for (uint8_t i=0; i<10*5; i++) scratchpad[i]=0x00;

    timer_get_string_int();
    textProperties.x=0;
    const char *str = &msg[0];
    while (*str)
        writeCharScratchPad(*str++);

    for (uint8_t j=0; j<3; j++) {
        TMS99X8_setPtr(MODE2_ADDRESS_PG + 64*(32-3+j));
        for (uint8_t i=0; i<10; i++) {
            TMS99X8_write(scratchpad[j*10+i]);
        }
    }
    for (uint8_t j=0; j<3; j++) {
        TMS99X8_setPtr(MODE2_ADDRESS_CT + 64*(32-3+j));
        for (uint8_t i=0; i<10; i++) {
            TMS99X8_write(color);
        }
    }
}


void write_no_timer_int(uint8_t color) __z88dk_fastcall {
    
    for (uint8_t i=0; i<10*5; i++) scratchpad[i]=0x00;

    msg[0]='-';
    msg[1]='-';
    msg[2]=':';
    msg[3]='-';
    msg[4]='-';
    msg[5]=0;
    
    textProperties.x=0;
    const char *str = &msg[0];
    while (*str)
        writeCharScratchPad(*str++);

    for (uint8_t j=0; j<3; j++) {
        TMS99X8_setPtr(MODE2_ADDRESS_PG + 64*(32-3+j));
        for (uint8_t i=0; i<10; i++) {
            TMS99X8_write(scratchpad[j*10+i]);
        }
    }
    for (uint8_t j=0; j<3; j++) {
        TMS99X8_setPtr(MODE2_ADDRESS_CT + 64*(32-3+j));
        for (uint8_t i=0; i<10; i++) {
            TMS99X8_write(color);
        }
    }
}

