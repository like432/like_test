#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t USART_RXFlag;
uint8_t USART_RXData;

void UART_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//启动GPIOA的时钟  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//启动UsART1的时钟 
    
   //初始化TX 
   GPIO_InitTypeDef GPIO_Instructure;//创建结构体
   GPIO_Instructure.GPIO_Mode=GPIO_Mode_AF_PP;//设置复用输入模式
   GPIO_Instructure.GPIO_Pin=GPIO_Pin_9;
   GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_Init(GPIOA,&GPIO_Instructure);//初始化pin9  
  //初始化RX
   GPIO_Instructure.GPIO_Mode=GPIO_Mode_IPU;//设置s上拉输入模式
   GPIO_Instructure.GPIO_Pin=GPIO_Pin_10;
   GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_Init(GPIOA,&GPIO_Instructure);//初始化pin10 

   USART_InitTypeDef USART_Instructure;
   USART_Instructure.USART_BaudRate=9600;//H设置波特率为9600
   USART_Instructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//不使用流控制器
   USART_Instructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;//同时使用接收发送模式
   USART_Instructure.USART_Parity=USART_Parity_No;//不使用奇偶校验
   USART_Instructure.USART_StopBits=USART_StopBits_1;//设置为一位停止位
   USART_Instructure.USART_WordLength=USART_WordLength_8b;//设置字长为8位
   USART_Init(USART1,&USART_Instructure);
   
   USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);//开启USART1的接收中断
   //配置终端系统
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//设置优先中断级
   
   NVIC_InitTypeDef NVIC_Instructure;
   NVIC_Instructure.NVIC_IRQChannel=USART1_IRQn;//设置中断通道为USART1
   NVIC_Instructure.NVIC_IRQChannelCmd=ENABLE;//判断为内部通道
   NVIC_Instructure.NVIC_IRQChannelPreemptionPriority=1;//设置抢占优先级
   NVIC_Instructure.NVIC_IRQChannelSubPriority=1;//设置次优先级
   NVIC_Init(&NVIC_Instructure);
   
   USART_Cmd(USART1,ENABLE);//启用USART1
 
}

void USART_SendByte(uint16_t Byte)//发送单一字节
{
   USART_SendData(USART1,Byte); //发送
   while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//等待发送完成（标志位为0/reset时正在发送）
    
}

void USART_SendArray(uint16_t *Array , uint16_t length)//发送数组
{
    uint16_t i;
    for(i=0;i<length;i++)
    {
      USART_SendByte(Array[i]);  
        
    }
}


void USART_SendString(char*String)//发送字符串
{
    uint8_t i;
    for(i=0;String[i]!='\0';i++)
    {
      USART_SendByte(String[i]);    
    }
    
}

uint32_t USART_Pow(uint16_t x,uint16_t y)//x为底数，y为次数(x^y)
{
    uint32_t result=1;
    while(y--)
    {
        result *=x;  
    }
    return result;
}

void USART_SendNumber(uint32_t Number ,uint8_t length)//发送数字
{
    uint8_t i;
    for(i=0;i<length;i++)
    {
        USART_SendByte((Number/USART_Pow(10,length-i-1))%10+'0'); 

    }

}
//发送中文
void USART_Printf(char*format ,...)//(...其他变量)
{
    char String[100]; 
    va_list arg;//创建链表
    va_start(arg,format);
    vsprintf(String,format,arg);
    va_end(arg);
    USART_SendString(String);
}

uint8_t USART_GetRXFlag(void)//获取接受标志位，并重装
{
    if(USART_RXFlag==1)
    {
        USART_RXFlag=0;//重装
        return 1;
    }
    return 0;
}

uint8_t USART_GetRXData(void)//获取接收到的数据
{
    return USART_RXData;
}

void USART1_IRQHandler(void)
{
   if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET) 
   {
     USART_RXData=USART_ReceiveData(USART1);//接收数据 
     USART_RXFlag = 1;//接收完成 
     USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);//清除USART1的标志位
   }
    
    
}


