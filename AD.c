#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStruct;
	//����ʱ�ӣ����÷�������GPIO����·���أ��ṹ��ADCת����
	//�������жϾ͵���ITconfig��������NVIC���ȼ��Դ����ж�
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//ADC��Ƶ��ѡ��6��Ƶ��ADCʱ���ź�����ADCclk=72Mhz
	//���ֻ��14Mhz����Ƶʱֻ��ѡ6/8��Ƶ������Ҫ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//PA0��ʼ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3; //��ͨ����ʼ��ʹ�õ���GPIO��
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//ADC������
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	
	//�ṹ���ʼ��ADC
	

	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent; 		//����ģʽ
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; //�Ҷ���
	ADC_InitStruct.ADC_NbrOfChannel = 1;  							//ͨ����Ŀ
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;  				//ɨ��ģʽ
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //��ʹ���ⲿ��������ʹ���������
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;		//����/����ת��
	
	ADC_Init(ADC1,&ADC_InitStruct);
	//����ʹ�õ���ת������ɨ��ģʽ��nbrofchannelͨ����Ŀ���ڷ�ɨ��ģʽ��ʵ���ã�ֻ������1��Ŀ��Ч
	//�˴��ɿ��жϻ��߿��Ź�
	
	//����ADC��Դ
	ADC_Cmd(ADC1,ENABLE);
	
	//�����ֲὨ�飬ʹ��У׼��������λУ׼�����ظ�λУ׼״̬����ʼУ׼���ȴ�У׼���
	ADC_ResetCalibration(ADC1);					//��λ��ѡУ׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1)== SET);//��ȡ��ѡADC��λУ׼�Ĵ���״̬
	ADC_StartCalibration(ADC1);					//��ʼУ׼����
	while(ADC_GetCalibrationStatus(ADC1)==SET);			//��ȡADCУ׼״̬
	
	//ʹ��whileѭ��ʹ�ó���ȴ���λ�Ĵ�����־λ�����������ȡADC-CR2�Ĵ�����ֵ���������1����������Ӳ����λ��0��δ�������while��ѭ����ȴ�
	//ͬ���ȡADCУ׼����ź�Ҳ�����

}


//��ȡУ׼���:�����������ת�����ȴ�ת����ɣ���ȡADC�Ĵ���
uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);//���������ݵ�����������ʱѡ��ָ����ͨ���Ϳ�����ɵ���ת��
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//�������ת��
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);//��ȡ��־λ״̬;ѡ��ת����ɺ��Զ�����ѭ����ֵ
	return ADC_GetConversionValue(ADC1); //����ת��ֵ�Ľ����������ȡDR�Ĵ���ֵ������ȡ����Զ������־λ������Ҫ�ֶ����

}


//ת��ʱ�䣺ָ����������Ϊ55.5��ת�����ڹ̶���12.5��
//��68���ڣ�ѡ����6��Ƶ����72/6=12Mhz��ʱ��Ϊ��1/12Mhz�� * 68 =5.6us


/**************************************************************************************************
*
*���ɸĳ�����ת��ģʽ������Ͳ��ϵ���ת��һ��
*ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
*��GetValueģʽ������return ADC_GetConversionValue(ADC1); 
*ADC_SoftwareStartConvCmd(ADC1,ENABLE);���ڳ�ʼ�����������ת��ģʽֻ��Ҫ����һ�ξͿ�����
*
**************************************************************************************************/





