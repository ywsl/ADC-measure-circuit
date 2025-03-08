#include "stm32f10x.h"                  // Device header



//led��ʼ������
void LED_Init(void)
{
	//����һ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	//ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8 | GPIO_Pin_9);	//��λ���ص�
}

//���ƺ���
void LED8_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);

}	

void LED9_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_9);
}	
/////////////////////////////////////////////////////////////////////////////

//�صƺ���
void LED8_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
}	

void LED9_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_9);
}	


///////////////////////////////////////////////////////////////////////////

/*void LED1_Turn()																				//��ת����
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)				//��ȡ��ǰ�˿����״̬
	{
		 LED1_OFF();										
	}
	else 
	{
		 LED1_ON();
	}
}

void LED2_Turn()																				//��ת����
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)
	{
		LED2_OFF();
	}
	else 
	{
		LED2_ON();
	}
}
*/

void LED_ADC_Control()
{	
	uint16_t light;
	
	while(1)
	{
		light = ADC_GetConversionValue(ADC1);
		if(light<1500)
		{
			LED8_ON();
			if(light<800)
			LED9_ON();
				if(light>2500)
				{
					LED8_OFF();
					LED9_OFF();
				}
		}
	}

}
























