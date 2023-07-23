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
	 void*           data ;
	uint32_t         color ;
	int              w, h  ;
}Bitmap , *Bitmap_PTR ;


#define ENABLE_Pin GPIO_PIN_10
#define ENABLE_GPIO_Port GPIOF
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define B5_Pin GPIO_PIN_3
#define B5_GPIO_Port GPIOA
#define VSYNC_Pin GPIO_PIN_4
#define VSYNC_GPIO_Port GPIOA
#define G2_Pin GPIO_PIN_6
#define G2_GPIO_Port GPIOA
#define R3_Pin GPIO_PIN_0
#define R3_GPIO_Port GPIOB
#define R6_Pin GPIO_PIN_1
#define R6_GPIO_Port GPIOB
#define A6_Pin GPIO_PIN_12
#define A6_GPIO_Port GPIOF
#define A7_Pin GPIO_PIN_13
#define A7_GPIO_Port GPIOF
#define A8_Pin GPIO_PIN_14
#define A8_GPIO_Port GPIOF
#define A9_Pin GPIO_PIN_15
#define A9_GPIO_Port GPIOF
#define A10_Pin GPIO_PIN_0
#define A10_GPIO_Port GPIOG
#define A11_Pin GPIO_PIN_1
#define A11_GPIO_Port GPIOG
#define D4_Pin GPIO_PIN_7
#define D4_GPIO_Port GPIOE
#define D5_Pin GPIO_PIN_8
#define D5_GPIO_Port GPIOE
#define D6_Pin GPIO_PIN_9
#define D6_GPIO_Port GPIOE
#define D7_Pin GPIO_PIN_10
#define D7_GPIO_Port GPIOE
#define D8_Pin GPIO_PIN_11
#define D8_GPIO_Port GPIOE
#define D9_Pin GPIO_PIN_12
#define D9_GPIO_Port GPIOE
#define D10_Pin GPIO_PIN_13
#define D10_GPIO_Port GPIOE
#define D11_Pin GPIO_PIN_14
#define D11_GPIO_Port GPIOE
#define D12_Pin GPIO_PIN_15
#define D12_GPIO_Port GPIOE
#define G4_Pin GPIO_PIN_10
#define G4_GPIO_Port GPIOB
#define G5_Pin GPIO_PIN_11
#define G5_GPIO_Port GPIOB
#define D13_Pin GPIO_PIN_8
#define D13_GPIO_Port GPIOD
#define D14_Pin GPIO_PIN_9
#define D14_GPIO_Port GPIOD
#define D15_Pin GPIO_PIN_10
#define D15_GPIO_Port GPIOD
#define R7_Pin GPIO_PIN_6
#define R7_GPIO_Port GPIOG
#define DOTCLK_Pin GPIO_PIN_7
#define DOTCLK_GPIO_Port GPIOG
#define SDCLK_Pin GPIO_PIN_8
#define SDCLK_GPIO_Port GPIOG
#define HSYNC_Pin GPIO_PIN_6
#define HSYNC_GPIO_Port GPIOC
#define G6_Pin GPIO_PIN_7
#define G6_GPIO_Port GPIOC
#define R4_Pin GPIO_PIN_11
#define R4_GPIO_Port GPIOA
#define R5_Pin GPIO_PIN_12
#define R5_GPIO_Port GPIOA
#define R2_Pin GPIO_PIN_10
#define R2_GPIO_Port GPIOC
#define D2_Pin GPIO_PIN_0
#define D2_GPIO_Port GPIOD
#define D3_Pin GPIO_PIN_1
#define D3_GPIO_Port GPIOD
#define G7_Pin GPIO_PIN_3
#define G7_GPIO_Port GPIOD
#define B2_Pin GPIO_PIN_6
#define B2_GPIO_Port GPIOD
#define G3_Pin GPIO_PIN_10
#define G3_GPIO_Port GPIOG
#define B3_Pin GPIO_PIN_11
#define B3_GPIO_Port GPIOG
#define B4_Pin GPIO_PIN_12
#define B4_GPIO_Port GPIOG
#define B6_Pin GPIO_PIN_8
#define B6_GPIO_Port GPIOB
#define B7_Pin GPIO_PIN_9
#define B7_GPIO_Port GPIOB

#define FONT_BITMAP            0
#define SDRAM_BANK_ADDR       ((uint32_t)0xD0000000)
#define LCD_WIDTH              240
#define LCD_HEIGHT             320
#define BPP                    2
#define CHAR_WIDTH             8
#define CHAR_HEIGHT            8

//Colors
#define WHITE                         0xFFFF
#define BLACK                         0x0000
#define TRANSPARARENT_COLOR_RGB888    0x52FF73


//Public variables
extern Display disp ;


//APIs
void InitDisplay(void* background_img , u32 color) ;
void CopyBMP(Bitmap_PTR Psrc_bmp , Bitmap_PTR Pdest_bmp , uint32_t in_offst) ;
void Fill_color_buff(u32 color , void* buf , u16 src_w , u16 dest_w , u16 h );
void Draw_Pixel(uint32_t x , uint32_t y , uint32_t color);
void renderChr(uint32_t x , uint32_t y , uint32_t color,char c);
void clearScreen(void);

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
