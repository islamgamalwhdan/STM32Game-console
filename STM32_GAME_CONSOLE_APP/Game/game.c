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
#include <string.h>
#include "game.h"


#define RANGE_RAND(min , max) (int)(Rand_num()%( (max)+1 - (min) ) +(min) )

//Global Variables
Sprite BackGround ;
Sprite Ship , BigAStr[NUM_ASTEROIDS];
Sprite bullet[MAX_BULLETS];
Sprite Explo[MAX_EXPLODES] ;
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

  InitDisplay((void*)AST_background , 0);
  GamePad_Init();
  touchpad_init();

  //umm_init() for dynamic memory allocation ,
  //and it must be called after SDRAM initialization !!
  umm_init();

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
		for(int i = 0 ; i < NUM_ASTEROIDS ; i++)
		      {
			     Asteriod_Init(&BigAStr[i],i) ;
		      }
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
   spr->ImageData =(uint16_t*) AST_background ;
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


void Asteriod_Init(Sprite * astr , u8 index)
{
	Bitmap frames_arr[16] ;


	astr->x = RANGE_RAND(0,SCREEN_W) ;
	astr->y = RANGE_RAND(0,SCREEN_H) ;

	astr->xSpeed = RANGE_RAND(1,3) ;
	astr->ySpeed = RANGE_RAND(1,3) ;
	//Init frames
	astr->Frames_no = 16 ;
	astr->curr_frame = 0 ;

	for( u8 i =0 ; i<16 ; i++)
			{
				astr->frames[i].w = 32 ;
				astr->frames[i].h = 32 ;
			}

	if(astr->active==0) // to prevent dynamic memory allocation while the sprite already created.
			{
		       Bitmap src_bmp ;
		       src_bmp.data = (void*) image_bigastr ;
		       src_bmp.w    = 32*16 ;
		       src_bmp.h    = 32 ;
		       if(index == 0) // grape frames once (only at astr[0])
			   {
		    	   Grape_frames(astr->frames ,&src_bmp , astr->Frames_no  );
			   }
		       else
		       {
		    	   //Copy frames from the preceding asteroid frame ex astr[4].frames = astr[0].frames
		    	   memcpy(astr->frames , (astr-1)->frames , astr->Frames_no * sizeof(Bitmap));
		       }
			}
	astr->ImageData = astr->frames[0].data ;
	astr->anim_cnt = 0 ;
	astr->anim_sp  = 2 ;

	astr->Width =  32 ;
	astr->Height = 32 ;
	astr->active =  1 ;
	astr->continus_anim = 1 ;
}

void Asteriod_update(Sprite * astr)
{
	astr->x += astr->xSpeed ;
	astr->y += astr->ySpeed ;

	if(astr->x > SCREEN_W) astr->x = 0 ;
	if(astr->x < 0)        astr->x = SCREEN_W;
	if(astr->y > SCREEN_H) astr->y = 0 ;
	if(astr->y < 0)        astr->y = SCREEN_H;

}



void fire(Sprite *shp , Sprite * bul)
{
	//init each bullet depending on the space position and angle

	int r = SHIP_H/2 ;

	bul->x = r*Fast_Sin(shp->angle) + shp->x + shp->Width/2.0  ;
	bul->y = r*(1-Fast_Cos(shp->angle) ) + shp->y ;
	bul->xSpeed =  Fast_Sin(shp->angle) *4.0f + shp->xSpeed ;
	bul->ySpeed = -Fast_Cos(shp->angle) *4.0f + shp->ySpeed ;
	bul->ImageData = image_bullet ;
	bul->Width  = BULLET_W ;
	bul->Height = BULLET_H ;
	bul->active = 1 ;
}

void Bullet_update(Sprite * bul)
{
	bul->x += bul->xSpeed ;
	bul->y += bul->ySpeed ;

	//Boundaries

	if(bul->x < 0 || bul->x > (SCREEN_W - bul->Width)
			|| bul-> y < 0 || bul->y > (SCREEN_H - bul->Height) )
	{
		bul->active = 0;
	}
}

void Explosion_Init(Sprite * exp ,Sprite * ast , u8 index)
{

	exp->x = ast->x ;
	exp->y = ast->y ;
	exp->Frames_no = EXPLOS_FRAMES ;
	exp->curr_frame = 0 ;

	for(u8 i =0 ; i< EXPLOS_FRAMES ; i++)
	{
		exp->frames[i].w = EXPLOS_W ;
		exp->frames[i].h = EXPLOS_H  ;
	}

	exp->anim_cnt = 0 ;
	exp->anim_sp = 2 ;

	exp->Width = EXPLOS_W ;
	exp->Height = EXPLOS_H ;

	if(exp->active==0) // to prevent dynamic memory allocation while the sprite already created.
			{
		       Bitmap src_bmp ;
		       src_bmp.data = (void*) image_explosion ;
		       src_bmp.w    = EXPLOS_W * EXPLOS_FRAMES ;
		       src_bmp.h    = EXPLOS_H ;

			   if(index == 0) // grape frames once (only at astr[0])
			   {
		    	   Grape_frames(exp->frames ,&src_bmp , EXPLOS_FRAMES  );
			   }
		       else
		       {
		    	   //Copy frames from the preceding asteroid frame ex astr[4].frames = astr[0].frames
		    	   memcpy(exp->frames , (exp-1)->frames , EXPLOS_FRAMES * sizeof(Bitmap));
		       }
			}
	exp->ImageData = exp->frames[0].data ;
	exp->active = 1 ;
	exp->continus_anim = 0 ;
}

void Explode(Sprite * exp ,Sprite * ast , u8 index)
{
	Explosion_Init(exp ,ast, index) ;

}

void Ship_Init(void)
{
		Ship.x = (SCREEN_W -SHIP_W)/2 ;
		Ship.y = (SCREEN_H - SHIP_H)/2 ;
		Ship.xSpeed = 0 ;
		Ship.ySpeed = 0 ;
		//Init frames
		Ship.Frames_no = 16 ;
		Ship.curr_frame = 0 ;


		for( u8 i =0 ; i<16 ; i++)
		{
			Ship.frames[i].w = SHIP_W ;
			Ship.frames[i].h = SHIP_H ;
		}

		Ship.anim_cnt = 0 ;
		Ship.anim_sp = 2 ;

		Ship.Width = SHIP_W ;
		Ship.Height = SHIP_H ;

		if(Ship.active==0) // to prevent dynamic memory allocation while the sprite already created.
		{
	       Bitmap src_bmp ;
	       src_bmp.data = (void*) image_spaceship ;
	       src_bmp.w    = SHIP_W * Ship.Frames_no ;
	       src_bmp.h    = SHIP_H ;
		   Grape_frames(Ship.frames ,&src_bmp , Ship.Frames_no  );
		}
		Ship.ImageData = Ship.frames[0].data ;

		Ship.active = 1 ;
}

void ship_test(void)
{
	static int i  , rgt_cnt , lft_cnt , up_cnt , down_cnt,  fire_pressed,fire_cnt ;
	static int expl_cnt ;
	for(int n = 0 ; n < NUM_ASTEROIDS ; n++)
	{
		Update_animation(&BigAStr[n]) ;
		Asteriod_update(&BigAStr[n]);
	}

	for(int n = 0 ; n< MAX_BULLETS; n++)
	{
		Bullet_update(&bullet[n]);
	}

   for(int n = 0; n <MAX_EXPLODES ; n++ )
   { 
	 Update_animation(&Explo[n]) ;
   }
	if(GamePad.button.left == PRESSED && ++lft_cnt >2 )
	{
		lft_cnt = 0;
		if(++i>15) i= 0 ;

	}
	if(GamePad.button.right == PRESSED && ++rgt_cnt >2)
	{
		rgt_cnt = 0 ;
		if(--i<0) i=15 ;

	}

	if(GamePad.button.up == PRESSED && ++up_cnt >2)
		{
			up_cnt = 0 ;
			Ship.xSpeed += Fast_Sin(Ship.angle)*0.2f;
			Ship.ySpeed -= Fast_Cos(Ship.angle)*0.2f;

		}
	else
	{
		Ship.xSpeed *= 0.99;
		Ship.ySpeed *= 0.99;
	}


	if(GamePad.button.yellow == PRESSED && !fire_pressed)
			{
		        fire_pressed = 1 ;
				fire(&Ship ,&bullet[fire_cnt] );
				if(fire_cnt++ > MAX_BULLETS) fire_cnt = 0;

			}
	if(GamePad.button.yellow == RELEASED && fire_pressed)
	{
		fire_pressed = 0;
	}

	Ship.angle = (16-i)*22.5f ;

	Ship.x += Ship.xSpeed ;
	Ship.y += Ship.ySpeed ;
	if(Ship.x < 0) Ship.x = SCREEN_W - Ship.Width ;
	if(Ship.x >SCREEN_W) Ship.x =0 ;
	if(Ship.y < 0) Ship.y = SCREEN_H - Ship.Height ;
    if(Ship.y >SCREEN_H) Ship.y =0 ;

	Ship.ImageData = Ship.frames[i].data ;


	//Collision check
	for(u8 a = 0 ; a< NUM_ASTEROIDS ; a++)
	{
		if(BigAStr[a].active == 0) continue ;
		for(u8 b = 0 ; b< fire_cnt ; b++)
		{
			if(bullet[b].active == 0) continue ;
			if( collision(&BigAStr[a], &bullet[b]) && BigAStr[a].active )
			{
				BigAStr[a].active = bullet[b].active = 0;
				Explode(&Explo[expl_cnt] ,&BigAStr[a], expl_cnt) ;
				if(++expl_cnt> MAX_EXPLODES) expl_cnt = 0 ;
				
			}
		}
	}
	//Draw
	clearScreen();
	DrawSprite(&Ship) ;
	for(int n = 0  ;n < MAX_EXPLODES ; n++)
	   {
		  DrawSprite(&Explo[n]);
	   }
	for(int n =0 ; n < NUM_ASTEROIDS ;n++)
	   {
		  DrawSprite(&BigAStr[n]);
	   }
	for(int n = 0 ; n< MAX_BULLETS; n++)
	{
		DrawSprite(&bullet[n]) ;
	}
	FlipBuffers();

}

