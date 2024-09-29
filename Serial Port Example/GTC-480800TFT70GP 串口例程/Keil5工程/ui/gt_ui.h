#ifndef __GT_UI_H__
#define __GT_UI_H__


#include "../../GT-HMI-Engine/gt.h"


extern gt_obj_st * screen_home;
extern char update_sreen_status;

void gt_ui_init(void);
void send_pack(void);
void Refresh_New_Page(unsigned char *data);

gt_obj_st * gt_init_screen_home(void);


typedef enum {
        GT_ID_SCREEN_HOME = 0,
} gt_scr_id_et;



#endif

