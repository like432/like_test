#include "stm32f10x.h"                  // Device header


#define CLK  GPIO_Pin_5//ʱ����
#define MOSI GPIO_Pin_7//�������/�ӻ�����
#define MISO GPIO_Pin_6//�ӻ����/��������
#define SS   GPIO_Pin_4//Ƭѡ��

#define SPI1_W_SS(x)		GPIO_WriteBit(GPIOA, SS, (BitAction)(x))


void SPI1_Init(void)
{
    //����ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
    //��������
    GPIO_InitTypeDef GPIO_Instructure;//�����ṹ��
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_Out_PP;//�������ģʽ
    GPIO_Instructure.GPIO_Pin=SS;
    GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Instructure);//��ʼ��SS
    
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_AF_PP;//�����������ģʽ
    GPIO_Instructure.GPIO_Pin=CLK | MOSI;
    GPIO_Init(GPIOA,&GPIO_Instructure);//��ʼ��CLK �� MOSI
    
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_IPU;//��������ģʽ
    GPIO_Instructure.GPIO_Pin=MISO;
    GPIO_Init(GPIOA,&GPIO_Instructure);//��ʼ��MISO
    
    SPI_InitTypeDef SPI_Instructure;//�����ṹ��
    SPI_Instructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_128;//ָ��������Ԥ��Ƶ����(ֵԽ��Ƶ��Խ��)
    SPI_Instructure.SPI_CPHA=SPI_CPHA_1Edge;//ָ��λ����ʱ����Ϊ��һ��Ե��������
    SPI_Instructure.SPI_CPOL=SPI_CPOL_Low;//���ÿ���ʱ��SCK������״̬Ϊ�͵�ƽ
    SPI_Instructure.SPI_CRCPolynomial=7;//����CRC����ʽУ��ֵ Ĭ��ֵΪ7
    SPI_Instructure.SPI_DataSize=SPI_DataSize_8b;//��������֡Ϊ8Ϊ����֡
    SPI_Instructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;//����ģʽѡ��ѡ��Ϊȫ˫��ģʽ
    SPI_Instructure.SPI_FirstBit=SPI_FirstBit_MSB;//ѡ����������λΪ��λ����
    SPI_Instructure.SPI_Mode=SPI_Mode_Master;//����ģʽѡ��ѡ��Ϊ����
    SPI_Instructure.SPI_NSS=SPI_NSS_Soft ;//����NSS������ʽΪ�������
    SPI_Init(SPI1,&SPI_Instructure);
    
    SPI_Cmd(SPI1,ENABLE);

    SPI1_W_SS(1);//��ѡ��ģ��
}

void SPI1_Start(void)
{
    SPI1_W_SS(0);
}

void SPI1_Stop(void)
{
    SPI1_W_SS(1);
}

uint8_t SPI1_SendByte(uint8_t ByteSend)//SPI����һ���ֽ�����
{
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)!=SET);//�ȴ���һ���ڷ������
    SPI_I2S_SendData(SPI1,ByteSend);
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)!=SET);//�ȴ���һ���ڽ������ 
    return SPI_I2S_ReceiveData(SPI1);
}





