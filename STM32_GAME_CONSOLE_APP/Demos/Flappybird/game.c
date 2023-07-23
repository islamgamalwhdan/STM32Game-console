/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************

  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/

#include "game.h"
#include "STMGame.h"
#include <stdio.h>

#define RANGE_RAND(min , max) (int)(Rand_num()%( (max)+1 - (min) ) +(min) )

//Global Variables
Sprite BackGround ;
Sprite fBird ;
Sprite pipeUp , pipeDown ;
GameState state = GAME_STATE_INIT  ;
GAMEPAD_BUTTON GamePad;
TC_Panel tc ;
int score;
char strbuf[131];
u8 pipe_passed = 0 ;


/* Main function ----------------------------------------------------------------------*/
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  MCU_Init() ;

  InitDisplay((void*)image_background , 0);
  GamePad_Init();
  touchpad_init();

  static TaskConfigType tskArray[] =
  {
		  {GamePad_InputsUpdate,  INTERVAL_20MS, 0 } ,
		  {TouchPad_InputsUpdate, INTERVAL_30MS, 0 } ,
		  {game_main,             INTERVAL_16MS, 0 }
  };

  SCH_AddHandlerTable(tskArray , sizeof(tskArray) /sizeof(TaskConfigType)) ;

  while (1)
  {
	  SCH_Dispatch() ;
  }

}//main


/* Functions ----------------------------------------------------------------------*/
void game_main(void)
{


	switch(state)
	{
	case GAME_STATE_INIT :

		/*
		 * At this state init background , Paddle , ball.
		 */
		BufferConfig(ANIMATED) ;
		Init_backGround(&BackGround);
		Init_pipes(&pipeDown , &pipeUp) ;
		fbird_Init();
		//Transition to level selection state
		state = GAME_STATE_LEVEL ;
		break ;

	case GAME_STATE_LEVEL:

		/*
		 * At this state we go for init the game level
		 */

		//zeroing score

		score =0;
		snprintf(strbuf,10,"Score %d" , score);
		//Transition to level selection state
		state = GAME_STATE_RUN ;
		break ;

	case GAME_STATE_RUN :

		/*
		 * The core of the game logic goes here.
		 */
			process_input();
			update_pipes() ;
			//BirdUpdatePostion();
			Update_animation(&fBird);
			fBird.y += fBird.ySpeed ;
			fBird.ySpeed += fBird.yAccel ;

			if( collision(&fBird , &pipeDown) || collision(&fBird , &pipeUp) || fBird.y > SCREEN_H)
			{
				state = GAME_STATE_END ;

			}
			if(pipeDown.x < fBird.x && fBird.active && !pipe_passed )
			{
				pipe_passed =1 ;
				score += 10 ;
				snprintf(strbuf,10,"Score %d" , score);
			}

			if(pipeDown.x >fBird.x)
				pipe_passed =0;

			//Draw
			clearScreen();

			DrawSprite(&fBird) ;
			DrawSprite(&pipeDown);
			DrawSprite(&pipeUp);

			//render Score value
			renderStr(90, 160,BLACK, strbuf);

			FlipBuffers();

		break;

	case GAME_STATE_END :

		Kill_Sprites() ;
		BufferConfig(NON_ANIMATED) ;

		do{ // render only once
		   clearScreen();
		   renderStr(80, 160,BLACK,"GAME OVER!!") ;
		   renderStr(5, 180,BLACK,"Press Start or\n\n"
				                                   "touch for new game") ;
		}while( state !=GAME_STATE_END );


		if( GamePad.button.start == PRESSED || tc.state == TC_PRESSED)
		{
			state = GAME_STATE_INIT ; // Start new game
		}

		break ;
	}//switch state


}


/***** Private Game functions *****/
void Init_backGround(Sprite *spr)
{
   spr->x = 0 ;
   spr->y = 0 ;
   spr->Width =  SCREEN_W ;
   spr->Height = SCREEN_H;
   spr->ImageData =(uint16_t*) image_background ;
   spr->active =1 ;
}


void GamePad_InputsUpdate(void)
{
	GamePad = GamePad_Read();
}

void TouchPad_InputsUpdate(void)
{
	GPIOG->ODR |=1<<13 ;   //debug pulse view program
	tc =touchpad_read() ;
	GPIOG->ODR &=~(1<<13) ;   //debug pulse view program
}



void fbird_Init()
{
	    fBird.x = 20 ;
		fBird.y = TFTH2 - 15 ;
		fBird.xSpeed = 0;
		fBird.ySpeed = -JUMP_FORCE;
		fBird.yAccel = GRAVITY * 0.01 ;
		fBird.vydelay = 0 ;
		fBird.ydelay = 0 ;

		//Init anim
		fBird.Frames_no = 3 ;
		fBird.curr_frame = 0 ;
		fBird.frames[0].w = fBird.frames[1].w = fBird.frames[2].w  = 16 ;
		fBird.frames[0].h = fBird.frames[1].h = fBird.frames[2].h  = 15 ;
		fBird.anim_cnt = 0 ;
		fBird.anim_sp = 15 ;

		fBird.Width = 16 ;
		fBird.Height = 15 ;

		if(fBird.active==0) // to prevent dynamic memory allocation while the sprite already created.
		{
	       Bitmap src_bmp ;
	       src_bmp.data = (void*) image_FBird ;
	       src_bmp.w    = 48 ;
	       src_bmp.h    = 15 ;
		   Grape_frames(fBird.frames ,&src_bmp,3  );
		}
		fBird.ImageData = fBird.frames[0].data ;

		fBird.active = 1 ;
}


void BirdUpdatePostion(void)
{
	if(++fBird.vxdelay > fBird.xdelay )
    {
        fBird.x += fBird.xSpeed ;
        fBird.vxdelay = 0 ;
    }
		if(++fBird.vydelay > fBird.ydelay )
    {
        fBird.y += fBird.ySpeed ;
        fBird.vydelay = 0 ;
    }
		fBird.ySpeed += fBird.yAccel ;

}
void Init_pipes(Sprite* pDwn , Sprite* pUp)
{
	//pipeUp
	pUp->Width= PIPEW ;
	pUp->Height = PIPEH ;
	pUp->ImageData = (void*)image_pipeUp ;
	pUp->x = TFTW ;
	pUp->y = RANGE_RAND(PIPEUP_MINY , PIPEUP_MAXY) ;
	pUp->xSpeed = -PIPE_SPEED ;
	pUp->ySpeed = -1.0 ;
	pUp->active = 1 ;

	//pipeDown
	pDwn->Width= PIPEW ;
	pDwn->Height = PIPEH ;
	pDwn->ImageData = (void*)image_pipeDown ;
	pDwn->x = TFTW  ;
	pDwn->y = RANGE_RAND(PIPEDN_MINY , PIPEDN_MAXY) ;
	pDwn->xSpeed = -PIPE_SPEED ;
	pDwn->ySpeed = -1.0 ;
	pDwn->active = 1 ;
}

void update_pipes()
{
	//upadte pipes

    pipeUp.x += pipeUp.xSpeed ;
	pipeUp.y += pipeUp.ySpeed ;
	pipeDown.Height = SCREEN_H - pipeDown.y ;
	pipeDown.x += pipeDown.xSpeed ;
	pipeDown.y += pipeDown.ySpeed ;

	 if(pipeUp.x < -pipeUp.Width || pipeDown.x < -pipeDown.Width )
	        {
	           pipeUp.x = pipeDown.x = TFTW   ;
	         //  gap = RANGE_RAND(GAP_MIN , GAP_MAX) ;
	           pipeUp.y = RANGE_RAND(PIPEUP_MINY , PIPEUP_MAXY) ;
	           pipeDown.y = RANGE_RAND(PIPEDN_MINY , PIPEDN_MAXY) ;
	        }
	 if(pipeUp.y < PIPEUP_MINY || pipeUp.y >PIPEUP_MAXY  )
	        {
	            pipeUp.ySpeed *= -1 ;
	        }
	 if(pipeDown.y < PIPEDN_MINY || pipeDown.y >PIPEDN_MAXY  )
	        {
	            pipeDown.ySpeed *= -1 ;
	        }
}


void process_input()
 {
	 static u8 isJumping =0 ;
	  if ( (tc.state == TC_RELEASED  || GamePad.button.yellow == RELEASED) && isJumping)
		 {
			   isJumping  = 0;
		 }
		 else if((tc.state == TC_PRESSED || GamePad.button.yellow == PRESSED) && !isJumping)
		 {
			  if (fBird.y > BIRDH2*0.5) fBird.ySpeed = -JUMP_FORCE;
              // else zero velocity
              else fBird.ySpeed = 0;
			 	   isJumping = 1;
		 }
 }

void Kill_Sprites(void)
{

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
