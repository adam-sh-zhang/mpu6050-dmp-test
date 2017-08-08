#include"stm32f10x.h"
#include "i2c.h"
#include "usart1.h"
#include "inv_mpu.h"
#include "delay.h"

int main(void)
{
	int count = 0;
	RCC_Configuration();
	Delay_Init();
	USART1_Config();
	printf("start\r\n");
	bsp_I2c_Init();
	Init_MPU6050();
	while(mpu_dmp_init())
 	{
		printf("mpu_dmp_init Exeing\r\n");
	}
	printf("mpu_dmp_init Exeing ok\r\n");
	Delay_ms(1000);
	//mpu_EXTI_Configuration();
	while(1)
	{	
		float pitch,roll,yaw; 		//Å·À­½Ç
		
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{ 
			//sprintf(buf,"pitch:%8.3f  roll:%8.3f  yaw:%8.3f \r\n",pitch,roll,yaw);
			printf("pitch:%8.3f  roll:%8.3f  yaw:%8.3f \r\n",pitch,roll,yaw);
			Delay_ms(3000);
		} else {
			count++;
			if(count==1000) {
				printf("failed 1000 times\r\n");
				count =0;
			}
			Delay_ms(10);
		}
		
	}
	return 0;
}


