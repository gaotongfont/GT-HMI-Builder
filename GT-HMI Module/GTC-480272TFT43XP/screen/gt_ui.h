#ifndef __GT_UI_H__
#define __GT_UI_H__


#include "../../GT-HMI-Engine/gt.h"


extern gt_obj_st * screen_home;
extern gt_obj_st * screen_home2;
extern gt_obj_st * screen_home3;


void gt_ui_init(void);


gt_obj_st * gt_init_screen_home(void);
gt_obj_st * gt_init_screen_home2(void);
gt_obj_st * gt_init_screen_home3(void);


typedef enum {
        GT_ID_SCREEN_HOME = 0,
        GT_ID_SCREEN_HOME2 = 1,
        GT_ID_SCREEN_HOME3 = 2,
} gt_scr_id_et;



#endif

