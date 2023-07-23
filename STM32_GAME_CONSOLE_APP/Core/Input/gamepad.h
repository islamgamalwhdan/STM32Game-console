#ifndef GAMPAD_H_
    #define GAMPAD_H_

/*
 * Connection from GampPad side (male side M Not F)
 * V5+            -> 6
 * GND            -> 8
 * GPIOB3(SH_LD)  -> 3
 * GPIOB4(clk)    -> 4
 * GPIOB7(datain) -> 2
 *
 */

#include "STMGame_types.h"

//Constants

#define GAMEPAD_NO_BTN       8
#define MAX_DEBOUNCE_COUNT   5

#define GAMEPAD_RIGHT    0x01
#define GAMEPAD_LEFT     0x02
#define GAMEPAD_DOWN     0x04
#define GAMEPAD_UP       0x08

#define GAMEPAD_START    0x10
#define GAMEPAD_SELECT   0x20

#define GAMEPAD_RED      0x40
#define GAMEPAD_YELLOW   0x80


//buttons
#define BUTTON_RIGHT    0
#define BUTTON_LEFT     1
#define BUTTON_DOWN     2
#define BUTTON_UP       3

#define BUTTON_START    4
#define BUTTON_SELECT   5

#define BUTTON_RED      6
#define BUTTON_YELLOW   7

typedef struct 
{
	u8
		right  : 1 ,
		left   : 1 ,
		down   : 1 ,
		up     : 1 ,
		start  : 1 ,
		select : 1 ,
		red    : 1 ,
		yellow : 1 ;
}GP_Button ;

typedef enum {
	GP_NOT_CONNECTED =0 ,
	GP_CONNECTED
}GP_State ;

typedef enum
{
	PRESSED = 0 ,
	RELEASED= 1
}GamePAD_BTNState;

typedef union
{
	u8         value ;
	GP_Button  btn   ;
}GP_RDState;

typedef struct
{
  u8  Curr_rd , Prev_rd ;
  GP_Button button  ;
  u8 BtnDebouceCounter[GAMEPAD_NO_BTN] ;
  GP_State  Connection ;

}GAMEPAD_BUTTON ;


//Functions Prototypes
void    GamePad_Init(void) ;
GAMEPAD_BUTTON GamePad_Read(void) ;


#endif // GAMEPAD_H_
