#include "gt_ui.h"


static const gt_scr_list_st gt_scr_list[] = {
	{GT_ID_SCREEN_HOME, gt_init_screen_home},
	{GT_ID_SCREEN_RECORDING, gt_init_screen_recording},
	{GT_ID_SCREEN_SETUP, gt_init_screen_setup},
	{GT_ID_SCREEN_SUBTITLE, gt_init_screen_subtitle},
	{GT_ID_SCREEN_JS, gt_init_screen_js},
	{GT_ID_SCREEN_XG, gt_init_screen_xg},
	{GT_ID_SCREEN_YS, gt_init_screen_ys},
	{GT_ID_SCREEN_NC, gt_init_screen_nc},
	{GT_ID_SCREEN_FAIL, gt_init_screen_fail},
	{GT_ID_SCREEN_GL, gt_init_screen_gl},
	{GT_ID_SCREEN_JZ, gt_init_screen_jz},
};

void gt_ui_init(void) {


	gt_scr_stack_register_id_list(gt_scr_list, sizeof(gt_scr_list) / sizeof(gt_scr_list[0]), 20);
	gt_scr_stack_set_home_scr_id(GT_ID_SCREEN_HOME, false);
	gt_disp_stack_load_scr(GT_ID_SCREEN_HOME);
}

