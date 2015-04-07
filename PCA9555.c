/***************************************************************************************************
 *
 * File name   : PCA9555.c
 *
 * Description : No song Write by JK
 *
 * COPYRIGHT JK 2008
 *
 **************************************************************************************************/


/*********************************************************************************************
                                       Including
*********************************************************************************************/
#include "maindef.h"

#if (JK_PCA9555_EN)
/*********************************************************************************************
                         Constants, Types, struct and Variables declarations
*********************************************************************************************/
// xdata volatile struct IICTag PCA9555IIC;

xdata PCA9555_LED_POSTR PCA9555_LED_PORT;

/*********************************************************************************************
                                       Functions
*********************************************************************************************/


/*================================================================================
Name        : PCA9555_IIC_Delay
Description : Do you no eye can see
Parameters  : 
Return Value: None
See Also    : ALL
================================================================================*/
void PCA9555_IIC_Delay(void)
{
  idata unsigned char n;

  n=PCA9555_IIC_Delay_Time;
  while(n--)
  	{
	_nop_();
  	}
}

/*================================================================================
Name        : PCA9555_IIC_Start
Description : No Song Write JK
Parameters  : None
Return Value: None
See Also    : ALL
================================================================================*/
void PCA9555_IIC_Start(void)
{
	PCA9555_IIC_SCL(HI); PCA9555_IIC_SDA(HI);
	PCA9555_IIC_Delay();
	PCA9555_IIC_SDA(LO); PCA9555_IIC_SCL(HI);
	PCA9555_IIC_Delay();
	PCA9555_IIC_SDA(LO); PCA9555_IIC_SCL(LO);
	PCA9555_IIC_Delay();
}

/*================================================================================
Name        : IIC_Stop
Description : Do you no eye can see
Parameters  : None
Return Value: None
See Also    : ALL
================================================================================*/
void PCA9555_IIC_Stop(void) 
{  
	PCA9555_IIC_SDA(LO); PCA9555_IIC_SCL(LO);
	PCA9555_IIC_Delay();
	PCA9555_IIC_SDA(LO); PCA9555_IIC_SCL(HI);
	PCA9555_IIC_Delay();
	PCA9555_IIC_SDA(HI); PCA9555_IIC_SCL(HI);
	PCA9555_IIC_Delay();
}

/*================================================================================
Name        :
Description :
Parameters  :
Return Value:
See Also    :
================================================================================*/
#if PCA9555_READ
void PCA9555_IIC_Acknowledge(BOOL ack) 
{
	PCA9555_IIC_SDA(LO); PCA9555_IIC_SCL(LO);
	PCA9555_IIC_SDA=(ack ? 0:1);   PCA9555_IIC_Delay();
	PCA9555_IIC_SCL(HI);    PCA9555_IIC_Delay();
	PCA9555_IIC_SCL(LO);   PCA9555_IIC_Delay();
}
#endif

/*================================================================================
Name        :
Description :
Parameters  :
Return Value:
See Also    :
================================================================================*/
BOOL PCA9555_IIC_Set_Data(unsigned char Data)
{
  idata unsigned char i,Byte;
  BOOL ACK;

    Byte=Data;          
    for(i=0; i<8; i++) 
    {
      PCA9555_IIC_SDA(Byte&0x80); PCA9555_IIC_SCL(LO);
      PCA9555_IIC_Delay();
      PCA9555_IIC_SCL(HI); PCA9555_IIC_Delay(); 
      Byte<<=1;    
      PCA9555_IIC_SCL(LO); PCA9555_IIC_Delay(); 
    }
	PCA9555_IIC_SDA(HI); PCA9555_IIC_SCL(LO);
	PCA9555_IIC_Delay();
	PCA9555_IIC_SCL(HI); PCA9555_IIC_Delay();
	ACK=(PCA9555_IIC_SDA_READ() ? 0:1); PCA9555_IIC_Delay();
	PCA9555_IIC_SCL(LO); PCA9555_IIC_Delay();
	PCA9555_IIC_SDA(LO); PCA9555_IIC_Delay();

  return ACK;
}


/*================================================================================
Name        :
Description :
Parameters  :
Return Value:
See Also    :
================================================================================*/
#if PCA9555_READ
BYTE PCA9555_IIC_Get_Data(void)
{
  idata unsigned int i,Byte;

    Byte=0;   
   
      PCA9555_IIC_SDA(HI), PCA9555_IIC_Delay();
      for(i=0; i<8; i++) 
      {
        PCA9555_IIC_SCL(HI), PCA9555_IIC_Delay();
        Byte<<=1;
        Byte|=PCA9555_IIC_SDA, PCA9555_IIC_Delay();
        PCA9555_IIC_SCL(LO), PCA9555_IIC_Delay();
      }
	PCA9555_IIC_Acknowledge(1);
	return Byte;    
}
#endif

/*================================================================================
Name        :
Description :
Parameters  :
Return Value:
See Also    :
================================================================================*/
void PCA9555_DEVICE_Write(BYTE *IIC_Data,BYTE Length)
{
 BYTE Byte;

 Byte=Length;

 PCA9555_IIC_SDA_SET(HI);

 PCA9555_IIC_Start();
 if(!(PCA9555_IIC_Set_Data(PCA9555_DEVID)))	// Detect ACK
	{
	#if (JK_DEBUG_EN)
	Print_Num(1, 7, PCA9555_DEVID, TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 NONE ACK DEVID",TEXT_COLOR);
	#endif
	return;
	}
 else
	{
	#if (JK_DEBUG_EN)
	Print_Num(1, 7, PCA9555_DEVID, TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 OK ACK DEVID",TEXT_COLOR);
	#endif
	}

 if(!(PCA9555_IIC_Set_Data(IIC_Data[0])))	// Detect ACK
	{
	#if (JK_DEBUG_EN)
	Print_Num(2, 7, IIC_Data[0], TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 NONE ACK COMMAND",TEXT_COLOR);
	#endif
	return;
	}
 else
	{
	#if (JK_DEBUG_EN)
	Print_Num(2, 7, IIC_Data[0], TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 OK ACK COMMAND",TEXT_COLOR);
	#endif
	}

 if(!(PCA9555_IIC_Set_Data(IIC_Data[1])))	// Detect ACK
	{
	#if (JK_DEBUG_EN)
	Print_Num(3, 7, IIC_Data[1], TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 NONE ACK DATA1",TEXT_COLOR);
	#endif
	return;
	}
 else
	{
	#if (JK_DEBUG_EN)
	Print_Num(3, 7, IIC_Data[1], TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 OK ACK DATA1",TEXT_COLOR);
	#endif
	}

 if(!(PCA9555_IIC_Set_Data(IIC_Data[2])))	// Detect ACK
	{
	#if (JK_DEBUG_EN)
	Print_Num(4, 7, IIC_Data[2], TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 NONE ACK DATA2",TEXT_COLOR);
	#endif
	return;
	}
 else
	{
	#if (JK_DEBUG_EN)
	Print_Num(4, 7, IIC_Data[2], TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 OK ACK DATA2",TEXT_COLOR);
	#endif
	}
 PCA9555_IIC_Stop();
}


/*================================================================================
Name        :
Description :
Parameters  :
Return Value:
See Also    :
================================================================================*/
#if PCA9555_READ
BYTE PCA9555_DEVICE_Read(BYTE *IIC_Data,BYTE Length)
{
 BYTE DATA;

 DATA=Length;

 PCA9555_IIC_SDA_SET(HI);
 PCA9555_IIC_Start();
 if(!(PCA9555_IIC_Set_Data(PCA9555_DEVID)))
 	{
 	#if (JK_DEBUG_EN)
	Print_Num(1, 7, PCA9555_DEVID, TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 NONE ACK DEVID",TEXT_COLOR);
	#endif
	return 0;
	}
 else
	{
	#if (JK_DEBUG_EN)
	Print_Num(1, 7, PCA9555_DEVID, TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 OK ACK DEVID",TEXT_COLOR);
	#endif
 	}

 if(!(PCA9555_IIC_Set_Data(IIC_Data[0])))	// Detect ACK
	{
	#if (JK_DEBUG_EN)
	Print_Num(2, 7, IIC_Data[0], TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 NONE ACK COMMAND",TEXT_COLOR);
	#endif
	return 0;
	}
 else
	{
	#if (JK_DEBUG_EN)
	Print_Num(2, 7, IIC_Data[0], TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 OK ACK COMMAND",TEXT_COLOR);
	#endif
	}

  if(!(PCA9555_IIC_Set_Data(IIC_Data[1])))	 // Detect ACK
	 {
   #if (JK_DEBUG_EN)
	 Print_Num(2, 7, IIC_Data[1], TEXT_COLOR, HEX_VALUE);
	 Print_String(5,7,"PCA9555 NONE ACK COMMAND",TEXT_COLOR);
   #endif
	 return 0;
	 }
  else
	 {
   #if (JK_DEBUG_EN)
	 Print_Num(2, 7, IIC_Data[1], TEXT_COLOR, HEX_VALUE);
	 Print_String(5,7,"PCA9555 OK ACK COMMAND",TEXT_COLOR);
   #endif
	 }

  if(!(PCA9555_IIC_Set_Data(IIC_Data[2])))	 // Detect ACK
	 {
   #if (JK_DEBUG_EN)
	 Print_Num(2, 7, IIC_Data[2], TEXT_COLOR, HEX_VALUE);
	 Print_String(5,7,"PCA9555 NONE ACK COMMAND",TEXT_COLOR);
   #endif
	 return 0;
	 }
  else
	 {
   #if (JK_DEBUG_EN)
	 Print_Num(2, 7, IIC_Data[2], TEXT_COLOR, HEX_VALUE);
	 Print_String(5,7,"PCA9555 OK ACK COMMAND",TEXT_COLOR);
   #endif
	 }

  if(!(PCA9555_IIC_Set_Data((PCA9555_DEVID|0x01))))
 	{
 	#if (JK_DEBUG_EN)
	Print_Num(1, 7, PCA9555_DEVID, TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 NONE ACK DEVID",TEXT_COLOR);
	#endif
	return 0;
	}
 else
	{
	#if (JK_DEBUG_EN)
	Print_Num(1, 7, PCA9555_DEVID, TEXT_COLOR, HEX_VALUE);
	Print_String(5,7,"PCA9555 OK ACK DEVID",TEXT_COLOR);
	#endif
 	}
 DATA=PCA9555_IIC_Get_Data();
 Print_Num(3, 7, DATA, TEXT_COLOR, HEX_VALUE);
 Print_String(5,7,"KEY DATA",TEXT_COLOR);
 PCA9555_IIC_Stop();
 return DATA;
}
#endif

#endif

