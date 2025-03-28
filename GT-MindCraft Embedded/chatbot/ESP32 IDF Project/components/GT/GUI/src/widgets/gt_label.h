/**
 * @file gt_label.h
 * @author yongg
 * @brief label for content description
 * @version 0.1
 * @date 2022-07-13 11:55:38
 * @copyright Copyright (c) 2014-present, Company Genitop. Co., Ltd.
 */
#ifndef _GT_LABEL_H_
#define _GT_LABEL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* include --------------------------------------------------------------*/
#include "gt_conf_widgets.h"

#if GT_CFG_ENABLE_LABEL
#include "gt_obj.h"
#include "gt_obj_class.h"
#include "stdarg.h"
#include "stdlib.h"
#include "../others/gt_color.h"
#include "../core/gt_style.h"
#include "../font/gt_font.h"


/* define ---------------------------------------------------------------*/



/* typedef --------------------------------------------------------------*/



/* macros ---------------------------------------------------------------*/



/* global functions / API interface -------------------------------------*/

/**
 * @brief create label obj
 *
 * @param parent label's parent obj
 * @return gt_obj_st* label obj ptr
 */
gt_obj_st * gt_label_create(gt_obj_st * parent);

/**
 * @brief set label obj text
 *
 * @param label label obj
 * @param fmt text format
 */
void gt_label_set_text(gt_obj_st * label, const char * fmt, ...);

/**
 * @brief Set label text by content length
 *
 * @param label
 * @param text
 * @param len encoding byte count, such as: strlen(text).
 */
void gt_label_set_text_by_len(gt_obj_st * label, const char * text, uint16_t len);

/**
 * @brief get label text
 *
 * @param label label obj
 * @return char* label's text
 */
char * gt_label_get_text(gt_obj_st * label);

/**
 * @brief set label font color
 *
 * @param label label obj
 * @param color color
 */
void gt_label_set_font_color(gt_obj_st * label, gt_color_t color);

gt_color_t gt_label_get_font_color(gt_obj_st * label);

void gt_label_set_font_size(gt_obj_st * label, uint8_t size);
void gt_label_set_font_gray(gt_obj_st * label, uint8_t gray);
void gt_label_set_indent(gt_obj_st * label, uint16_t indent);
void gt_label_set_font_align(gt_obj_st * label, gt_align_et align);
#if (defined(GT_FONT_FAMILY_OLD_ENABLE) && (GT_FONT_FAMILY_OLD_ENABLE == 1))
void gt_label_set_font_family_cn(gt_obj_st * label, gt_family_t family);
void gt_label_set_font_family_en(gt_obj_st * label, gt_family_t family);
void gt_label_set_font_family_fl(gt_obj_st * label, gt_family_t family);
void gt_label_set_font_family_numb(gt_obj_st * label, gt_family_t family);
#else
void gt_label_set_font_family(gt_obj_st * label, gt_family_t family);
void gt_label_set_font_cjk(gt_obj_st* label, gt_font_cjk_et cjk);
#endif
void gt_label_set_font_thick_en(gt_obj_st * label, uint8_t thick);
void gt_label_set_font_thick_cn(gt_obj_st * label, uint8_t thick);
void gt_label_set_font_encoding(gt_obj_st * label, gt_encoding_et encoding);

void gt_label_set_space(gt_obj_st * label, uint8_t space_x, uint8_t space_y);

void gt_label_set_font_style(gt_obj_st * label, gt_font_style_et font_style);

uint8_t gt_label_get_font_size(gt_obj_st * label);

uint8_t gt_label_get_space_x(gt_obj_st * label);
uint8_t gt_label_get_space_y(gt_obj_st * label);

void gt_label_set_font_info(gt_obj_st * label, gt_font_info_st * font_info);
gt_font_info_st * gt_label_get_font_info(gt_obj_st * label);

/**
 * @brief Get max substring line width
 *
 * @param label
 * @return uint16_t max substring line width
 */
uint16_t gt_label_get_longest_line_substring_width(gt_obj_st * label);

/**
 * @brief Set single line, label first time init is multi-line.
 *      The characters that can be displayed in the display area, without
 *      "..." or "。。。" at the end of the line.
 *
 * @param label
 * @param is_single_line true: single line, false: multi-line
 */
void gt_label_set_single_line(gt_obj_st * label, bool is_single_line);

/**
 * @brief Set omit single line, The characters display "..." or "。。。"
 *      at the end of the line, if the characters that can be displayed.
 *
 * @param label
 * @param is_omit true: omit single line, false: multi-line
 */
void gt_label_set_omit_single_line(gt_obj_st * label, bool is_omit);

/**
 * @brief Set auto scroll single line
 *
 * @param label
 * @param is_auto_scroll true: auto scroll single line, false: omit single line
 */
void gt_label_set_auto_scroll_single_line(gt_obj_st * label, bool is_auto_scroll);

/**
 * @brief Set auto scroll speed
 *
 * @param label
 * @param total_time_ms > 0: total time(ms) for auto scroll each time;
 *                     = 0: set default 2s.
 */
void gt_label_set_auto_scroll_total_time(gt_obj_st * label, uint32_t total_time_ms);

bool gt_label_is_single_line(gt_obj_st * label);
bool gt_label_is_omit_single_line(gt_obj_st * label);
bool gt_label_is_auto_scroll_single_line(gt_obj_st * label);


void gt_label_add_text(gt_obj_st * label, const char * fmt, ...);

#endif  /** GT_CFG_ENABLE_LABEL */

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif //!_GT_LABEL_H_
