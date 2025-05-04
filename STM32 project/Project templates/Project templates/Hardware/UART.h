#ifndef _UART_H_
#define _UART_H_


void UART_Init(void);
void USART_SendByte(uint16_t Byte);
void USART_SendArray(uint16_t *Array , uint16_t length);
void USART_SendString(char*String);
void USART_SendNumber(uint32_t Number ,uint8_t length);
void USART_Printf(char*format ,...);
uint8_t USART_GetRXData(void);
uint8_t USART_GetRXFlag(void);


#endif
