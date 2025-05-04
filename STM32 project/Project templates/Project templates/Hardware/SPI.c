#include "stm32f10x.h"                  // Device header


#define CLK  GPIO_Pin_5//时钟线
#define MOSI GPIO_Pin_7//主机输出/从机接收
#define MISO GPIO_Pin_6//从机输出/主机接收
#define SS   GPIO_Pin_4//片选线

#define SPI1_W_SS(x)		GPIO_WriteBit(GPIOA, SS, (BitAction)(x))


void SPI1_Init(void)
{
    //开启时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
    //配置引脚
    GPIO_InitTypeDef GPIO_Instructure;//创建结构体
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出模式
    GPIO_Instructure.GPIO_Pin=SS;
    GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Instructure);//初始化SS
    
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出模式
    GPIO_Instructure.GPIO_Pin=CLK | MOSI;
    GPIO_Init(GPIOA,&GPIO_Instructure);//初始化CLK 和 MOSI
    
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入模式
    GPIO_Instructure.GPIO_Pin=MISO;
    GPIO_Init(GPIOA,&GPIO_Instructure);//初始化MISO
    
    SPI_InitTypeDef SPI_Instructure;//创建结构体
    SPI_Instructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_128;//指定波特率预分频计数(值越大频率越低)
    SPI_Instructure.SPI_CPHA=SPI_CPHA_1Edge;//指定位捕获时钟沿为第一边缘即上升沿
    SPI_Instructure.SPI_CPOL=SPI_CPOL_Low;//设置空闲时间SCK的引脚状态为低电平
    SPI_Instructure.SPI_CRCPolynomial=7;//设置CRC多项式校验值 默认值为7
    SPI_Instructure.SPI_DataSize=SPI_DataSize_8b;//设置数据帧为8为数据帧
    SPI_Instructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;//传输模式选择，选择为全双工模式
    SPI_Instructure.SPI_FirstBit=SPI_FirstBit_MSB;//选择数据先行位为高位先行
    SPI_Instructure.SPI_Mode=SPI_Mode_Master;//主从模式选择，选择为主机
    SPI_Instructure.SPI_NSS=SPI_NSS_Soft ;//设置NSS触发方式为软件触发
    SPI_Init(SPI1,&SPI_Instructure);
    
    SPI_Cmd(SPI1,ENABLE);

    SPI1_W_SS(1);//不选择模块
}

void SPI1_Start(void)
{
    SPI1_W_SS(0);
}

void SPI1_Stop(void)
{
    SPI1_W_SS(1);
}

uint8_t SPI1_SendByte(uint8_t ByteSend)//SPI交换一个字节数据
{
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE)!=SET);//等待上一周期发送完成
    SPI_I2S_SendData(SPI1,ByteSend);
    while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE)!=SET);//等待上一周期接收完成 
    return SPI_I2S_ReceiveData(SPI1);
}





