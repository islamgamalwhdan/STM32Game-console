/*
 * gpu.h
 *
 *  Created on: Apr 14, 2021
 *      Author: Islam
 */
#include "STMGame_types.h"


#ifndef INC_GPU_H_
#define INC_GPU_H_


typedef struct
{
	 void*  Rendr_buf ;
	 void*  draw_buff ;
	int32_t Dis_w ;
	int32_t Dis_h ;
}Display;

typedef struct
{
	//uint16_t*        data  ;
	 void*       data ;
	uint32_t         color ;
	int              w, h  ;
}Bitmap , *Bitmap_PTR ;




#define FONT_BITMAP            0
#define SDRAM_BANK_ADDR       ((uint32_t)0xD0000000)
#define LCD_WIDTH              240
#define LCD_HEIGHT             320
#define BPP                    2
#define FONT8x8                1
#define FONT16x16              0

#if FONT8x8 == 1
#define CHAR_WIDTH  8
#define CHAR_HEIGHT 8
#else
#define CHAR_WIDTH  16
#define CHAR_HEIGHT 16
#endif

//Colors
#define BLACK    0x0000 //font
#define WHITE    0xFFFF //font
#define BLUE     0x3282F6 //screen
#define TRANSPARARENT_COLOR_RGB888    0x52FF73

//Public Variables
extern Display disp ;


//APIs
void InitDisplay(u32 background ,u32 color);
void CopyBMP(Bitmap_PTR Psrc_bmp , Bitmap_PTR Pdest_bmp , uint32_t in_offst) ;
void Fill_color_buff(Bitmap_PTR Psrc_bmp , Bitmap_PTR Pdest_bmp );
void Draw_Pixel(uint32_t x , uint32_t y , uint32_t color);
void renderChr(uint32_t x , uint32_t y , uint32_t color,char c);

#if FONT_BITMAP == 1
void Draw_chr_fast(uint32_t x , uint32_t y  , char c);
void Draw_String_fast(uint32_t x , uint32_t y ,char *str);
#endif

void renderStr(uint32_t x , uint32_t y , uint32_t color,char *str);
void FlipBuffers(void);
uint32_t Is_Render_cplt(void);
void Render_flush(void);
void GPU_BufferConfig(uint8_t Type) ;
#endif /* INC_GPU_H_ */
