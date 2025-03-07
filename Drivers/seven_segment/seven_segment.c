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
void seven_seg_set_num(struct seven_seg *seven_seg, uint8_t value, uint8_t dp){

    if(value <= 9){
        
        *seven_seg->port = seven_seg->num_arr[value] | dp << 7;
    }
    else{
        *seven_seg->port = seven_seg->num_arr[10] | dp << 7;
    }
//    switch(value){
//        case 0:
//            *seven_seg->port = 0b01000000;
//            break;
//        case 1:
//            *seven_seg->port = 0b01111001;
//            break;
//        case 2:
//            *seven_seg->port = 0b00100100;
//            break;
//        case 3:
//            *seven_seg->port = 0b00110000;
//            break;
//        case 4:
//            *seven_seg->port = 0b00011001;
//            break;
//        case 5:
//            *seven_seg->port = 0b00010010;
//            break;
//        case 6:
//            *seven_seg->port = 0b00000010;
//            break;
//        case 7:
//            *seven_seg->port = 0b01111000;
//            break;
//        case 8:
//            *seven_seg->port = 0b00000000;
//            break;
//        case 9:
//            *seven_seg->port = 0b00011000;
//            break;
//        default:
//            *seven_seg->port = 0b01111111;
//            break;
//    }
}