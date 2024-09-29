#ifndef __GT_UI_H__
#define __GT_UI_H__


#include "../../GT-HMI-Engine/gt.h"


extern gt_obj_st * screen_home;
extern char update_sreen_status;

void gt_ui_init(void);
void send_pack(void);

void gt_init_screen_home(void);


#endif

