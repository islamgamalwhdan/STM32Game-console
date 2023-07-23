/*
 * GameEngine.c
 *
 *  Created on: Apr 16, 2021
 *      Author: Islam
 */
#include "STMGame.h"


#define BPP                          2
#define ASPECT_RATIO_W               12
#define ASPECT_RATIO_H               16

#define MAX_SPRITES                  10

#ifndef MAX_FRAMES
#define MAX_FRAMES                   5
#endif

#define MAX_FRAME_W                  100
#define MAX_FRAME_H                  100

typedef struct
{
	u16 data[MAX_FRAME_W * MAX_FRAME_H] ;
}Frame_t;

typedef struct
{
	Frame_t frames_container[MAX_FRAMES] ;
}SPR_Container;


/*************************** Private variables ***************************/

/*static Container to hold frames of a sprite located at SDRAM bank3
 * Container size = MAX_SPRITES * MAX_FRAMES * MAX_FRAME_W * MAX_FRAME_H * 2
 */

//static __attribute__( ( section( ".sdram3" ) ) )
//SPR_Container spr_mem[MAX_SPRITES] ;

static AnimType buffering = ANIMATED ;
/*************************** Public functions ***************************/
static void blit(Bitmap* SrcPm, void *fb,  int src_x, int src_y, int dst_x, int dst_y, int w, int h);

void  BufferConfig(AnimType an)
{
	buffering = an ;
	GPU_BufferConfig((u8) an ) ;
}


void  DrawSprite(Sprite* spr )
{
	if(spr->active)
	{
      void * data = (void *)spr->ImageData ;
      u32 spr_h = spr->Height;
      u32 spr_w = spr->Width;

      /**** Clipping work ****/

      //1- check if the image is totally invisible
      	if(spr->x >= disp.Dis_w || spr->y >= disp.Dis_h ||
      	   spr->x+spr_w <= 0 || spr->y+spr_h <= 0 )
      		                                          return ; // go out
      //2-compute new coordinations for easy computation
      	int x1 = spr->x ;
      	int y1 = spr->y ;
      	int x2 = x1+spr_w -1 ;
      	int y2 = y1+spr_h -1 ;

      //3- left upper corner wrapping.
      	if(x1 < 0) x1 = 0 ;
      	if(y1 < 0) y1 = 0 ;

     //4- Right lower corner wrapping.
       if(x2 >= disp.Dis_w) x2 = disp.Dis_w - 1 ;
       if(y2 >= disp.Dis_h) y2 = disp.Dis_h - 1 ;


    //5- Calculate new offset for destination buffer and source bitmap.
      int offset_des = BPP * (x1 + y1*disp.Dis_w) ;
      int offset_src = BPP * ( x1 -spr->x + (y1-spr->y)*spr_w ) ;


    //6- Calculate new width and height for sprite.

      int w = x2-x1 +1 ;
      int h = y2-y1 +1 ;
      int in_offset = spr->Width - w ; /* It is added at the end of each line to determine the starting address of the
                                      next line from source bitmap*/
      Bitmap src , dest ;

      src.data  = data+offset_src              ;
     // src.color = TRANSPARARENT_COLOR_RGB888   ;
      src.color = spr->color ;
      src.w     = w                            ;
      src.h     = h                            ;

      dest.data = (buffering == ANIMATED ? disp.draw_buff : disp.Rendr_buf) + offset_des  ;
      dest.w    = disp.Dis_w                   ;
      dest.h    = disp.Dis_h                   ;

     // Now finally blit!
      if(spr->LayerId == SPRITE)
    	  CopyBMP(&src , &dest ,in_offset );
      else
    	  Fill_color_buff(&src , &dest);
	}//if
}

void Erase_Sprite(Sprite *spr ,Sprite *back )
{
#if 0
	int offset_src = BPP * ( spr->x + spr->y * back->Width ) ;
	static Bitmap src , dest ;

	dest.data = (buffering == ANIMATED ? disp.draw_buff : disp.Rendr_buf);
	dest.data +=  offset_src ;
	dest.w    = spr->Width  ;
	dest.h    = spr->Height ;

	src.data  = (void *)(back->ImageData) + offset_src  ;
	src.color = TRANSPARARENT_COLOR_RGB888    ;
	src.w     = spr->Width                    ;
	src.h     = spr->Height                    ;

	CopyBMP(&src  , &dest, back->Width - spr->Width) ;
	//Fill_color_buff(&src , &dest);
#endif

	u32 x = spr->x , y = spr->y  ;
	__IO u16* buf = (buffering == ANIMATED ? disp.draw_buff : disp.Rendr_buf);
	__IO u16*  ptr = (u16*)(back->ImageData)+ x +y*back->Width ;

	for (u32 i = 0; i <  spr->Height ; i++)
			for (u32 j = 0; j  < spr->Width; j++)
			{
				u16 color = back->ImageData? *ptr++ : rgb888torgb565(back->color);
				*( buf + ((y+i)* disp.Dis_w + x + j) ) = color;
			}

}

static void blit(Bitmap* SrcPm, void *fb,  int src_x, int src_y, int dst_x, int dst_y, int w, int h)
{
	u16 *ptr = (u16*)SrcPm->data;
	ptr += src_x + src_y *SrcPm->w ;
	for (u32 i = 0; i <  h ; i++)
	{
		for (u32 j = 0; j  < w; j++)
		{
			u16 color = *ptr++;

				*( (( u16*) fb) + ((dst_y+i)* disp.Dis_w + dst_x + j) ) = color;

		}

  }

}

u16 rgb888torgb565(u32 rgb888Pixel)
{
	u8 red   = ((u32)rgb888Pixel ) >>16 ;
	u8 green = (((u32)rgb888Pixel ) >>8) & 0x00FF ;
	u8 blue  = (u32)rgb888Pixel & 0x000000FFUl ;

    u16 b = (blue >> 3) & 0x1f;
    u16 g = ((green >> 2) & 0x3f) << 5;
    u16 r = ((red >> 3) & 0x1f) << 11;

    return (u16) (r | g | b);
}
#if 0
void Grape_frames(Sprite *spr , Bitmap_PTR Psrc_bmp ,int dest_w ,int src_w )
{
	for(int i = 0 ; i < spr->Frames_no ; i++)
	{
		spr->frames[i].data   = spr_mem[spr->spr_ID].frames_container[i].data ;
		CopyBMP(Psrc_bmp,&(spr->frames[i]) , src_w - dest_w) ;
		Psrc_bmp->data   += dest_w ;
	}
}
int collision( Sprite* spr1 ,  Sprite* spr2)
{
    if(spr1->x  > (spr2->x + spr2->Width  )  ||
       spr1->y  > (spr2->y + spr2->Height  ) ||
       spr2->x  > (spr1->x + spr1->Width  )  ||
       spr2->y  > (spr1->y + spr1->Height  ) )
   {
       return 0 ;
   }
   return 1 ;
}
#endif
