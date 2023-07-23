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

#define MAX_FRAMES                   16


typedef enum {ROT_ZERO= 0 , ROT_90 , ROT_180 , ROT_270}ROT_MODE;


typedef struct
{
  void * ImageData            ;
  float      x      , y       ;
  int       Width   , Height  ;
  float     xSpeed  , ySpeed  ;
  float     xAccel  , yAccel  ;
  float     vxdelay , vydelay ,
            xdelay , ydelay   ;
  float     angle;
  int       active            ;
  //Animation variables
  int curr_frame  , Frames_no ,
      anim_cnt , anim_sp     ,
      continus_anim ;
  Bitmap frames[MAX_FRAMES]   ;
}Sprite ;

typedef enum
{
	NON_ANIMATED =0  , ANIMATED =1
}AnimType;

void  BufferConfig(AnimType an) ;
void  DrawSprite(Sprite* spr );
void  Erase_Sprite(Sprite *spr ,Sprite *back );
void Grape_frames(Bitmap* frames , Bitmap* Psrc_bmp  , u8 Frames_no);
void Update_animation(Sprite *spr);
u8  collision( Sprite* spr1 ,  Sprite* spr2);
#endif /* INC_GAMEENGINE_H_ */
