/*
 * GameEngine.c
 *
 *  Created on: Apr 16, 2021
 *      Author: Islam
 */
#include "STMGame.h"

#define TRANSPARARENT_COLOR_RGB888   0x52FF73
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
	u8 data[MAX_FRAME_W * MAX_FRAME_H * BPP] ;
}Frame_t;

typedef struct
{
	Frame_t frames_container[MAX_FRAMES] ;
}SPR_Container;


/*************************** Private variables ***************************/

/*static Container to hold frames of a sprite located at SDRAM bank3
 * Container size = MAX_SPRITES * MAX_FRAMES * MAX_FRAME_W * MAX_FRAME_H * 2
 */
#if 0
union block
{
  union block * next;
  unsigned char payload[32];
};

static union block arena[100];
static union block * head;

void init(void)
{
  int i;
    for (i = 0; i < 100 - 1; i++)
         arena[i].next = &arena[i + 1];
 arena[i].next = 0; /* last one, null */
 head = arena;
}
void *block_alloc()
{
  void *answer = head;
  if (answer)
      head = head->next;
  return answer;
}
#endif
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
	if(spr->active == 0) return ;

      void * data = (void *)spr->ImageData ;
      u32 spr_h = spr->Height;
      u32 spr_w = spr->Width;
      s16 spr_x = (s16)spr->x ;
      s16 spr_y = (s16)spr->y ;
      /**** Clipping work ****/

      //1- check if the image is totally invisible
      	if(spr_x >= disp.Dis_w || spr_y >= disp.Dis_h ||
      	   spr_x+spr_w <= 0 || spr_y+spr_h <= 0 )
      		                                          return ; // go out
      //2-compute new coordinations for easy computation
      	s16 x1 = spr_x ;
      	s16 y1 = spr_y ;
      	s16 x2 = x1+spr_w -1 ;
      	s16 y2 = y1+spr_h -1 ;

      //3- left upper corner wrapping.
      	if(x1 < 0) x1 = 0 ;
      	if(y1 < 0) y1 = 0 ;

     //4- Right lower corner wrapping.
       if(x2 >= disp.Dis_w) x2 = disp.Dis_w - 1 ;
       if(y2 >= disp.Dis_h) y2 = disp.Dis_h - 1 ;


    //5- Calculate new offset for destination buffer and source bitmap.
      int offset_des = BPP * (x1 + y1*disp.Dis_w) ;
      int offset_src = BPP * ( x1 -spr_x + (y1-spr_y)*spr_w ) ;


    //6- Calculate new width and height for sprite.

      int w = x2-x1 +1 ;
      int h = y2-y1 +1 ;
      int in_offset = spr->Width - w ; /* It is added at the end of each line to determine the starting address of the
                                      next line from source bitmap*/
      Bitmap src , dest ;

      src.data  = data+offset_src              ;
      src.color = TRANSPARARENT_COLOR_RGB888   ;
      src.w     = w                            ;
      src.h     = h                            ;

      dest.data = (buffering == ANIMATED ? disp.draw_buff : disp.Rendr_buf) + offset_des  ;
      dest.w    = disp.Dis_w                   ;
      dest.h    = disp.Dis_h                   ;

     // Now finally blit!
      CopyBMP(&src , &dest ,in_offset );
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
				u16 color = *ptr++;
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
void Grape_frames(Bitmap* frames , Bitmap* Psrc_bmp  , u8 Frames_no)
{
	Bitmap src, des ;
	u16 in_offset ;

	src.w = frames[0].w;
	src.h = frames[0].h ;
	src.data = Psrc_bmp->data ;

	des.w = src.w ;
	des.h = src.h ;

	in_offset = Psrc_bmp->w - src.w ;
	for(int i = 0 ; i < Frames_no ; i++)
	{
		//spr->frames[i].data   = (void*)(spr_mem[spr->spr_ID].frames_container[i].data) ;
		frames[i].data = umm_malloc(src.w * src.h * BPP) ;
		des.data = frames[i].data ;
		CopyBMP(&src,&des ,in_offset) ;
		src.data += src.w * BPP  ;
	}
}


void Update_animation(Sprite *spr)
{
	if (spr->active == 0) return ;
	if(++spr->anim_cnt > spr->anim_sp)
				{

					spr->anim_cnt = 0 ;
				    if(++spr->curr_frame >=spr->Frames_no)
				    	 {
							spr->curr_frame =  0 ;
							if(spr->continus_anim == 0)  spr->active = 0 ;
						 }
                    // Assign current frame to Imagedata to be displayed while rendering
				    spr->ImageData = spr->frames[spr->curr_frame].data ;
					
				}
}
u8 collision( Sprite* spr1 ,  Sprite* spr2)
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
