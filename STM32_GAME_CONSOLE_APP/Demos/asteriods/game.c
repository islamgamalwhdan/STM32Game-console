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

#include "STMGame.h"
#include "string.h"
#include "game.h"


#define RANGE_RAND(min , max) (int)(Rand_num()%( (max)+1 - (min) ) +(min) )

//Global Variables
Sprite BackGround ;
Sprite fBird ;
Sprite pipeUp , pipeDown ;
Sprite Ship , astr;
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

  //umm_init() for dynamic memory allocation ,
  //and it must be called after SDRAM initialization !!
 // umm_init();

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
		Ship_Init();
		Asteriod_Init() ;
		//Init_pipes(&pipeDown , &pipeUp) ;
		//fbird_Init();
		//Transition to level selection state
		state = GAME_STATE_LEVEL ;
		break ;

	case GAME_STATE_LEVEL:

		/*
		 * At this state we go for init the game level
		 */

		//zeroing score

		score =0;
	//	snprintf(strbuf,10,"Score %d" , score);
		//Transition to level selection state
		state = GAME_STATE_RUN ;
		break ;

	case GAME_STATE_RUN :

		/*
		 * The core of the game logic goes here.
		 */
		ship_test() ;
#if 0
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
#endif
		break;

	case GAME_STATE_END :

		//Kill_Sprites() ;
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


#if 0
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
		   Grape_frames(&fBird ,&src_bmp  );
		}
		fBird.ImageData = fBird.frames[0].data ;

		fBird.active = 1 ;
}
#endif
void Asteriod_Init()
{
	Bitmap frames_arr[16] ;


	astr.x = 50 ;
	astr.y = 50 ;

	//Init frames
	astr.Frames_no = 16 ;
	astr.curr_frame = 0 ;

	for( u8 i =0 ; i<16 ; i++)
			{
				astr.frames[i].w = 32 ;
				astr.frames[i].h = 32 ;
			}

	if(astr.active==0) // to prevent dynamic memory allocation while the sprite already created.
			{
		       Bitmap src_bmp ;
		       src_bmp.data = (void*) image_bigastr ;
		       src_bmp.w    = 32*16 ;
		       src_bmp.h    = 32 ;
			   Grape_frames(astr.frames ,&src_bmp , 16  );
			}
	astr.ImageData = astr.frames[0].data ;
	astr.anim_cnt = 0 ;
	astr.anim_sp  = 2 ;

	astr.Width =  32 ;
	astr.Height = 32 ;
	astr.active =  1 ;
}

void Ship_Init()
{
	    Ship.x = 105 ;
		Ship.y = 144;

		//Init frames
		Ship.Frames_no = 16 ;
		Ship.curr_frame = 0 ;


		for( u8 i =0 ; i<16 ; i++)
		{
			Ship.frames[i].w = 29 ;
			Ship.frames[i].h = 32 ;
		}

		Ship.anim_cnt = 0 ;
		Ship.anim_sp = 2 ;

		Ship.Width = 29 ;
		Ship.Height = 32 ;

		if(Ship.active==0) // to prevent dynamic memory allocation while the sprite already created.
		{
	       Bitmap src_bmp ;
	       src_bmp.data = (void*) image_spaceship ;
	       src_bmp.w    = 29*16 ;
	       src_bmp.h    = 32 ;
		   Grape_frames(Ship.frames ,&src_bmp , 16  );
		}
		Ship.ImageData = Ship.frames[0].data ;

		Ship.active = 1 ;
}

void ship_test(void)
{
	static int i  , rgt_cnt , lft_cnt;
	static float ShipAngle =0 ;
	Update_animation(&astr) ;
	if(GamePad.button.left == PRESSED && ++rgt_cnt >4 )
	{
		rgt_cnt = 0;
		if(++i>15) i= 0 ;

	}
	if(GamePad.button.right == PRESSED && ++lft_cnt >4)
	{
		lft_cnt = 0 ;
		if(--i<0) i=15 ;

	}
	ShipAngle = i*22.5f ;
	Ship.ImageData = Ship.frames[i].data ;
	//Draw
	clearScreen();
	DrawSprite(&Ship) ;
	DrawSprite(&astr);
	FlipBuffers();

}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
