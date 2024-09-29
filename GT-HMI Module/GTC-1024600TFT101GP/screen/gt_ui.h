#ifndef __GT_UI_H__
#define __GT_UI_H__


#include "../../GT-HMI-Engine/gt.h"


extern gt_obj_st * screen_home;
extern gt_obj_st * screen_1;
extern gt_obj_st * screen_2;
extern gt_obj_st * screen_3;
extern gt_obj_st * screen_4;
extern gt_obj_st * screen_5;
extern gt_obj_st * screen_6;
extern gt_obj_st * screen_7;
extern gt_obj_st * screen_8;
extern gt_obj_st * screen_9;
extern gt_obj_st * screen_10;
extern gt_obj_st * screen_11;


void gt_ui_init(void);


gt_obj_st * gt_init_screen_home(void);
gt_obj_st * gt_init_screen_1(void);
gt_obj_st * gt_init_screen_2(void);
gt_obj_st * gt_init_screen_3(void);
gt_obj_st * gt_init_screen_4(void);
gt_obj_st * gt_init_screen_5(void);
gt_obj_st * gt_init_screen_6(void);
gt_obj_st * gt_init_screen_7(void);
gt_obj_st * gt_init_screen_8(void);
gt_obj_st * gt_init_screen_9(void);
gt_obj_st * gt_init_screen_10(void);
gt_obj_st * gt_init_screen_11(void);


typedef enum {
        GT_ID_SCREEN_HOME = 0,
        GT_ID_SCREEN_1 = 1,
        GT_ID_SCREEN_2 = 2,
        GT_ID_SCREEN_3 = 3,
        GT_ID_SCREEN_4 = 4,
        GT_ID_SCREEN_5 = 5,
        GT_ID_SCREEN_6 = 6,
        GT_ID_SCREEN_7 = 7,
        GT_ID_SCREEN_8 = 8,
        GT_ID_SCREEN_9 = 9,
        GT_ID_SCREEN_10 = 10,
        GT_ID_SCREEN_11 = 11,
} gt_scr_id_et;



#endif

