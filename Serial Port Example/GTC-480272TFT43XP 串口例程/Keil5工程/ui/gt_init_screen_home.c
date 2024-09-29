#include "gt_ui.h"
#include "bsp_uart.h"
#include "gt_input_number.h"
/** screen_home */
gt_obj_st * screen_home = NULL;
static gt_obj_st * rect1 = NULL;
static gt_obj_st * lab1 = NULL;
static gt_obj_st * lab2 = NULL;
static gt_obj_st * lab3 = NULL;
static gt_obj_st * lab4 = NULL;
static gt_obj_st * lab5 = NULL;
static gt_obj_st * lab6 = NULL;
static gt_obj_st * switch1 = NULL;
static gt_obj_st * inputNum1 = NULL;
static gt_obj_st * lab7 = NULL;
static gt_obj_st * imgbtn1 = NULL;
static gt_obj_st * imgbtn2 = NULL;
static gt_obj_st * imgbtn3 = NULL;
static gt_obj_st * inputNum2 = NULL;
static gt_obj_st * lab8 = NULL;
static gt_obj_st * imgbtn4 = NULL;
static gt_obj_st * imgbtn5 = NULL;
static gt_obj_st * inputNum3 = NULL;
static gt_obj_st * lab9 = NULL;
static gt_obj_st * imgbtn6 = NULL;
static gt_obj_st * slider1 = NULL;
char update_sreen_status;

/***********************
**数据包格式：头(0xAA)+设备启动状态+间隔时间+重复次数+工作温度+等待速度+包长度+校验位
**设备启动状态：0x0、0x1
**间隔时间：1~30
**重复次数：1~10
**工作温度：10~100
**等待速度：0~100
***********************/
void Refresh_New_Page(unsigned char *data)
{
	unsigned char verify=0 ,i=0;

	for ( i = 0; i < data[6]-1; i++)
	{
		verify += data[i];
	}
	if(data[0] == 0xaa && verify == data[7])//判断包头和校验和
	{
		if(data[1]==1)//设备启动
		{
			gt_obj_set_state(switch1, 1);
		}else if(data[1]==0)
		{
			gt_obj_set_state(switch1, 0);
		}
		gt_input_number_set_value(inputNum1, data[2]);//设置间隔时间
		gt_input_number_set_value(inputNum2,data[3]);//设置重复次数
		gt_input_number_set_value(inputNum3,data[4]);//设置工作温度
		gt_slider_set_pos(slider1, data[5]);//设置等待速度
		gt_disp_load_scr(screen_home);
	}

}

void send_pack(void)
{
	unsigned char buf[8]={0};

	buf[0] = 0xaa;//包头
	buf[1] = gt_obj_get_state(switch1);

	buf[2] = gt_input_number_get_value(inputNum1);//间隔时间
	buf[3] =  gt_input_number_get_value(inputNum2);//重复次数
	buf[4] =  gt_input_number_get_value(inputNum3);//工作温度
	buf[5] = gt_slider_get_pos(slider1);//等待速度·
	buf[6] = 8;//长度
	buf[7] = (unsigned char *)(buf[0] + buf[1] + buf[2] + buf[3]
		+ buf[4] + buf[5] + buf[6]);//校验位
	uart_send_pack(buf);
}

static void imgbtn1_0_cb(gt_event_st * e) {
	gt_input_number_increase(inputNum1);
	update_sreen_status=1;
}


static void imgbtn2_0_cb(gt_event_st * e) {
	gt_input_number_decrease(inputNum1);
	update_sreen_status=1;
}


static void imgbtn3_0_cb(gt_event_st * e) {
	gt_input_number_increase(inputNum2);
	update_sreen_status=1;
}


static void imgbtn4_0_cb(gt_event_st * e) {
	gt_input_number_decrease(inputNum2);
	update_sreen_status=1;
}


static void imgbtn5_0_cb(gt_event_st * e) {
	gt_input_number_increase(inputNum3);
	update_sreen_status=1;
}


static void imgbtn6_0_cb(gt_event_st * e) {
	gt_input_number_decrease(inputNum3);
	update_sreen_status=1;
}

 static void slider1_0_cb(gt_event_st * e) {
	update_sreen_status=1;
}

 static void switch1_0_cb(gt_event_st * e) {
	//update_sreen_status=1;
	send_pack();
}

void gt_init_screen_home(void)
{
	screen_home = gt_obj_create(NULL);//
	gt_screen_set_bgcolor(screen_home, gt_color_hex(0x000011));//设置背景颜色


	/** rect1 */
	rect1 = gt_rect_create(screen_home);
	gt_obj_set_pos(rect1, 10, 46);
	gt_obj_set_size(rect1, 460, 1);
	gt_rect_set_radius(rect1, 0);
	gt_rect_set_bg_color(rect1, gt_color_hex(0xffffff));
	gt_rect_set_color_border(rect1, gt_color_hex(0xffffff));
	gt_rect_set_fill(rect1, 1);
	gt_rect_set_border(rect1, 0);


	/** lab1 */
	lab1 = gt_label_create(screen_home);
	gt_obj_set_pos(lab1, 188, 6);
	gt_obj_set_size(lab1, 110, 24);
	gt_label_set_font_color(lab1, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab1, 24);
	gt_label_set_font_family_cn(lab1, 16);
	gt_label_set_font_align(lab1, GT_ALIGN_LEFT);
	gt_label_set_text(lab1, "设备管理");


	/** lab2 */
	lab2 = gt_label_create(screen_home);
	gt_obj_set_pos(lab2, 22, 61);
	gt_obj_set_size(lab2, 100, 24);
	gt_label_set_font_color(lab2, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab2, 20);
	gt_label_set_font_family_cn(lab2, 15);
	gt_label_set_font_align(lab2, GT_ALIGN_LEFT);
	gt_label_set_text(lab2, "设备启动");


	/** lab3 */
	lab3 = gt_label_create(screen_home);
	gt_obj_set_pos(lab3, 22, 102);
	gt_obj_set_size(lab3, 100, 24);
	gt_label_set_font_color(lab3, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab3, 20);
	gt_label_set_font_family_cn(lab3, 15);
	gt_label_set_font_align(lab3, GT_ALIGN_LEFT);
	gt_label_set_text(lab3, "间隔时间");


	/** lab4 */
	lab4 = gt_label_create(screen_home);
	gt_obj_set_pos(lab4, 22, 142);
	gt_obj_set_size(lab4, 100, 24);
	gt_label_set_font_color(lab4, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab4, 20);
	gt_label_set_font_family_cn(lab4, 15);
	gt_label_set_font_align(lab4, GT_ALIGN_LEFT);
	gt_label_set_text(lab4, "重复次数");


	/** lab5 */
	lab5 = gt_label_create(screen_home);
	gt_obj_set_pos(lab5, 22, 182);
	gt_obj_set_size(lab5, 100, 24);
	gt_label_set_font_color(lab5, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab5, 20);
	gt_label_set_font_family_cn(lab5, 15);
	gt_label_set_font_align(lab5, GT_ALIGN_LEFT);
	gt_label_set_text(lab5, "工作温度");


	/** lab6 */
	lab6 = gt_label_create(screen_home);
	gt_obj_set_pos(lab6, 22, 222);
	gt_obj_set_size(lab6, 100, 24);
	gt_label_set_font_color(lab6, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab6, 20);
	gt_label_set_font_family_cn(lab6, 15);
	gt_label_set_font_align(lab6, GT_ALIGN_LEFT);
	gt_label_set_text(lab6, "等待速度");


	/** switch1 */
	switch1 = gt_switch_create(screen_home);
	gt_obj_set_pos(switch1, 389, 66);
	gt_obj_set_size(switch1, 41, 20);
	gt_switch_set_color_act(switch1, gt_color_hex(0x13ce66));
	gt_switch_set_color_ina(switch1, gt_color_hex(0xebeef5));
	gt_switch_set_color_point(switch1, gt_color_hex(0xFFFFFF));
	gt_obj_set_state(switch1, 1);
	gt_obj_add_event_cb(switch1, switch1_0_cb, GT_EVENT_TYPE_INPUT_PROCESSED, NULL);

	/** inputNum1 */
	inputNum1 = gt_input_number_create(screen_home);
	gt_obj_set_pos(inputNum1, 344, 102);
	gt_obj_set_size(inputNum1, 36, 30);
	gt_input_number_set_font_color(inputNum1, gt_color_hex(0xffffff));
	gt_input_number_set_font_size(inputNum1, 24);
	gt_input_number_set_font_family_en(inputNum1, 40);
	gt_input_number_set_font_align(inputNum1, GT_ALIGN_LEFT);
	gt_input_number_set_value(inputNum1, 5);
	gt_input_number_set_step(inputNum1, 1);
	gt_input_number_set_min(inputNum1, 1);
	gt_input_number_set_max(inputNum1, 30);
	gt_input_number_set_fill_zero_front(inputNum1, false);
	gt_input_number_set_display_integer_length(inputNum1, 2);
	gt_input_number_set_display_decimal_length(inputNum1, 0);


	/** lab7 */
	lab7 = gt_label_create(screen_home);
	gt_obj_set_pos(lab7, 370, 107);
	gt_obj_set_size(lab7, 37, 24);
	gt_label_set_font_color(lab7, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab7, 16);
	gt_label_set_font_family_en(lab7, 38);
	gt_label_set_font_align(lab7, GT_ALIGN_LEFT);
	gt_label_set_text(lab7, "min");


	/** imgbtn1 */
	imgbtn1 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn1, 305, 108);
	gt_obj_set_size(imgbtn1, 20, 17);
	gt_imgbtn_set_src(imgbtn1, "f:img_20x17_1.png");
	gt_obj_add_event_cb(imgbtn1, imgbtn1_0_cb, GT_EVENT_TYPE_INPUT_PROCESSED, NULL);


	/** imgbtn2 */
	imgbtn2 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn2, 418, 108);
	gt_obj_set_size(imgbtn2, 20, 17);
	gt_imgbtn_set_src(imgbtn2, "f:img_20x17_2.png");
	gt_obj_add_event_cb(imgbtn2, imgbtn2_0_cb, GT_EVENT_TYPE_INPUT_PROCESSED, NULL);


	/** imgbtn3 */
	imgbtn3 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn3, 305, 148);
	gt_obj_set_size(imgbtn3, 20, 17);
	gt_imgbtn_set_src(imgbtn3, "f:img_20x17_1.png");
	gt_obj_add_event_cb(imgbtn3, imgbtn3_0_cb, GT_EVENT_TYPE_INPUT_PROCESSED, NULL);


	/** inputNum2 */
	inputNum2 = gt_input_number_create(screen_home);
	gt_obj_set_pos(inputNum2, 344, 143);
	gt_obj_set_size(inputNum2, 36, 30);
	gt_input_number_set_font_color(inputNum2, gt_color_hex(0xffffff));
	gt_input_number_set_font_size(inputNum2, 24);
	gt_input_number_set_font_family_en(inputNum2, 40);
	gt_input_number_set_font_align(inputNum2, GT_ALIGN_LEFT);
	gt_input_number_set_value(inputNum2, 6);
	gt_input_number_set_step(inputNum2, 1);
	gt_input_number_set_min(inputNum2, 1);
	gt_input_number_set_max(inputNum2, 10);
	gt_input_number_set_fill_zero_front(inputNum2, false);
	gt_input_number_set_display_integer_length(inputNum2, 2);
	gt_input_number_set_display_decimal_length(inputNum2, 0);


	/** lab8 */
	lab8 = gt_label_create(screen_home);
	gt_obj_set_pos(lab8, 374, 143);
	gt_obj_set_size(lab8, 30, 24);
	gt_label_set_font_color(lab8, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab8, 20);
	gt_label_set_font_family_cn(lab8, 15);
	gt_label_set_font_align(lab8, GT_ALIGN_LEFT);
	gt_label_set_text(lab8, "次");


	/** imgbtn4 */
	imgbtn4 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn4, 418, 148);
	gt_obj_set_size(imgbtn4, 20, 17);
	gt_imgbtn_set_src(imgbtn4, "f:img_20x17_2.png");
	gt_obj_add_event_cb(imgbtn4, imgbtn4_0_cb, GT_EVENT_TYPE_INPUT_PROCESSED, NULL);


	/** imgbtn5 */
	imgbtn5 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn5, 305, 188);
	gt_obj_set_size(imgbtn5, 20, 17);
	gt_imgbtn_set_src(imgbtn5, "f:img_20x17_1.png");
	gt_obj_add_event_cb(imgbtn5, imgbtn5_0_cb, GT_EVENT_TYPE_INPUT_PROCESSED, NULL);


	/** inputNum3 */
	inputNum3 = gt_input_number_create(screen_home);
	gt_obj_set_pos(inputNum3, 356, 183);
	gt_obj_set_size(inputNum3, 36, 24);
	gt_input_number_set_font_color(inputNum3, gt_color_hex(0xffffff));
	gt_input_number_set_font_size(inputNum3, 24);
	gt_input_number_set_font_family_en(inputNum3, 40);
	gt_input_number_set_font_align(inputNum3, GT_ALIGN_LEFT);
	gt_input_number_set_value(inputNum3, 72);
	gt_input_number_set_step(inputNum3, 1);
	gt_input_number_set_min(inputNum3, 10);
	gt_input_number_set_max(inputNum3, 100);
	gt_input_number_set_fill_zero_front(inputNum3, false);
	gt_input_number_set_display_integer_length(inputNum3, 2);
	gt_input_number_set_display_decimal_length(inputNum3, 0);


	/** lab9 */
	lab9 = gt_label_create(screen_home);
	gt_obj_set_pos(lab9, 388, 183);
	gt_obj_set_size(lab9, 37, 24);
	gt_label_set_font_color(lab9, gt_color_hex(0xffffff));
	gt_label_set_font_size(lab9, 24);
	gt_label_set_font_family_cn(lab9, 15);
	gt_label_set_font_family_en(lab9, 40);
	gt_label_set_font_align(lab9, GT_ALIGN_LEFT);
	gt_label_set_text(lab9, "℃");


	/** imgbtn6 */
	imgbtn6 = gt_imgbtn_create(screen_home);
	gt_obj_set_pos(imgbtn6, 418, 188);
	gt_obj_set_size(imgbtn6, 20, 17);
	gt_imgbtn_set_src(imgbtn6, "f:img_20x17_2.png");
	gt_obj_add_event_cb(imgbtn6, imgbtn6_0_cb, GT_EVENT_TYPE_INPUT_PROCESSED, NULL);


	/** slider1 */
	slider1 = gt_slider_create(screen_home);
	gt_obj_set_pos(slider1, 119, 222);
	gt_obj_set_size(slider1, 320, 30);
	gt_slider_set_start_end(slider1, 0, 100);
	gt_slider_set_pos(slider1, 5);
	gt_slider_set_color_act(slider1, gt_color_hex(0x409eff));
	gt_slider_set_color_ina(slider1, gt_color_hex(0xebeef5));
	gt_slider_set_tag_visible(slider1, 1);
	gt_slider_set_dir(slider1, GT_BAR_DIR_HOR_L2R);
	gt_obj_add_event_cb(slider1, slider1_0_cb, GT_EVENT_TYPE_INPUT_PROCESSED, NULL);


	gt_disp_load_scr(screen_home);
}

