#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStruct;
	//开启时钟，配置蜂鸣器，GPIO，多路开关，结构体ADC转换器
	//想配置中断就调用ITconfig，再配置NVIC优先级以触发中断
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//ADC分频，选择6分频，ADC时钟信号来自ADCclk=72Mhz
	//最大只能14Mhz，分频时只能选6/8分频以满足要求
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	//PA0初始化
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3; //多通道初始化使用到的GPIO口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//ADC规则组
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	
	//结构体初始化ADC
	

	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent; 		//独立模式
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; //右对齐
	ADC_InitStruct.ADC_NbrOfChannel = 1;  							//通道数目
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;  				//扫描模式
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //不使用外部触发，即使用软件触发
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;		//单次/连续转换
	
	ADC_Init(ADC1,&ADC_InitStruct);
	//这里使用单次转换，非扫描模式；nbrofchannel通道数目，在非扫描模式其实无用，只有序列1数目有效
	//此处可开中断或者看门狗
	
	//开启ADC电源
	ADC_Cmd(ADC1,ENABLE);
	
	//根据手册建议，使用校准函数：复位校准；返回复位校准状态；开始校准；等待校准完成
	ADC_ResetCalibration(ADC1);					//复位所选校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1)== SET);//获取所选ADC复位校准寄存器状态
	ADC_StartCalibration(ADC1);					//开始校准过程
	while(ADC_GetCalibrationStatus(ADC1)==SET);			//获取ADC校准状态
	
	//使用while循环使得程序等待复位寄存器标志位结果，函数读取ADC-CR2寄存器的值，由软件置1，结束后由硬件复位置0，未完成则在while空循环里等待
	//同理获取ADC校准完成信号也是如此

}


//获取校准结果:启动软件触发转换；等待转换完成；读取ADC寄存器
uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1,ADC_Channel,1,ADC_SampleTime_55Cycles5);//将参数传递到函数，调用时选择指定的通道就可以完成单次转换
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件触发转换
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);//获取标志位状态;选择转换完成后自动跳出循环读值
	return ADC_GetConversionValue(ADC1); //返回转换值的结果，函数读取DR寄存器值，而读取完后自动清除标志位，不需要手动清除

}


//转换时间：指定采样周期为55.5，转换周期固定的12.5，
//共68周期，选择了6分频，即72/6=12Mhz；时间为（1/12Mhz） * 68 =5.6us


/**************************************************************************************************
*
*还可改成连续转换模式，现象和不断单次转换一致
*ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
*在GetValue模式仅保留return ADC_GetConversionValue(ADC1); 
*ADC_SoftwareStartConvCmd(ADC1,ENABLE);放在初始化函数里，连续转换模式只需要触发一次就可以了
*
**************************************************************************************************/





