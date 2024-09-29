#ifndef __GT_UI_H__
#define __GT_UI_H__


#include "../../GT-HMI-Engine/gt.h"


extern gt_obj_st * screen_home;
extern gt_obj_st * screen_recording;
extern gt_obj_st * screen_setup;
extern gt_obj_st * screen_subtitle;
extern gt_obj_st * screen_js;
extern gt_obj_st * screen_xg;
extern gt_obj_st * screen_ys;
extern gt_obj_st * screen_nc;
extern gt_obj_st * screen_fail;
extern gt_obj_st * screen_gl;
extern gt_obj_st * screen_jz;


void gt_ui_init(void);


gt_obj_st * gt_init_screen_home(void);
gt_obj_st * gt_init_screen_recording(void);
gt_obj_st * gt_init_screen_setup(void);
gt_obj_st * gt_init_screen_subtitle(void);
gt_obj_st * gt_init_screen_js(void);
gt_obj_st * gt_init_screen_xg(void);
gt_obj_st * gt_init_screen_ys(void);
gt_obj_st * gt_init_screen_nc(void);
gt_obj_st * gt_init_screen_fail(void);
gt_obj_st * gt_init_screen_gl(void);
gt_obj_st * gt_init_screen_jz(void);


typedef enum {
        GT_ID_SCREEN_HOME = 0,
        GT_ID_SCREEN_RECORDING = 1,
        GT_ID_SCREEN_SETUP = 2,
        GT_ID_SCREEN_SUBTITLE = 3,
        GT_ID_SCREEN_JS = 4,
        GT_ID_SCREEN_XG = 5,
        GT_ID_SCREEN_YS = 6,
        GT_ID_SCREEN_NC = 7,
        GT_ID_SCREEN_FAIL = 8,
        GT_ID_SCREEN_GL = 9,
        GT_ID_SCREEN_JZ = 10,
} gt_scr_id_et;



#endif

