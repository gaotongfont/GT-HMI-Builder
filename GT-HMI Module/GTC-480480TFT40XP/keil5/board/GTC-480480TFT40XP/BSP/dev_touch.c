//----------------------------头文件依赖----------------------------//
#include "dev_touch.h"
#include "gt911.h"



//----------------------------全局变量----------------------------//
tp_dev_t TP_Dev = {
	touch_ic_init,
	touch_read_points,
	0,
  0,
  0,
	0,
};//实例化触摸屏控制
/* 依靠 tp_dev_t 建立对 TP_IC 的抽象层 */


//----------------------------函数定义----------------------------//
////触摸INT中断方式
//void GPIOD_Handler(void)
//{
//    if (EXTI_State(TP_GPIO_INT, TP_PIN_INT))
//    {
//        EXTI_Clear(TP_GPIO_INT, TP_PIN_INT);
//        gt9x_read_points(&TP_Dev);
//    }
//}

//读取触摸点函数
uint8_t touch_read_points(void)
{
    uint8_t res;

    res = GT911_Scan(0);
		return res;


}

//触摸IC初始化函数
void touch_ic_init(void)
{

//#if (480 == LCD_HDOT && 272 == LCD_VDOT) // 480*272

//    res = gt9x_init();

//#elif (480 == LCD_HDOT && 480 == LCD_VDOT) // 480*480

//#if (0 == LCD_TYPE)
//    res = ft6336_init();

//#elif (1 == LCD_TYPE)
//    res = cst826_init();

//#endif //LCD_TYPE

//#elif (800 == LCD_HDOT && 480 == LCD_VDOT) // 800*480

    GT911_Init();
//#elif (1024 == LCD_HDOT && 600 == LCD_VDOT) // 1024*600

//#if (0 == LCD_TYPE)
//    res = ft5206_init();

//#elif (1 == LCD_TYPE)
//    res = gt9x_init();

//#endif //LCD_TYPE

//#endif //LCD_HDOT * LCD_VDOT

//	#if res //中断方式
//		GPIO_Init(TP_GPIO_INT, TP_PIN_INT, 0, 0, 0, 0);
//		EXTI_Init(TP_GPIO_INT, TP_PIN_INT, EXTI_FALL_EDGE); //下降沿触发
//		NVIC_EnableIRQ(GPIOD_IRQn);
//		EXTI_Open(TP_GPIO_INT, TP_PIN_INT);
//	#endif
}
