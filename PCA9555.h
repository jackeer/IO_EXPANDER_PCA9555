/***************************************************************************************************
 *
 * File name   : PCA9555.h
 *
 * Description : No song Write by JK
 *
 * COPYRIGHT JK 2008
 *
 **************************************************************************************************/
#ifndef _PCA9555
#define _PCA9555
//==================================================================================================

/*********************************************************************************************
                                       Including
*********************************************************************************************/
#include "maindef.h"

#if (JK_PCA9555_EN)

#define PCA9555_READ	1
/*********************************************************************************************
                         Constants, Types, struct and Variables declarations
*********************************************************************************************/
#define PCA9555_IIC_SDA_SET(x)		(x)?(P5_OPDN|=0x3F):(P5_OPDN&=~0xFF)	// PCA9555_IIC_SDA
#define PCA9555_IIC_SDA(x)			(x)?(P5_DATA|=0x40):(P5_DATA&=~0x40)	// PCA9555_IIC_SDA
#define PCA9555_IIC_SCL(x)			(x)?(P5_DATA|=0x80):(P5_DATA&=~0x80)	// PCA9555_IIC_SCL
#define PCA9555_IIC_SDA_READ()		(P5_DATA&0x40)							// PCA9555_IIC_SDA

// P5_OE|=0x80

#define PCA9555_IIC_Delay_Time 0x01

#define PCA9555_DEVID 0x4E

#define PCA9555_CM_IN_P0					0x00
#define PCA9555_CM_IN_P1					0x01
#define PCA9555_CM_OUT_P0					0x02
#define PCA9555_CM_OUT_P1					0x03
#define PCA9555_CM_Polarity_Inversion_P0	0x04
#define PCA9555_CM_Polarity_Inversion_P1	0x05
#define PCA9555_CM_Config_P0				0x06
#define PCA9555_CM_Config_P1				0x07

typedef unsigned char BYTE;
typedef bit BOOL;

typedef struct PCA9555_LED_PO_OUT
{
	unsigned char p0;
	unsigned char p1;
}PCA9555_LED_POSTR;

extern xdata PCA9555_LED_POSTR PCA9555_LED_PORT;

#define LED_POWER(x) x?(PCA9555_LED_PORT.p0&=~0x01,PCA9555_LED_PORT.p1=~0x00):(PCA9555_LED_PORT.p0=~0x00,PCA9555_LED_PORT.p1=~0x00)
#define LED_VGA(x) x?(PCA9555_LED_PORT.p0&=~0x02):(PCA9555_LED_PORT.p0|=0x02)
#define LED_SV(x) x?(PCA9555_LED_PORT.p0&=~0x04):(PCA9555_LED_PORT.p0|=0x04)
#define LED_AV(x) x?(PCA9555_LED_PORT.p0&=~0x08):(PCA9555_LED_PORT.p0|=0x08)

#define LED_NTSC1(x) x?(PCA9555_LED_PORT.p0&=~0x10):(PCA9555_LED_PORT.p0|=0x10)
#define LED_NTSC2(x) x?(PCA9555_LED_PORT.p0&=~0x20):(PCA9555_LED_PORT.p0|=0x20)

#define LED_PAL1(x) x?(PCA9555_LED_PORT.p0&=~0x40):(PCA9555_LED_PORT.p0|=0x40)
#define LED_PALN(x) x?(PCA9555_LED_PORT.p0&=~0x80):(PCA9555_LED_PORT.p0|=0x80)

#define LED_PAL2(x) x?(PCA9555_LED_PORT.p1&=~0x01):(PCA9555_LED_PORT.p1|=0x01)
#define LED_PALM(x) x?(PCA9555_LED_PORT.p1&=~0x02):(PCA9555_LED_PORT.p1|=0x02)
#define LED_ALL(x) x?(PCA9555_LED_PORT.p0=0x00,PCA9555_LED_PORT.p1=0x00):(PCA9555_LED_PORT.p0=~0x00,PCA9555_LED_PORT.p1=~0x00)

/*********************************************************************************************
                                       Functions
*********************************************************************************************/

extern void PCA9555_DEVICE_Write(BYTE *,BYTE );
#if PCA9555_READ
extern BYTE PCA9555_DEVICE_Read(BYTE *,BYTE );
#endif

#endif
#endif


