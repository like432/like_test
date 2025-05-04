#include "stm32f10x.h"                  // Device header


void AD_Init(void)
{
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//启动GPIOA区时钟
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); //启动ADC1区时钟
    
   RCC_ADCCLKConfig(RCC_PCLK2_Div6);//设置采样周期 72Mhz/6=12Mhz
    
   GPIO_InitTypeDef GPIO_Instructure;//创建结构体
   GPIO_Instructure.GPIO_Mode=GPIO_Mode_AIN;//设置模拟输入模式
   GPIO_Instructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
   GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_Init(GPIOA,&GPIO_Instructure); 
   
  

   ADC_InitTypeDef ADC_Instructure;//创建结构体
   ADC_Instructure.ADC_ContinuousConvMode=DISABLE;//不使用连续转换模式
   ADC_Instructure.ADC_DataAlign=ADC_DataAlign_Right;//数据右对齐
   ADC_Instructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//不使用外部时钟
   ADC_Instructure.ADC_Mode=ADC_Mode_Independent; //设置为独立工作模式
   ADC_Instructure.ADC_NbrOfChannel=1;//指定通道转换数目为1
   ADC_Instructure.ADC_ScanConvMode=DISABLE;//不使用扫描模式
   ADC_Init(ADC1,&ADC_Instructure);
   
   ADC_Cmd(ADC1,ENABLE);//启动ADC1
   //重置校准
   ADC_ResetCalibration(ADC1);//重新校准ADC1，校准完成以后标志位 置1
   while(ADC_GetResetCalibrationStatus(ADC1)==SET);//等待校准完成
   //开始校准
   while(ADC_GetCalibrationStatus(ADC1) == SET);//等待校准完成
    
}

uint16_t AD_Getvalue(uint16_t ADC_Channel_x)
{
    ADC_RegularChannelConfig(ADC1,ADC_Channel_x,1,ADC_SampleTime_55Cycles5);//设置ADC规则组 使用ADC1 使用第x通道 设定为第一序列 采样周期为55.5个ADCCLK
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件开启转换
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//等待转换完成
    return ADC_GetConversionValue(ADC1);//返回转换值
    
}












