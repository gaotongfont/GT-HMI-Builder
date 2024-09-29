//----------------------------头文件依赖----------------------------//
#include "dev_touch.h"
#include "SWM341.h"
#if (1 == __RESOLUTION_TARGET__ || (480 == LCD_HDOT && 272 == LCD_VDOT) ) // 480*272

#include "TP_GT911.h"

#elif (2 == __RESOLUTION_TARGET__ || (480 == LCD_HDOT && 480 == LCD_VDOT) ) // 480*480

#if (0 == LCD_TYPE)
#include "TP_FT6336.h"

#elif (1 == LCD_TYPE)
#include "TP_CST826.h"

#endif //LCD_TYPE

#elif (3 == __RESOLUTION_TARGET__ || (800 == LCD_HDOT && 480 == LCD_VDOT) ) // 800*480

#include "TP_GT911.h"

#elif (4 == __RESOLUTION_TARGET__ || (1024 == LCD_HDOT && 600 == LCD_VDOT) ) // 1024*600

#if (0 == LCD_TYPE)bool
#include "TP_FT5206.h"

#elif (1 == LCD_TYPE)
#include "TP_GT911.h"

#endif //LCD_TYPE

#endif //__RESOLUTION_TARGET__

//----------------------------全局变量----------------------------//
tp_dev_t TP_Dev; //实例化触摸屏控制
/* 依靠 tp_dev_t 建立对 TP_IC 的抽象层 */

volatile BOOL Boot_Video_Flag = false; // 开机视频停止位

//----------------------------函数定义----------------------------//
//触摸INT中断方式
void GPIOD_Handler(void)
{
    if (EXTI_State(TP_GPIO_INT, TP_PIN_INT))
    {
        EXTI_Clear(TP_GPIO_INT, TP_PIN_INT);
        touch_read_points();
        Boot_Video_Flag = true;
    }
}

//读取触摸点函数
void touch_read_points(void)
{
    uint8_t res = 0;

#if (1 == __RESOLUTION_TARGET__ || (480 == LCD_HDOT && 272 == LCD_VDOT) ) // 480*272

    res = gt9x_read_points(&TP_Dev);

#elif (2 == __RESOLUTION_TARGET__ || (480 == LCD_HDOT && 480 == LCD_VDOT) ) // 480*480

#if (0 == LCD_TYPE)
    res = ft6336_read_points(&TP_Dev);

#elif (1 == LCD_TYPE)
    res = cst826_read_points(&TP_Dev);

#endif //LCD_TYPE

#elif (3 == __RESOLUTION_TARGET__ || (800 == LCD_HDOT && 480 == LCD_VDOT) ) // 800*480

    res = gt9x_read_points(&TP_Dev);

#elif (4 == __RESOLUTION_TARGET__ || (1024 == LCD_HDOT && 600 == LCD_VDOT) ) // 1024*600

#if (0 == LCD_TYPE)
    res = ft5206_read_points(&TP_Dev);

#elif (1 == LCD_TYPE)
    res = gt9x_read_points(&TP_Dev);

#endif //LCD_TYPE

#endif //__RESOLUTION_TARGET__
}

//触摸IC初始化函数
void touch_ic_init(void)
{
    uint8_t res = 0;

#if (1 == __RESOLUTION_TARGET__ || (480 == LCD_HDOT && 272 == LCD_VDOT) ) // 480*272

    res = gt9x_init();

#elif (2 == __RESOLUTION_TARGET__ || (480 == LCD_HDOT && 480 == LCD_VDOT) ) // 480*480

#if (0 == LCD_TYPE)
    res = ft6336_init();

#elif (1 == LCD_TYPE)
    res = cst826_init();

#endif //LCD_TYPE

#elif (3 == __RESOLUTION_TARGET__ || (800 == LCD_HDOT && 480 == LCD_VDOT) ) // 800*480

    res = gt9x_init();

#elif (4 == __RESOLUTION_TARGET__ || (1024 == LCD_HDOT && 600 == LCD_VDOT) ) // 1024*600

#if (0 == LCD_TYPE)
    res = ft5206_init();

#elif (1 == LCD_TYPE)
    res = gt9x_init();

#endif //LCD_TYPE

#endif //__RESOLUTION_TARGET__

#if 1 //中断方式
    GPIO_Init(TP_GPIO_INT, TP_PIN_INT, 0, 0, 0, 0);
    EXTI_Init(TP_GPIO_INT, TP_PIN_INT, EXTI_FALL_EDGE); //下降沿触发
    NVIC_EnableIRQ(GPIOD_IRQn);
    EXTI_Open(TP_GPIO_INT, TP_PIN_INT);
#endif
}
