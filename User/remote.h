#ifndef _REMOTE_H_
#define _REMOTE_H_

#include <stdint.h>

typedef struct
{
    int16_t ch0;
    int16_t ch1;
    int16_t ch2;
    int16_t ch3;
    uint8_t  s1;
    uint8_t  s2;
} RC;
typedef struct
 {
    int16_t x;
    int16_t y;
    int16_t z;
    uint8_t press_l;
    uint8_t press_r;
 } mouse;
typedef struct
 {
    uint16_t v;
 }key;
 #define RC_FRAME_LENGTH 18
extern RC rc_ctrl;
extern mouse mouse_ctrl;
extern key key_ctrl;
extern uint8_t dbus_buf[18];
void Remote_Decode(void);
void Remote_Init(void);
#endif
