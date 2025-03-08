#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//������ʼ��
void Key_Init(void)
{
	//
	GPIO_InitTypeDef GPIO_InitStructure;
	//ʹ��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
	 GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1 | GPIO_Pin_0;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 
	 GPIO_Init(GPIOB,&GPIO_InitStructure);
}

//����ֵ��ȡ
uint8_t Key_GetNum(void)
{
  uint8_t Key_Num = 0;
	if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1))==0)			//������Ϊ�ߵ�ƽ��
	{
		Delay_ms(20); 																		//��ʱ����
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);		//������Ϊ�ߵ�ƽ��ס��ѭ��
		Delay_ms(20); 
		Key_Num = 1;																			//����Ϊ�͵�ƽ�������ֵ
	}

	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)			//������Ϊ�ߵ�ƽ��
	{
		Delay_ms(20); 																		//��ʱ����
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0);	//������Ϊ�ߵ�ƽ��ס��ѭ��
		Delay_ms(20); 
		Key_Num = 2;																			//����Ϊ�͵�ƽ�������ֵ
	}
	return Key_Num;
}























