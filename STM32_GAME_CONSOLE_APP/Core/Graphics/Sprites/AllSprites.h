#ifndef ALL_SPRITES_
#define ALL_SPRITES_


static const uint16_t image_explosion[] =
	{
	      #include "explosion.bin"
	};

static const uint16_t image_spaceship[] =
{
		#include "spaceship.bin"
};

static const uint16_t image_bullet[] =
{
        #include "bullet.bin"
};
static const uint16_t image_bigastr[] =
{
		#include "BigAstr.bin"
};


static const
 uint16_t AST_background[] =
{
		#include "back_ast.bin"
};


/*
static  __attribute__( ( section( ".sdram3" ) ) )
 uint16_t image_explosion[] =
{
      #include "explosion.bin"
};

static const uint16_t image_FBird[] =
{
		#include "FBird.bin"
};

static const uint16_t image_pipeUp[] =
{
            #include "pipeDwn.bin"
};

static const uint16_t image_pipeDown[] =
{
            #include "pipeUp.bin"
};
*/

#endif //ALL_SPRITES_
