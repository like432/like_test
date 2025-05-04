#include "stm32f10x.h"                  // Device header

void GPIOA_Init(void )
{
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //启动APB2总线时钟，激活GPIOC区
    GPIO_InitTypeDef GPIO_Instructure;//创建结构体
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_IPU;
    GPIO_Instructure.GPIO_Pin=GPIO_Pin_0;
    GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Instructure);
    //初始化GPIOA_PIN0  为开漏输出模式
}


void GPIOB_Init(void )
{
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    //启动APB2总线时钟，激活GPIOC区
    GPIO_InitTypeDef GPIO_Instructure;//创建结构体
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Instructure.GPIO_Pin=GPIO_Pin_13;
    GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_Instructure);
    //初始化GPIOB_PIN13 为开漏输出模式

}


void GPIOC_Init(void )
{
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
    //启动APB2总线时钟，激活GPIOC区
    GPIO_InitTypeDef GPIO_Instructure;//创建结构体
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Instructure.GPIO_Pin=GPIO_Pin_13;
    GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_Instructure);
    //初始化GPIOC_PIN13 为开漏输出模式

}

void GPIO_ALLInit( )
{
    GPIOA_Init();
    GPIOB_Init();
    GPIOC_Init();
}

