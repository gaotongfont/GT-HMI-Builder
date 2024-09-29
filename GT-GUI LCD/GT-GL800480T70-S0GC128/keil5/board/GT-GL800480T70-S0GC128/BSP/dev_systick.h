#ifndef __DEV_SYSTICK_H__
#define __DEV_SYSTICK_H__

//----------------------------头文件依赖----------------------------//
#include "SWM341.h"

//----------------------------函数声明----------------------------//
void systick_init(void);
void swm_delay_ms(uint32_t ms);
void swm_delay_us(uint32_t us);
void swm_inctick(void);
uint32_t swm_gettick(void);

#endif //__DEV_SYSTICK_H__
