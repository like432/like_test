#include "stm32f10x.h"                  // Device header

void GPIOA_Init(void )
{
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //����APB2����ʱ�ӣ�����GPIOC��
    GPIO_InitTypeDef GPIO_Instructure;//�����ṹ��
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Instructure.GPIO_Pin=GPIO_Pin_0;
    GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Instructure);
    //��ʼ��GPIOA_PIN0  Ϊ��©���ģʽ
}


void GPIOB_Init(void )
{
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    //����APB2����ʱ�ӣ�����GPIOC��
    GPIO_InitTypeDef GPIO_Instructure;//�����ṹ��
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Instructure.GPIO_Pin=GPIO_Pin_13;
    GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_Instructure);
    //��ʼ��GPIOB_PIN13 Ϊ��©���ģʽ

}


void GPIOC_Init(void )
{
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    //����APB2����ʱ�ӣ�����GPIOC��
    GPIO_InitTypeDef GPIO_Instructure;//�����ṹ��
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Instructure.GPIO_Pin=GPIO_Pin_13;
    GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_Instructure);
    //��ʼ��GPIOC_PIN13 Ϊ��©���ģʽ

}

void GPIO_ALLInit( )
{
    GPIOA_Init();
    GPIOB_Init();
    GPIOC_Init();
}

