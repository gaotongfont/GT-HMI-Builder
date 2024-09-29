#include "touch.h"
#include "SWM341.h"
#include "dev_systick.h"
#include "stdlib.h"
#include "math.h"
#include "ugui.h"
#include "bsp_lcd_rgb.h"
#include "lcd_show.h"

#define TOUCH_XFAC -0.130680
#define TOUCH_YFAC -0.090237
#define TOUCH_XOFF 507
#define TOUCH_YOFF 315

uint8_t FlagAdjusted = false;
char Buf[20] = { 0 };
_m_tp_dev tp_dev =
{
	TP_Init,
	TP_Scan,
	TP_Adjust,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};


uint8_t CMD_RDX = 0X90;//1 101 0000   //XP,XN
uint8_t CMD_RDY = 0XD0;//1 001 0000   //YP,YN




void TP_Write_Byte(uint8_t num)
{
	uint8_t count = 0;
	for (count = 0;count < 8;count++) {
		if (num & 0x80) {
			TDIN_Set;
		}
		else {
			TDIN_Clr;
		}

		num <<= 1;
		TCLK_Clr;
		swm_delay_us(1);
		TCLK_Set;
	}
}



uint16_t TP_Read_AD(uint8_t CMD)
{
	uint8_t count = 0;
	uint16_t Num = 0;
	TCLK_Clr;
	TDIN_Clr;
	TCS_Clr;
	TP_Write_Byte(CMD);
	swm_delay_us(6);
	TCLK_Clr;
	swm_delay_us(1);
	TCLK_Set;
	swm_delay_us(1);
	TCLK_Clr;
	for (count = 0;count < 16;count++) {
		Num <<= 1;
		TCLK_Clr;

		swm_delay_us(1);
		TCLK_Set;
		if (GPIO_GetBit(PORT_TSDI, PIN_TSDI)) {
			Num++;
		}
		else {
		}
	}
	Num >>= 4;

	TCS_Set;
	return(Num);
}


#define READ_TIMES 5
#define LOST_VAL 1
uint16_t TP_Read_XOY(uint8_t xy)
{
	uint16_t i, j;
	uint16_t buf[READ_TIMES];
	uint16_t sum = 0;
	uint16_t temp;
	for (i = 0;i < READ_TIMES;i++) {
		buf[i] = TP_Read_AD(xy);
	}
	for (i = 0;i < READ_TIMES - 1; i++) {
		for (j = i + 1;j < READ_TIMES;j++) {
			if (buf[i] > buf[j]) {
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}
	sum = 0;
	for (i = LOST_VAL;i < READ_TIMES - LOST_VAL;i++) {
		sum += buf[i];
	}
	temp = sum / (READ_TIMES - 2 * LOST_VAL);
	return temp;
}



uint8_t TP_Read_XY(uint16_t * x, uint16_t * y)
{
	uint16_t xtemp, ytemp;
	xtemp = TP_Read_XOY(CMD_RDX);
	ytemp = TP_Read_XOY(CMD_RDY);
	//if(xtemp<100||ytemp<100)return 0;
	*x = xtemp;
	*y = ytemp;
	return 1;
}


#define ERR_RANGE 50 //��Χ
uint8_t TP_Read_XY2(uint16_t * x, uint16_t * y)
{
	uint16_t x1, y1;
	uint16_t x2, y2;
	uint8_t flag;

	flag = TP_Read_XY(&x1, &y1);
	if (flag == 0)return(0);

	flag = TP_Read_XY(&x2, &y2);
	if (flag == 0)return(0);
	if (((x2 <= x1 && x1 < x2 + ERR_RANGE) || (x1 <= x2 && x2 < x1 + ERR_RANGE))
		&& ((y2 <= y1 && y1 < y2 + ERR_RANGE) || (y1 <= y2 && y2 < y1 + ERR_RANGE))) {
		*x = (x1 + x2) / 2;
		*y = (y1 + y2) / 2;

		return 1;
	}
	else return 0;
}


uint8_t TP_Get_Adjdata(void)
{

	tp_dev.xfac = (float)(-0.089859);
	printf("tp_dev.xfac %f     ", tp_dev.xfac);

	tp_dev.yfac = (float)(-0.128056);
	printf("tp_dev.yfac %f    ", tp_dev.yfac);
	tp_dev.xoff = 337;
	printf("tp_dev.xoff %d    ", tp_dev.xoff);

	tp_dev.yoff = 509;
	printf("tp_dev.yoff %d    ", tp_dev.yoff);

	tp_dev.touchtype = 0;
	printf("tp_dev.touchtype %d    ", tp_dev.touchtype);
	if (tp_dev.touchtype) {
		CMD_RDX = 0X90;
		CMD_RDY = 0XD0;
	}
	else {
		CMD_RDX = 0XD0;
		CMD_RDY = 0X90;
	}
	return 1;

	return 0;
}



uint8_t TP_Scan(uint8_t tp)
{
	u16 temp1, temp2;
	tp_dev.xfac = TOUCH_XFAC;
	tp_dev.yfac = TOUCH_YFAC;
	tp_dev.xoff = TOUCH_XOFF;
	tp_dev.yoff = TOUCH_YOFF;
	//INT(TPEN)
	if (GPIO_GetBit(PORT_TPEN, PIN_TPEN) == 0) {
		if (tp == 1) {

			TP_Read_XY2(&tp_dev.x[0], &tp_dev.y[0]);
		}
		else if (TP_Read_XY2(&tp_dev.x[0], &tp_dev.y[0])) {
			temp1 = tp_dev.x[0];
			temp2 = tp_dev.y[0];
			tp_dev.x[0] = tp_dev.xfac * temp2 + tp_dev.xoff;
			tp_dev.y[0] = tp_dev.yfac * temp1 + tp_dev.yoff;
			sprintf(Buf, "X:%d,Y:%d", tp_dev.x[0], tp_dev.y[0]);
		}

		if ((tp_dev.status & TP_PRES_DOWN) == 0) {
			tp_dev.status = TP_PRES_DOWN | TP_CATH_PRES;
			tp_dev.x[4] = tp_dev.x[0];
			tp_dev.y[4] = tp_dev.y[0];
		}
	}
	else {

		if (tp_dev.status & TP_PRES_DOWN) {
			tp_dev.status &= ~(1 << 7);
		}
		else {
			tp_dev.x[4] = 0;
			tp_dev.y[4] = 0;
			tp_dev.x[0] = 0xffff;
			tp_dev.y[0] = 0xffff;
		}
	}
	return tp_dev.status & TP_PRES_DOWN;
}









uint8_t TP_Init(void)
{
	//TSCL
	GPIO_Init(PORT_TSCL, PIN_TSCL, 1, 0, 0, 0);
	//SDA(MOSI)
	GPIO_Init(PORT_TSDO, PIN_TSDO, 1, 0, 0, 0);
	//INT(TPEN)
	GPIO_Init(PORT_TPEN, PIN_TPEN, 0, 1, 0, 0);

	EXTI_Init(PORT_TPEN, PIN_TPEN, EXTI_FALL_EDGE);
	NVIC_EnableIRQ(GPIOD_IRQn);
	EXTI_Open(PORT_TPEN, PIN_TPEN);

	//RST(CS)
	GPIO_Init(PORT_TCS, PIN_TCS, 1, 1, 0, 0);
	//MISO
	GPIO_Init(PORT_TSDI, PIN_TSDI, 0, 0, 0, 0);

	TP_Read_XY(&tp_dev.x[0], &tp_dev.y[0]);

	//TP_Get_Adjdata();

	return 1;
}

char TP_REMIND_MSG_TBL[10] = "press";



uint16_t pos_temp[4][2];
void TP_Adjust(void)
{

	uint8_t cnt = 0;
	uint16_t d1, d2;
	uint32_t tem1, tem2;
	float fac;
	uint16_t outtime = 0;

	//    LCD_Clear(WHITE);

	POINT_COLOR = C_BLACK;
	LCD_ShowString(40, 40, 160, 100, 16, (uint8_t *)TP_REMIND_MSG_TBL);
	lcd_draw_point(20, 20, C_RED);
	tp_dev.status = 0;
	tp_dev.xfac = 0;
	while (1) {
		TP_Scan(1);
		if ((tp_dev.status & 0xc0) == TP_CATH_PRES) {
			outtime = 0;
			tp_dev.status &= ~(1 << 6);

			pos_temp[cnt][0] = tp_dev.x[0];
			pos_temp[cnt][1] = tp_dev.y[0];
			cnt++;

			switch (cnt) {
			case 1:
				LCD_Draw_color_Circle(20, 20, 10, C_BLUE);
				lcd_draw_point(20, 20, C_WHITE);
				lcd_draw_point(LCD_WIDTH - 20, 20, C_RED);
				LCD_ShowString(40, 40, 160, 100, 16, (uint8_t *)TP_REMIND_MSG_TBL);
				break;
			case 2:
				LCD_Draw_color_Circle(LCD_WIDTH - 20, 20, 10, C_BLUE);
				lcd_draw_point(LCD_WIDTH - 20, 20, C_WHITE);
				lcd_draw_point(20, LCD_HEIGTH - 20, C_RED);
				break;
			case 3:
				LCD_Draw_color_Circle(20, LCD_HEIGTH - 20, 10, C_BLUE);
				lcd_draw_point(20, lcddev.height - 20, C_WHITE);
				lcd_draw_point(LCD_WIDTH - 20, LCD_HEIGTH - 20, C_RED);
				break;
			case 4:
				LCD_Draw_color_Circle(LCD_WIDTH - 20, LCD_HEIGTH - 20, 10, C_BLUE);

				tem1 = abs(pos_temp[0][0] - pos_temp[1][0]); //x1-x2
				tem2 = abs(pos_temp[0][1] - pos_temp[1][1]); //y1-y2
				tem1 *= tem1;
				tem2 *= tem2;
				d1 = sqrt(tem1 + tem2);

				tem1 = abs(pos_temp[2][0] - pos_temp[3][0]); //x3-x4
				tem2 = abs(pos_temp[2][1] - pos_temp[3][1]); //y3-y4
				tem1 *= tem1;
				tem2 *= tem2;
				d2 = sqrt(tem1 + tem2);
				fac = (float)d1 / d2;
				if (fac < 0.9 || fac > 1.1 || d1 == 0 || d2 == 0) {
					cnt = 0;
					lcd_draw_point(LCD_WIDTH - 20, LCD_HEIGTH - 20, C_WHITE);                                                                                           //�����?4
					lcd_draw_point(20, 20, C_RED);                                                                                                                            //����1
					//                    TP_Adj_Info_Show(pos_temp[0][0], pos_temp[0][1], pos_temp[1][0], pos_temp[1][1], pos_temp[2][0], pos_temp[2][1], pos_temp[3][0], pos_temp[3][1], fac * 100); //��ʾ����
					continue;
				}
				tem1 = abs(pos_temp[0][0] - pos_temp[2][0]); //x1-x3
				tem2 = abs(pos_temp[0][1] - pos_temp[2][1]); //y1-y3
				tem1 *= tem1;
				tem2 *= tem2;
				d1 = sqrt(tem1 + tem2);

				tem1 = abs(pos_temp[1][0] - pos_temp[3][0]); //x2-x4
				tem2 = abs(pos_temp[1][1] - pos_temp[3][1]); //y2-y4
				tem1 *= tem1;
				tem2 *= tem2;
				d2 = sqrt(tem1 + tem2);
				fac = (float)d1 / d2;
				if (fac < 0.9 || fac > 1.1) {
					cnt = 0;
					lcd_draw_point(LCD_WIDTH - 20, LCD_HEIGTH - 20, C_WHITE);                                                                                           //�����?4
					lcd_draw_point(20, 20, C_RED);                                                                                                                            //����1
					//TP_Adj_Info_Show(pos_temp[0][0], pos_temp[0][1], pos_temp[1][0], pos_temp[1][1], pos_temp[2][0], pos_temp[2][1], pos_temp[3][0], pos_temp[3][1], fac * 100); //��ʾ����
					continue;
				}


				tem1 = abs(pos_temp[1][0] - pos_temp[2][0]); //x1-x3
				tem2 = abs(pos_temp[1][1] - pos_temp[2][1]); //y1-y3
				tem1 *= tem1;
				tem2 *= tem2;
				d1 = sqrt(tem1 + tem2);

				tem1 = abs(pos_temp[0][0] - pos_temp[3][0]); //x2-x4
				tem2 = abs(pos_temp[0][1] - pos_temp[3][1]); //y2-y4
				tem1 *= tem1;
				tem2 *= tem2;
				d2 = sqrt(tem1 + tem2);
				fac = (float)d1 / d2;
				if (fac < 0.9 || fac > 1.1) {
					cnt = 0;
					lcd_draw_point(lcddev.width - 20, lcddev.height - 20, C_WHITE);                                                                                           //�����?4
					lcd_draw_point(20, 20, C_RED);                                                                                                                            //����1
					//TP_Adj_Info_Show(pos_temp[0][0], pos_temp[0][1], pos_temp[1][0], pos_temp[1][1], pos_temp[2][0], pos_temp[2][1], pos_temp[3][0], pos_temp[3][1], fac * 100); //��ʾ����
					continue;
				}


				tp_dev.yfac = (float)(LCD_WIDTH - 40) / (pos_temp[1][0] - pos_temp[0][0]);
				tp_dev.yoff = (LCD_WIDTH - tp_dev.yfac * (pos_temp[1][0] + pos_temp[0][0])) / 2;

				tp_dev.xfac = (float)(LCD_HEIGTH - 40) / (pos_temp[2][1] - pos_temp[0][1]);
				tp_dev.xoff = (LCD_HEIGTH - tp_dev.xfac * (pos_temp[2][1] + pos_temp[0][1])) / 2;
				if (fabs(tp_dev.xfac) > 2 || fabs(tp_dev.yfac) > 2) {
					cnt = 0;
					lcd_draw_point(lcddev.width - 20, lcddev.height - 20, C_WHITE);
					lcd_draw_point(20, 20, C_RED);
					LCD_ShowString(40, 26, lcddev.width, lcddev.height, 16, "TP Need readjust!");
					tp_dev.touchtype = !tp_dev.touchtype;
					if (tp_dev.touchtype) {
						CMD_RDX = 0X90;
						CMD_RDY = 0XD0;
					}
					else {
						CMD_RDX = 0XD0;
						CMD_RDY = 0X90;
					}
					UG_FillScreen(C_WHITE);
					lcd_draw_point(20, 20, C_RED);
					continue;
				}
				POINT_COLOR = C_BLUE;
				UG_FillScreen(C_WHITE);
				LCD_ShowString(35, 110, lcddev.width, lcddev.height, 16, "Touch Screen Adjust OK!");
				swm_delay_ms(1000);
				UG_FillScreen(C_WHITE);

				FlagAdjusted = true;
				return;
			}
		}
		swm_delay_ms(10);
		outtime++;
		if (outtime > 2000) {
			//            LCD_Clear(WHITE);
						//break;
		}
	}

}
void RTP_Read(void)
{
	tp_dev.scan(0);
	if (tp_dev.status & TP_PRES_DOWN) {
		//		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		//			{
		//				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)
		//
		//			}

	}
	else
		swm_delay_ms(100);
}


void GPIOM_Handler(void)
{
	if (EXTI_State(PORT_TPEN, PIN_TPEN))
		EXTI_Clear(PORT_TPEN, PIN_TPEN);
	if (FlagAdjusted == true) {
		tp_dev.scan(0);
	}
	else {
		tp_dev.scan(1);
		UG_PutString(180, 180, "No ready");
	}
}
