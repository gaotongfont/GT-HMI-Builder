#ifndef __DEV_SYSTICK_H__
#define __DEV_SYSTICK_H__

//----------------------------ͷ�ļ�����----------------------------//
#include "SWM341.h"

//----------------------------��������----------------------------//
void systick_init(void);
void swm_delay_ms(uint32_t ms);
void swm_delay_us(uint32_t us);
void swm_inctick(void);
uint32_t swm_gettick(void);

#endif //__DEV_SYSTICK_H__
