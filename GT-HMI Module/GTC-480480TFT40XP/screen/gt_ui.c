#include "gt_ui.h"


static const gt_scr_list_st gt_scr_list[] = {
	{GT_ID_SCREEN_HOME, gt_init_screen_home},
	{GT_ID_SCREEN_1, gt_init_screen_1},
	{GT_ID_SCREEN_2, gt_init_screen_2},
	{GT_ID_SCREEN_3, gt_init_screen_3},
	{GT_ID_SCREEN_4, gt_init_screen_4},
	{GT_ID_SCREEN_5, gt_init_screen_5},
	{GT_ID_SCREEN_6, gt_init_screen_6},
	{GT_ID_SCREEN_7, gt_init_screen_7},
};

void gt_ui_init(void) {
	gt_project_encoding_set(1);




	gt_scr_stack_register_id_list(gt_scr_list, sizeof(gt_scr_list) / sizeof(gt_scr_list[0]), 20);
	gt_scr_stack_set_home_scr_id(GT_ID_SCREEN_HOME, false);
	gt_disp_stack_load_scr(GT_ID_SCREEN_HOME);
}

