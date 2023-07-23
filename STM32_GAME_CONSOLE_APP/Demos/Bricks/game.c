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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "main.h"
#include <stdio.h>



Sprite aln ;
Sprite fBird ;
GameState state = GAME_STATE_INIT  ;
Sprite BackGround ;
Sprite bricks[BRICKS_WIDTH*BRICKS_HEIGHT];
Sprite Paddle;
Sprite Ball;
Sprite Bird;
GAMEPAD_BUTTON GamePad;
TC_Panel tc ;
GYRO_Angle gAngle;


int hits ;
int score;
char strbuf[131];


/* Main function ----------------------------------------------------------------------*/
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  MCU_Init() ;

  InitDisplay((uint32_t)image_background);
  GamePad_Init();
  touchpad_init();
 // GYRO_Init();
 // GYRO_Reset();
 // GYRO_Calibaration();


  static TaskConfigType tskArray[] =
  {
		 // {GET_GYRO_Angles,       INTERVAL_10MS, 0 } ,
		  {GamePad_InputsUpdate,  INTERVAL_20MS, 0 } ,
		  {TouchPad_InputsUpdate, INTERVAL_30MS, 0 } ,
		  {game_main,             INTERVAL_16MS, 0 }
  };
  SCH_AddHandlerTable(tskArray , sizeof(tskArray) /sizeof(TaskConfigType)) ;

  Init_backGround(&BackGround);
  Alien_init() ;
  //fbird_Init();
  while (1)
  {
	  SCH_Dispatch() ;

	  //test_code() ;
  }//while
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
		Init_Paddle(&Paddle);
		Init_Ball(&Ball);

		//Transition to level selection state
		state = GAME_STATE_LEVEL ;
		break ;

	case GAME_STATE_LEVEL:

		/*
		 * At this state we go for init the game level
		 */
		InitBricks(bricks);

		//zeroing hits
		hits = 0 ;
		score =0;
		//Transition to level selection state
		state = GAME_STATE_RUN ;
		break ;

	case GAME_STATE_RUN :

		/*
		 * The core of the game logic goes here.
		 */
		//test_code() ;
		test_code_alien();
#if 0
		DrawSprite(&BackGround ); //clear back buffer
	    Control_Paddle_Move(&Paddle,&Ball, &GamePad);
		Control_Ball_Move(&Ball, &GamePad);
		Control_collsion();
		DrawSprite(&Paddle);
		DrawSprite(&Ball);
		DrawBricks(bricks);
		if(GamePad.Connection == GP_NOT_CONNECTED)
					//Draw_String_fast(20, 160, "GamePad not connected!!");
			       renderStr(20, 160,BLACK, "GamePad not connected!!");

		snprintf(strbuf,10,"Score %d" , score);
			//Draw_String_fast(80, 260, strbuf);
		renderStr(80, 260,BLACK, strbuf);
	    if(  (GamePad.Connection == GP_CONNECTED &&GamePad.button.select == PRESSED)
				                            || hits== BRICKS_WIDTH * BRICKS_HEIGHT )

		  {
				//shutdown the game
				state = GAME_STATE_END ;
		  }
	    FlipBuffers();// Double buffering
#endif
		break;

	case GAME_STATE_END :

		state = GAME_STATE_INIT ;

		break ;
	}//switch state

}

void Init_backGround(Sprite *spr)
{
   spr->x = 0 ;
   spr->y = 0 ;
   spr->Width =  SCREEN_W ;
   spr->Height = SCREEN_H;
   spr->ImageData =(uint16_t*) image_background ;
   spr->LayerId   = BACKGROUND ;
   spr->active =1 ;
}


void Init_Arrow(Sprite *spr)
{
	spr->x = 90 ;
	spr->y = 90 ;
	spr->Width =  10 ;
	spr->Height = 8;
	spr->ImageData =(uint16_t*) image_arrow ;
	spr->LayerId   = SPRITE ;
	spr->active =1 ;
}

void Init_Paddle(Sprite *paddle)
{

	paddle->x = SCREEN_W/2 - PADDLE_WIDTH/2 ;
	paddle->y = SCREEN_H-PADDLE_HEIGHT ;
	paddle->Width =  PADDLE_WIDTH ;
	paddle->Height = PADDLE_HEIGHT;
	paddle->ImageData =(uint16_t*) image_paddle ;
	paddle->xSpeed = 4;
	paddle->ySpeed = 0;
	paddle->LayerId   = SPRITE ;
	paddle->active = 1 ;
#if 0
	    paddle->x =SCREEN_W_RO/2 - PADDLE_WIDTH_RO/2; //SCREEN_H/2 - 80/2 ;
		paddle->y =SCREEN_H_RO-PADDLE_HEIGHT_RO; //SCREEN_W - 12 ;
		paddle->Width =  PADDLE_WIDTH_RO ;
		paddle->Height = PADDLE_HEIGHT_RO;
		paddle->ImageData = image_paddle_rot_90 ;
		paddle->xSpeed = 4;
		paddle->ySpeed = 0;
		paddle->LayerId   = SPRITE ;
		paddle->active = 1 ;
#endif
}

void Control_Paddle_Move(Sprite * paddle ,Sprite * ball ,  GAMEPAD_BUTTON *GamePad)
{
	if(GamePad->Connection == GP_CONNECTED &&
			GamePad->button.right == PRESSED)
	{
		paddle->x += paddle->xSpeed ;

		if(ball->ySpeed == 0)
			ball->x += paddle->xSpeed ;
	}
	else if(GamePad->Connection == GP_CONNECTED &&
			      GamePad->button.left == PRESSED)
	{
		  paddle->x -= paddle->xSpeed ;
		  if(ball->ySpeed == 0)
		  			ball->x -= paddle->xSpeed ;
	}


	if(ball->ySpeed)
	  //  paddle->x = PADDLE_CENTRE+ gAngle.y *3 ;
		paddle->x +=  gAngle.y *3 ;

	if(tc.state == TC_PRESSED)
	{
		paddle->x = tc.x ;
	}

	//Keep paddle in the screen X values
	if(paddle->x > (SCREEN_W - PADDLE_WIDTH))
	{
		paddle->x = SCREEN_W - PADDLE_WIDTH ;
	}

	if(paddle->x < 0)
	{
		paddle->x = 0 ;
	}
}

void Control_Ball_Move(Sprite * ball, GAMEPAD_BUTTON *GamePad)
{
	if(ball->ySpeed == 0 &&
			(( GamePad->button.start  == PRESSED && GamePad->Connection == GP_CONNECTED ) || tc.state == TC_PRESSED) )
	{
		// start to move the ball todo : slope to get xspeed , yspeed
		ball->xSpeed = 3 ;
		ball->ySpeed = -2 ;
	}
	ball->x += ball->xSpeed ;
	ball->y += ball->ySpeed ;

	//Keep the ball in the screen boundaries.

	if(ball->x > (SCREEN_W - ball->Width) || ball->x < 0)
	{
		ball->xSpeed = 0- ball->xSpeed ;
		ball->x += ball->xSpeed ;
	}

	if(ball ->y > (SCREEN_H - ball->Height) || ball->y < 0)
	{
		if(ball ->y > (SCREEN_H - ball->Height)) score -= 20 ;
		ball->ySpeed = 0- ball->ySpeed ;
		ball->y += ball->ySpeed ;


		//you loose Todo: score--

	}
}


void Control_collsion(void)
{
   // Check ball collision with bricks

	for(int i = 0 ; i <BRICKS_WIDTH * BRICKS_HEIGHT ; i++)
		{
		  if(collision(&Ball , &bricks[i]) &&bricks[i].active)
		  {
			  //destroy this brick
			  bricks[i].active = 0;

			  //ball action
			  Ball.ySpeed = -Ball.ySpeed ; //bounce the ball
			  Ball.xSpeed += (-1 +Rand_num()%3 ) ;

			  //increase score
			  hits++; ;
			  score += 10;
		  }//if
		} //for

	if(collision(&Ball, &Paddle) && Ball.ySpeed)
			{
		      //ball action
			     Ball.ySpeed = -Ball.ySpeed ; //bounce the ball
				 Ball.xSpeed += (-1 +Rand_num()%3 ) ;
			}
}

void Init_Ball(Sprite *ball)
{

	ball->x = SCREEN_W/2 - BALL_WIDTH/2 ;
    ball->y = SCREEN_H-(PADDLE_HEIGHT + BALL_HEIGHT) ;
	ball->Width =  BALL_WIDTH ;
	ball->Height = BALL_HEIGHT;
	ball->xSpeed  = 0 ;
	ball->ySpeed  = 0 ;
	ball->ImageData = (uint16_t*)image_ball ;
	ball->LayerId   = SPRITE ;
	ball->active =1;

#if 0
	    ball->x = 0;//SCREEN_H/2 - BALL_WIDTH/2 ;
	    ball->y =0; //SCREEN_W-(12 + BALL_HEIGHT) ;
		ball->Width =  BALL_WIDTH ;
		ball->Height = BALL_HEIGHT;
		ball->xSpeed  = 0 ;
		ball->ySpeed  = 0 ;
		ball->ImageData = image_ball ;
		ball->LayerId   = SPRITE ;
		ball->active =1;
#endif
}

void InitBricks(Sprite *bricks)
{
	for(int i = 0 ; i <BRICKS_WIDTH * BRICKS_HEIGHT ; i++)
	{
		   bricks[i].x = ONEBRICK_WIDHT * (i%BRICKS_WIDTH) ;
		   bricks[i].y = ONEBRICK_HEIGHT *(i%BRICKS_HEIGHT) ;
		   bricks[i].ImageData =(uint16_t*) image_Bricks[Rand_num()%6] ;
		   bricks[i].Width = ONEBRICK_WIDHT ;
		   bricks[i].Height = ONEBRICK_HEIGHT ;
		   bricks[i].LayerId = SPRITE ;
		   bricks[i].active = 1 ;
	}
}

void DrawBricks(Sprite *bricks)
{
	for(int i = 0 ; i <BRICKS_WIDTH * BRICKS_HEIGHT ; i++)
		{
		  DrawSprite(&bricks[i]) ;
		}
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

void GET_GYRO_Angles(void)
{
	GYRO_AngleXYZ(&gAngle) ;
}

void Small_tasks(Display *dis)
{
	GPIOG->ODR ^=1;
}
#if 0
void Init_bird(Sprite *bird)
{
	bird->Width= 50 ;
	bird->Height = 50 ;
	bird->ImageData = (uint16_t*)image_angryBird ;
	bird->LayerId = SPRITE ;
	bird->x = 0;
	bird->y = 0;
	bird->active = 1 ;
}

#endif
void Alien_init(void)
{
	aln.x = 0 ;
	aln.y = 0 ;
	aln.xSpeed = 2;
	aln.Frames_no = 3 ;
	aln.curr_frame = 0 ;

	aln.frames[0].w = aln.frames[1].w = aln.frames[2].w  = 72 ;
	aln.frames[0].h = aln.frames[1].h = aln.frames[2].h  = 80 ;

	aln.Width = 72 ;
	aln.Height = 80 ;

     Bitmap src_bmp ;
    src_bmp.data = (void*) image_alein ;
    src_bmp.w    = 216 ;
    src_bmp.h    = 80  ;
	Grape_frames(&aln ,&src_bmp , 72 , 216 );

	aln.ImageData = aln.frames[0].data ;

	aln.anim_cnt = 0 ;
	aln.LayerId = SPRITE ;
	aln.active = 1 ;
	aln.spr_ID = 0 ;
}


void fbird_Init()
{
	    fBird.x = 0 ;
		fBird.y = 0 ;
		fBird.xSpeed = 2;
		fBird.Frames_no = 3 ;
		fBird.curr_frame = 0 ;

		fBird.frames[0].w = fBird.frames[1].w = fBird.frames[2].w  = 16 ;
		fBird.frames[0].h = fBird.frames[1].h = fBird.frames[2].h  = 15 ;

		fBird.Width = 16 ;
		fBird.Height = 15 ;

	     Bitmap src_bmp ;
	    src_bmp.data = (void*) image_FBird ;
	    src_bmp.w    = 48 ;
	    src_bmp.h    = 15 ;
		Grape_frames(&fBird ,&src_bmp , 16 , 48 );

		fBird.ImageData = fBird.frames[0].data ;

		fBird.anim_cnt = 0 ;
		fBird.LayerId = SPRITE ;
		fBird.active = 1 ;
		fBird.spr_ID = 0 ;
}

void test_code(void)
{

			DrawSprite(&BackGround); //clear back buffer

			if(++fBird.anim_cnt > 15)
			{

				fBird.anim_cnt = 0 ;
			    if(++fBird.curr_frame >=fBird.Frames_no)
			    	 fBird.curr_frame =  0 ;

			    //fBird.ImageData = fBird.frames[fBird.curr_frame].data ;
			    fBird.ImageData = fBird.frames[1].data ;
			}
			fBird.x += 2 ;
			if(fBird.x > 239)
				fBird.x = -16 ;

			DrawSprite(&fBird) ;

			FlipBuffers();

}

void test_code_alien()
{
	DrawSprite(&BackGround); //clear back buffer

				if(++aln.anim_cnt > 15)
				{

					aln.anim_cnt = 0 ;
				    if(++aln.curr_frame >=aln.Frames_no)
				    	 aln.curr_frame =  0 ;

				    //aln.ImageData = aln.frames[aln.curr_frame].data ;
				    aln.ImageData = aln.frames[1].data ;
				}
				aln.x += 2 ;
				if(aln.x > 239)
					aln.x = -72 ;

				DrawSprite(&aln) ;

				FlipBuffers();
}

void toggle_led(void)
{
	GPIOG->ODR ^=1<<13 ;
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */



void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	while(1)
		{
		}
  /* USER CODE END Error_Handler_Debug */
}

void FileError_Handler(char *file, int line)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while(1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
