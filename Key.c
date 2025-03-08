#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//按键初始化
void Key_Init(void)
{
	//
	GPIO_InitTypeDef GPIO_InitStructure;
	//使能
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1 | GPIO_Pin_0;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 
	 GPIO_Init(GPIOB,&GPIO_InitStructure);
}

//按键值获取
uint8_t Key_GetNum(void)
{
  uint8_t Key_Num = 0;
	if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1))==0)			//引脚若为高电平，
	{
		Delay_ms(20); 																		//延时消抖
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);		//引脚仍为高电平则卡住空循环
		Delay_ms(20); 
		Key_Num = 1;																			//否则为低电平，输出键值
	}

	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)			//按键若为高电平，
	{
		Delay_ms(20); 																		//延时消抖
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0);	//引脚仍为高电平则卡住空循环
		Delay_ms(20); 
		Key_Num = 2;																			//否则为低电平，输出键值
	}
	return Key_Num;
}























