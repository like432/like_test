#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t USART_RXFlag;
uint8_t USART_RXData;

void UART_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����GPIOA��ʱ��  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//����UsART1��ʱ�� 
    
   //��ʼ��TX 
   GPIO_InitTypeDef GPIO_Instructure;//�����ṹ��
   GPIO_Instructure.GPIO_Mode=GPIO_Mode_AF_PP;//���ø�������ģʽ
   GPIO_Instructure.GPIO_Pin=GPIO_Pin_9;
   GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_Init(GPIOA,&GPIO_Instructure);//��ʼ��pin9  
  //��ʼ��RX
   GPIO_Instructure.GPIO_Mode=GPIO_Mode_IPU;//����s��������ģʽ
   GPIO_Instructure.GPIO_Pin=GPIO_Pin_10;
   GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_Init(GPIOA,&GPIO_Instructure);//��ʼ��pin10 

   USART_InitTypeDef USART_Instructure;
   USART_Instructure.USART_BaudRate=9600;//H���ò�����Ϊ9600
   USART_Instructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��ʹ����������
   USART_Instructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;//ͬʱʹ�ý��շ���ģʽ
   USART_Instructure.USART_Parity=USART_Parity_No;//��ʹ����żУ��
   USART_Instructure.USART_StopBits=USART_StopBits_1;//����Ϊһλֹͣλ
   USART_Instructure.USART_WordLength=USART_WordLength_8b;//�����ֳ�Ϊ8λ
   USART_Init(USART1,&USART_Instructure);
   
   USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);//����USART1�Ľ����ж�
   //�����ն�ϵͳ
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);//���������жϼ�
   
   NVIC_InitTypeDef NVIC_Instructure;
   NVIC_Instructure.NVIC_IRQChannel=USART1_IRQn;//�����ж�ͨ��ΪUSART1
   NVIC_Instructure.NVIC_IRQChannelCmd=ENABLE;//�ж�Ϊ�ڲ�ͨ��
   NVIC_Instructure.NVIC_IRQChannelPreemptionPriority=1;//������ռ���ȼ�
   NVIC_Instructure.NVIC_IRQChannelSubPriority=1;//���ô����ȼ�
   NVIC_Init(&NVIC_Instructure);
   
   USART_Cmd(USART1,ENABLE);//����USART1
 
}

void USART_SendByte(uint16_t Byte)//���͵�һ�ֽ�
{
   USART_SendData(USART1,Byte); //����
   while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//�ȴ�������ɣ���־λΪ0/resetʱ���ڷ��ͣ�
    
}

void USART_SendArray(uint16_t *Array , uint16_t length)//��������
{
    uint16_t i;
    for(i=0;i<length;i++)
    {
      USART_SendByte(Array[i]);  
        
    }
}


void USART_SendString(char*String)//�����ַ���
{
    uint8_t i;
    for(i=0;String[i]!='\0';i++)
    {
      USART_SendByte(String[i]);    
    }
    
}

uint32_t USART_Pow(uint16_t x,uint16_t y)//xΪ������yΪ����(x^y)
{
    uint32_t result=1;
    while(y--)
    {
        result *=x;  
    }
    return result;
}

void USART_SendNumber(uint32_t Number ,uint8_t length)//��������
{
    uint8_t i;
    for(i=0;i<length;i++)
    {
        USART_SendByte((Number/USART_Pow(10,length-i-1))%10+'0'); 

    }

}
//��������
void USART_Printf(char*format ,...)//(...��������)
{
    char String[100]; 
    va_list arg;//��������
    va_start(arg,format);
    vsprintf(String,format,arg);
    va_end(arg);
    USART_SendString(String);
}

uint8_t USART_GetRXFlag(void)//��ȡ���ܱ�־λ������װ
{
    if(USART_RXFlag==1)
    {
        USART_RXFlag=0;//��װ
        return 1;
    }
    return 0;
}

uint8_t USART_GetRXData(void)//��ȡ���յ�������
{
    return USART_RXData;
}

void USART1_IRQHandler(void)
{
   if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET) 
   {
     USART_RXData=USART_ReceiveData(USART1);//�������� 
     USART_RXFlag = 1;//������� 
     USART_ClearITPendingBit(USART1,USART_FLAG_RXNE);//���USART1�ı�־λ
   }
    
    
}


