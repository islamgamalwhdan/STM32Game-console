/*
 * GameEngine.h
 *
 *  Created on: Apr 16, 2021
 *      Author: Islam
 */

#ifndef INC_GAMEENGINE_H_
#define INC_GAMEENGINE_H_

#include "stdint.h"
#include "gpu.h"
#include "STMGame_types.h"

#define MAX_FRAMES                   5

typedef enum {BACKGROUND , SPRITE}LayerType;

typedef enum {ROT_ZERO= 0 , ROT_90 , ROT_180 , ROT_270}ROT_MODE;


typedef struct
{
  u16* ImageData   ;
  int       x       , y       ;
  int       Width   , Height  ;
  int       xSpeed  , ySpeed  ;
  int       active            ;

  Bitmap frames[MAX_FRAMES];
  int curr_frame  , Frames_no  , anim_cnt;
  LayerType LayerId ;
  u32 color ;
  int spr_ID ;
}Sprite ;

typedef enum
{
	NON_ANIMATED =0  , ANIMATED =1
}AnimType;

void  BufferConfig(AnimType an) ;
void  DrawSprite(Sprite* spr );
void  Erase_Sprite(Sprite *spr ,Sprite *back );
void  Grape_frames(Sprite *spr , Bitmap_PTR Psrc_bmp ,int dest_w ,int src_w );
int   collision( Sprite* spr1 ,  Sprite* spr2);
u16   rgb888torgb565(u32 rgb888Pixel) ;
#endif /* INC_GAMEENGINE_H_ */
