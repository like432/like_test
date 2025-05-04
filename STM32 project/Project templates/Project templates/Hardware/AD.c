#include "stm32f10x.h"                  // Device header


void AD_Init(void)
{
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����GPIOA��ʱ��
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); //����ADC1��ʱ��
    
   RCC_ADCCLKConfig(RCC_PCLK2_Div6);//���ò������� 72Mhz/6=12Mhz
    
   GPIO_InitTypeDef GPIO_Instructure;//�����ṹ��
   GPIO_Instructure.GPIO_Mode=GPIO_Mode_AIN;//����ģ������ģʽ
   GPIO_Instructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
   GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_Init(GPIOA,&GPIO_Instructure); 
   
  

   ADC_InitTypeDef ADC_Instructure;//�����ṹ��
   ADC_Instructure.ADC_ContinuousConvMode=DISABLE;//��ʹ������ת��ģʽ
   ADC_Instructure.ADC_DataAlign=ADC_DataAlign_Right;//�����Ҷ���
   ADC_Instructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//��ʹ���ⲿʱ��
   ADC_Instructure.ADC_Mode=ADC_Mode_Independent; //����Ϊ��������ģʽ
   ADC_Instructure.ADC_NbrOfChannel=1;//ָ��ͨ��ת����ĿΪ1
   ADC_Instructure.ADC_ScanConvMode=DISABLE;//��ʹ��ɨ��ģʽ
   ADC_Init(ADC1,&ADC_Instructure);
   
   ADC_Cmd(ADC1,ENABLE);//����ADC1
   //����У׼
   ADC_ResetCalibration(ADC1);//����У׼ADC1��У׼����Ժ��־λ ��1
   while(ADC_GetResetCalibrationStatus(ADC1)==SET);//�ȴ�У׼���
   //��ʼУ׼
   while(ADC_GetCalibrationStatus(ADC1) == SET);//�ȴ�У׼���
    
}

uint16_t AD_Getvalue(uint16_t ADC_Channel_x)
{
    ADC_RegularChannelConfig(ADC1,ADC_Channel_x,1,ADC_SampleTime_55Cycles5);//����ADC������ ʹ��ADC1 ʹ�õ�xͨ�� �趨Ϊ��һ���� ��������Ϊ55.5��ADCCLK
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);//�������ת��
    while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);//�ȴ�ת�����
    return ADC_GetConversionValue(ADC1);//����ת��ֵ
    
}












