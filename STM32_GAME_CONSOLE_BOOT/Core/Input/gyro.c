/*
 * gyro.c
 *
 *  Created on: Apr 23, 2021
 *      Author: Islam
 */


#include "gyroscope.h"
#include "l3gd20.h"
#include "stm32f429i_discovery.h"

#define CALIBRATION_BUFFER_LENGTH       ((uint32_t) 2000u)
#define L3GD20_SENSITIVITY              ((float) 0.07f)
#define AVERAGE_WINDOW_SIZE              10
#define DT                               0.003f //(0.001f)

#define GYRO_ERROR 1
#define GYRO_OK    0


/*Private variables*/

static GYRO_DrvTypeDef *GyroscopeDrv;

static int32_t Offset_X = 0;
static int32_t Offset_Y = 0;
static int32_t Offset_Z = 0;

static float Noise_X = 0;
static float Noise_Y = 0;
static float Noise_Z = 0;

static float AngleRate_X = 0.0 ;
static float AngleRate_Y = 0.0 ;
static float AngleRate_Z = 0.0 ;

static float LastAngleRate_X = 0;
static float LastAngleRate_Y = 0;
static float LastAngleRate_Z = 0;

static int16_t calibrationBuffer_X[CALIBRATION_BUFFER_LENGTH];
static int16_t calibrationBuffer_Y[CALIBRATION_BUFFER_LENGTH];
static int16_t calibrationBuffer_Z[CALIBRATION_BUFFER_LENGTH];

static int32_t TempNoise_X = 0;
static int32_t TempNoise_Y = 0;
static int32_t TempNoise_Z = 0;

static int16_t gyro_rd[3] ;

static float angle_x, angle_y, angle_z;


uint8_t GYRO_Init(void)
{
	uint8_t ret = GYRO_ERROR;
	  uint16_t ctrl = 0x0000;
	  GYRO_InitTypeDef L3GD20_InitStructure;
	  GYRO_FilterConfigTypeDef L3GD20_FilterStructure={0,0};

	  if((L3gd20Drv.ReadID() == I_AM_L3GD20) )
	  {
	    /* Initialize the Gyroscope driver structure */
	    GyroscopeDrv = &L3gd20Drv;

	    /* MEMS configuration ----------------------------------------------------*/
	    /* Fill the Gyroscope structure */
	    L3GD20_InitStructure.Power_Mode = L3GD20_MODE_ACTIVE;
	    L3GD20_InitStructure.Output_DataRate = L3GD20_OUTPUT_DATARATE_1;
	    L3GD20_InitStructure.Axes_Enable = L3GD20_AXES_ENABLE;
	    L3GD20_InitStructure.Band_Width = L3GD20_BANDWIDTH_4;
	    L3GD20_InitStructure.BlockData_Update = L3GD20_BlockDataUpdate_Continous;
	    L3GD20_InitStructure.Endianness = L3GD20_BLE_LSB;
	    L3GD20_InitStructure.Full_Scale = L3GD20_FULLSCALE_500;

	    /* Configure MEMS: data rate, power mode, full scale and axes */
	    ctrl = (uint16_t) (L3GD20_InitStructure.Power_Mode | L3GD20_InitStructure.Output_DataRate | \
	                       L3GD20_InitStructure.Axes_Enable | L3GD20_InitStructure.Band_Width);

	    ctrl |= (uint16_t) ((L3GD20_InitStructure.BlockData_Update | L3GD20_InitStructure.Endianness | \
	                         L3GD20_InitStructure.Full_Scale) << 8);

	    /* Configure the Gyroscope main parameters */
	    GyroscopeDrv->Init(ctrl);

	    L3GD20_FilterStructure.HighPassFilter_Mode_Selection = L3GD20_HPM_NORMAL_MODE_RES;
	    L3GD20_FilterStructure.HighPassFilter_CutOff_Frequency = L3GD20_HPFCF_0;

	    ctrl = (uint8_t) ((L3GD20_FilterStructure.HighPassFilter_Mode_Selection |\
	                       L3GD20_FilterStructure.HighPassFilter_CutOff_Frequency));

	    /* Configure the Gyroscope main parameters */
	    GyroscopeDrv->FilterConfig(ctrl) ;

	    GyroscopeDrv->FilterCmd(L3GD20_HIGHPASSFILTER_ENABLE);

	    ret = GYRO_OK;
	  }
	  else
	  {
	    ret = GYRO_ERROR;
	  }
	  return ret;
}

void GYRO_Reset(void)
{
	L3gd20Drv.Reset();
}

void GYRO_GetXYZ(int16_t* RD_data)
{
	L3gd20Drv.GetXYZ(RD_data);
}


void GYRO_Calibaration(void)
{

/* Variables for moving average calculation */
	  int16_t averageWindow_X[AVERAGE_WINDOW_SIZE] = {0};
	  int16_t averageWindow_Y[AVERAGE_WINDOW_SIZE] = {0};
	  int16_t averageWindow_Z[AVERAGE_WINDOW_SIZE] = {0};

	  uint32_t windowPosition = 0;
	  int32_t tempSum_X = 0;
	  int32_t tempSum_Y = 0;
	  int32_t tempSum_Z = 0;
	for(uint32_t idx = 0; idx < CALIBRATION_BUFFER_LENGTH; idx++)
		            {
		                GYRO_GetXYZ(gyro_rd) ;
		                calibrationBuffer_X[idx] =gyro_rd[0] ;
		                calibrationBuffer_Y[idx] =gyro_rd[1] ;
		                calibrationBuffer_Z[idx] =gyro_rd[2] ;
		            }


	/* Calculate offset using moving average */
	for(uint32_t idx = 0; idx < CALIBRATION_BUFFER_LENGTH; idx++)
	            {
	              /* Subtract the oldest sample from the old sum, add the new number */
	              tempSum_X = tempSum_X - averageWindow_X[windowPosition] +
	                  calibrationBuffer_X[idx];
	              tempSum_Y = tempSum_Y - averageWindow_Y[windowPosition] +
	                  calibrationBuffer_Y[idx];
	              tempSum_Z = tempSum_Z - averageWindow_Z[windowPosition] +
	                  calibrationBuffer_Z[idx];

	              /* Store current sample in the average window */
	              averageWindow_X[windowPosition] = calibrationBuffer_X[idx];
	              averageWindow_Y[windowPosition] = calibrationBuffer_Y[idx];
	              averageWindow_Z[windowPosition] = calibrationBuffer_Z[idx];

	              /* Calculate the offset */
	              Offset_X =  tempSum_X / (int32_t)AVERAGE_WINDOW_SIZE;
	              Offset_Y =  tempSum_Y / (int32_t)AVERAGE_WINDOW_SIZE;
	              Offset_Z =  tempSum_Z / (int32_t)AVERAGE_WINDOW_SIZE;

	              /* Increment window position */
	              windowPosition++;

	              /* Check last window position */
	              if (windowPosition >= AVERAGE_WINDOW_SIZE)
	              {
	                /* Reset window position */
	                windowPosition = 0;
	              }
	              else
	              {
	                /* Do nothing, last position is not yet reached */
	              }
	            }

	            /* Calculate noise levels */
	            for(uint32_t idx = 0; idx < CALIBRATION_BUFFER_LENGTH; idx++)
	            {
	              if( ((int32_t) calibrationBuffer_X[idx] - Offset_X) > TempNoise_X)
	              {
	                TempNoise_X = (int32_t) calibrationBuffer_X[idx] - Offset_X;
	              }
	              else if( ((int32_t) calibrationBuffer_X[idx] - Offset_X) < -TempNoise_X)
	              {
	                TempNoise_X = -((int32_t) calibrationBuffer_X[idx] - Offset_X);
	              }

	              /* Calculate Y noise values */
	              if( ((int32_t) calibrationBuffer_Y[idx] - Offset_Y) > TempNoise_Y)
	              {
	                TempNoise_Y = (int32_t) calibrationBuffer_Y[idx] - Offset_Y;
	              }
	              else if( ((int32_t) calibrationBuffer_Y[idx] - Offset_Y) < -TempNoise_Y)
	              {
	                TempNoise_Y = -((int32_t) calibrationBuffer_Y[idx] - Offset_Y);
	              }

	              /* Calculate Z noise values */
	              if( ((int32_t) calibrationBuffer_Z[idx] - Offset_Z) > TempNoise_Z)
	              {
	                TempNoise_Z = (int32_t) calibrationBuffer_Z[idx] - Offset_Z;
	              }
	              else if( ((int32_t) calibrationBuffer_Z[idx] - Offset_Z) < -TempNoise_Z)
	              {
	                TempNoise_Z = -((int32_t) calibrationBuffer_Z[idx] - Offset_Z);
	              }
	            }

	            /* Get noise values in degree/s */
	            Noise_X = (float)TempNoise_X * L3GD20_SENSITIVITY;
	            Noise_Y = (float)TempNoise_Y * L3GD20_SENSITIVITY;
	            Noise_Z = (float)TempNoise_Z * L3GD20_SENSITIVITY;

}

void GYRO_AngleXYZ(GYRO_Angle* Pangle)
{
	GYRO_GetXYZ(gyro_rd);

	/* Get angle rate values in degrees/s */
	AngleRate_X = (float)(gyro_rd[0] - Offset_X) * L3GD20_SENSITIVITY;
	AngleRate_Y = (float)(gyro_rd[1] - Offset_Y) * L3GD20_SENSITIVITY;
	AngleRate_Z = (float)(gyro_rd[2] - Offset_Z) * L3GD20_SENSITIVITY;

	if( (AngleRate_X > Noise_X) || (AngleRate_X < -Noise_X) )
	{
		     //angle_y += AngleRate_Y *DT ;
			angle_x += ((AngleRate_X + LastAngleRate_X) * DT) / 2.0;

			 /* Store last sampled data */
			LastAngleRate_X = AngleRate_X;
		}
	if( (AngleRate_Y > Noise_Y) || (AngleRate_Y < -Noise_Y) )
	{
	     //angle_y += AngleRate_Y *DT ;
		angle_y += ((AngleRate_Y + LastAngleRate_Y) * DT) / 2.0;

		 /* Store last sampled data */
		LastAngleRate_Y = AngleRate_Y;
	}
	if( (AngleRate_Z > Noise_Z) || (AngleRate_Z < -Noise_Z) )
	{
		     //angle_y += AngleRate_Y *DT ;
			angle_z += ((AngleRate_Z + LastAngleRate_Z) * DT) / 2.0;

			 /* Store last sampled data */
			LastAngleRate_Z = AngleRate_Z;
		}

	Pangle->x = angle_x ;
	Pangle->y = angle_y ;
	Pangle->z = angle_z ;

}
