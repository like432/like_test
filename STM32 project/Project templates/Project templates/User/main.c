#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "UART.h"
#include "SPI.h"



int main()
{
    uint8_t RxData;
    UART_Init();
    OLED_Init();
   while(1)
   { 
    if(USART_GetRXFlag()==1)
    {
        RxData=USART_GetRXData();
        USART_SendByte(RxData);
        OLED_ShowHexNum(1,4,RxData,2);
        OLED_ShowNum(2,4,RxData,2);
        OLED_ShowChar(3,1,RxData+55);
    }        
       
   }
   
}



