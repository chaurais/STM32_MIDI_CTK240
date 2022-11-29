#ifndef __STARTUP_H__
#define __STARTUP_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f1xx.h"

void initialize(void);
void setup(void);
void keypad_scan(void);
void key_pressed(void);
void key_unpressed();
void beep(uint8_t Qte, uint16_t On, uint16_t Off);

#ifdef __cplusplus
}
#endif

#endif /* __STARTUP_H__ */
