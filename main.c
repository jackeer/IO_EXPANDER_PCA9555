void main(void)
{
			temp[0]=PCA9555_CM_Config_P0;
			temp[1]=0x00;
			temp[2]=0x00;
			PCA9555_DEVICE_Write(&temp,3);

			LED_NTSC1(ON),LED_NTSC2(OFF),LED_PAL1(OFF);
			LED_PALN(OFF),LED_PAL2(OFF),LED_PALM(OFF);
			temp[0]=PCA9555_CM_OUT_P0;
			temp[1]=PCA9555_LED_PORT.p0;
			temp[2]=PCA9555_LED_PORT.p1;
			PCA9555_DEVICE_Write(&temp,3);

			temp[0]=PCA9555_CM_Config_P0;
			temp[1]=0xFF;
			temp[2]=0xFF;
			PCA9555_DEVICE_Write(&temp,3);

			temp[0]=PCA9555_CM_IN_P0;
			temp[1]=0xFF;
			temp[2]=0xFF;
			temp[2]=PCA9555_DEVICE_Read(&temp,3);

			printf("\t P0=%d\n ", temp[2])
}
