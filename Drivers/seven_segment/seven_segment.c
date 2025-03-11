#include <stdint.h>
#include "seven_segment.h"

void seven_seg_init(struct seven_seg *seven_seg, volatile unsigned char *port, volatile unsigned char *port_dir){
    seven_seg->port = port;
    seven_seg->port_dir = port_dir;
    
    *seven_seg->port_dir = 0x00;
    *seven_seg->port = 0xFF;
    
    static const uint8_t num_arr[11] = {
        0b01000000,
        0b01111001,
        0b00100100,
        0b00110000,
        0b00011001,
        0b00010010,
        0b00000010,
        0b01111000,
        0b00000000,
        0b00011000,
        0b01111111
    };
    
    seven_seg->num_arr = num_arr;
    
}

void seven_seg_set_num(struct seven_seg *seven_seg, uint8_t value){

    if(value <= 9){
        
        *seven_seg->port = seven_seg->num_arr[value] | (*seven_seg->port & 0x80);
    }
    else{
        *seven_seg->port = seven_seg->num_arr[10] | (*seven_seg->port & 0x80);
    }
}

void seven_seg_set_num_dp(struct seven_seg *seven_seg, uint8_t value, uint8_t dp){

    if(value <= 9){
        
        *seven_seg->port = seven_seg->num_arr[value] | dp << 7;
    }
    else{
        *seven_seg->port = seven_seg->num_arr[10] | dp << 7;
    }
}

