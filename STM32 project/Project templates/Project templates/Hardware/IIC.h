#ifndef _IIC_H
#define _IIC_H

void IIC_Init(void);                //���ų�ʼ��
void IIC_Start(void);               //��ʼ�ź�
void IIC_Stop(void);                //��ֹ�ź�
void  IIC_SendByte(uint8_t Byte);       //��������
uint8_t IIC_ReceiveByte(void );     //��������
void IIC_SendACK(uint8_t ACKBit);   //дӦ��
uint8_t IIC_RceiveACK(void );       //��Ӧ��

#endif
