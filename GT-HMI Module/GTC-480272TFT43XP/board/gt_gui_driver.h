#ifndef _GT_GUI_DRIVER_H_
#define _GT_GUI_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"
/* 外部函数声明 */
extern unsigned long r_dat_bat(unsigned long address, unsigned long DataLen, unsigned char* pBuff);
extern unsigned char gt_read_data(unsigned char* sendbuf, unsigned char sendlen, unsigned char* receivebuf, unsigned int receivelen);
/*------------------------------------------------------------------  Separation  -----------------------------------------------------------------*/

//字库初始化
int GT_Font_Init(void);
/*------------------------------------------------------------------  Separation  -----------------------------------------------------------------*/

#define GT_FAMILY_ASCII_32x32_A 43

typedef enum {
	gt_family_ascii_32x32_a = GT_FAMILY_ASCII_32x32_A, // 英文圆角
}font_option_et;

typedef struct gt_font_func_s
{
    font_option_et option;
    union
    {
        int (*read_dot_font)(unsigned long , unsigned int , unsigned char*);
        int (*read_vec_font)(unsigned char* , unsigned int ,unsigned long ,unsigned int , unsigned char , unsigned char);
    }func;
    unsigned char type;
}gt_font_func_st;

/**
* @brief  读取英文的点阵数据
* @param  fontcode：		英文编码
* @param  font_option：	字体选择
* @param  pbuffer：		存储读取出的点阵数据
* @retval 读取的数据个数	
*/
int GT_GetASCII(unsigned long fontcode, unsigned int font_option, unsigned char* pbuffer);

/**
 * @brief  Unicode转GBK
 * @param  fontcode	Unicode编码
 * @retval int  转换后编码
 */
unsigned int UnicodeToGBK(unsigned int fontcode);
/**
 * @brief  GBK转Unicode
 * @param  fontcode	GBK编码
 * @retval int  转换后编码
 */
unsigned int GBKToUnicode(unsigned int fontcode);
/**
* @brief 得到文字的宽度
* 
* @param fontcode 文字编码
* @param font_option 字体选择
* @param size 文字大小（矢量使用）
* @param gray 文字灰度（矢量使用）
* @param pBits 存储数据（矢量使用）
* @return int 宽度
*/
int GT_Get_Font_Width(unsigned long fontcode, unsigned int font_option, unsigned int size , unsigned int gray , unsigned char* pBits);

/**
* @brief 得到文字的高度
* 
* @param fontcode 
* @param font_option 字体选择
* @param size 文字大小（矢量使用
* @param gray 文字灰度（矢量使用）
* @return int 宽度
*/
int GT_Get_Font_Height(unsigned long fontcode, unsigned int font_option, unsigned int size , unsigned int gray);

/**
* @brief 检查字体是否是矢量字体
* 
* @param font_option 字体选择
* @return true 是矢量
* @return false 不是矢量
*/
char GT_Check_Is_Vec(unsigned int font_option);

/**
 * @brief 得到文字字体读取函数
 * 
 * @param style 字体类型
 * @return struct gt_font_func_s*  @gt_font_func_s
 */
struct gt_font_func_s* GT_Get_Font_Func_S(unsigned int style);
unsigned char GT_Get_Font_Type(unsigned int style);

unsigned char GT_Get_Chinese_Charset_Type(void);
void GT_Set_Chinese_Charset_Type(unsigned char charset);

typedef struct font_convertor_s
{
    uint16_t *fontcode ;
    uint16_t fontsize ;
    uint16_t font_option ;

    uint8_t fontgray;
    uint8_t thick;
    uint8_t * data ;

    bool is_rev ; // false is normal, true is reverse
    bool is_vec ;

    uint32_t code_len ;
    uint32_t data_len ; // Minimum three-character data storage length

    int (*read_dot_font)(unsigned long , unsigned int , unsigned char*);
    int (*read_vec_font)(unsigned char* , unsigned int ,unsigned long ,unsigned int , unsigned char , unsigned char);
}font_convertor_st;

int GT_Font_Code_Transform(font_convertor_st *convert);
int GT_Get_Font_Convertor_Data(font_convertor_st *convert , uint32_t pos);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

/*------------------------------------------------------------------ end of file -----------------------------------------------------------------*/
