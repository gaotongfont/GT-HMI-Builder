//----------------------------头文件依赖----------------------------//
#include "dev_systick.h"

//----------------------------变量定义----------------------------//
static volatile uint32_t Systick_Time = 0; // Timer ticks

//----------------------------函数定义----------------------------//
void systick_init(void)
{
    /* SystemFrequency / 1000   1ms中断一次 */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while (1)
            ;
    }
}

void swm_inctick(void)
{
    ++Systick_Time;
}

uint32_t swm_gettick(void)
{
    return Systick_Time;
}

void swm_delay_ms(uint32_t ms)
{
    uint32_t tickstart = 0;
    tickstart = swm_gettick();
    while ((swm_gettick() - tickstart) < ms)
        ;
}

void swm_delay_us(uint32_t us)
{
#if 0
    uint32_t delta;
    /* 获得延时经过的 tick 数 */
    us = us * ( (SysTick->LOAD) / (1000) );
    /* 获得当前时间 */
    delta = SysTick->VAL;
    /* 循环获得当前时间，直到达到指定的时间后退出循环 */
    while (delta - (SysTick->VAL) < us)
		;

#else
    uint32_t ticks = 0;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;
    /* 获得延时经过的 tick 数 */
    ticks = us * reload / 1000;
    /* 获得当前时间 */
    told = SysTick->VAL;
    for (; ; )
    {
        /* 循环获得当前时间，直到达到指定的时间后退出循环 */
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            tcnt += ( (tnow < told) ? (told - tnow) : (reload - tnow + told) );
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
#endif
}

__WEAK void SysTick_Handler_cb(void)
{
}

void SysTick_Handler(void)
{
    swm_inctick();
    SysTick_Handler_cb();
}

/*********************************************END OF FILE************************************************/
