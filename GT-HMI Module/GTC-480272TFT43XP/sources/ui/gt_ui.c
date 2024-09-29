#include "gt_ui.h"


static const gt_scr_list_st gt_scr_list[] = {
	{GT_ID_SCREEN_HOME, gt_init_screen_home},
	{GT_ID_SCREEN_HOME2, gt_init_screen_home2},
	{GT_ID_SCREEN_HOME3, gt_init_screen_home3},
};

void gt_ui_init(void) {


	gt_scr_stack_register_id_list(gt_scr_list, sizeof(gt_scr_list) / sizeof(gt_scr_list[0]), 20);
	gt_scr_stack_set_home_scr_id(GT_ID_SCREEN_HOME, false);
	gt_disp_stack_load_scr(GT_ID_SCREEN_HOME);
}

