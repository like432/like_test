#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"
#include "IIC.h"

//需要在主函数中表示 uint16_t AX,AY,AZ,GX,GY,GZ;

#define    MPU6050_ADDRESS 0XD0

void MPU6050_W_REG(uint8_t REG_ADDRESS,uint8_t DATA)//MPU6050发送数据数据
{
    IIC_Start();//开始iic协议
    IIC_SendByte(MPU6050_ADDRESS);//发送模块地址
    IIC_RceiveACK();//应答
    IIC_SendByte(REG_ADDRESS);//发送寄存器地址
    IIC_RceiveACK();//应答
    IIC_SendByte(DATA);//发送数据
    IIC_RceiveACK();//应答
    IIC_Stop();//结束iic协议
}

uint8_t MPU6050_R_REG(uint8_t REG_ADDRESS)//MPU6050读取数据
{
    //确定寄存器位置
   uint8_t DATA;//创建数据变量 
   IIC_Start();//开始iic协议
   IIC_SendByte(MPU6050_ADDRESS);//发送模块地址 
   IIC_RceiveACK();//应答 
   IIC_SendByte(REG_ADDRESS);//发送寄存器地址
   IIC_RceiveACK();//应答
    
    //开始读取数据
   IIC_Start();//开始iic协议
   IIC_SendByte(MPU6050_ADDRESS | 0x01);// 告诉MPU6050开始读取数据
   IIC_RceiveACK();//应答  
   DATA=IIC_ReceiveByte();//将接受数据赋值给DATA
   IIC_SendACK(0);//从机向主机发送应答，0为应答，1为非应答
   IIC_Stop();//结束iic协议
   return DATA;
}

void MPU6050_Init(void)//初始化MPU6050
{
  IIC_Init();//初始化协议  
  MPU6050_W_REG(MPU6050_PWR_MGMT_1,0X01);//电源管理 1(参数查看寄存器手册得出)
  MPU6050_W_REG(MPU6050_PWR_MGMT_2,0X00);//电源管理 2  
  MPU6050_W_REG(MPU6050_SMPLRT_DIV,0x09); //采样率分频器(10分频方便计算) 
  MPU6050_W_REG(MPU6050_CONFIG,0x06);//设置配置 采用常用滤波频率
  MPU6050_W_REG(MPU6050_GYRO_CONFIG,0x18);//陀螺仪配置（角度计配置）(关闭自测，量程最大)
  MPU6050_W_REG(MPU6050_ACCEL_CONFIG,0x18);// 加速度计配置 (关闭自测，量程最大)
    
}

void MPU6050_GetData(uint16_t *ACCELX,uint16_t *ACCELY,uint16_t *ACCELZ,
                     uint16_t *GYROX, uint16_t *GYROY, uint16_t *GYROZ)
{    
     uint8_t DATAH,DATAL;//创建高低位变量
     DATAH=MPU6050_R_REG(MPU6050_ACCEL_XOUT_H);//读取AX的高位地址
     DATAL=MPU6050_R_REG(MPU6050_ACCEL_XOUT_L);//读取AX的低位地址
     *ACCELX=(DATAH << 8)| DATAL;//C语言将自动数据转为十进制数呈现
     
     DATAH=MPU6050_R_REG(MPU6050_ACCEL_YOUT_H);//读取AY的高位地址
     DATAL=MPU6050_R_REG(MPU6050_ACCEL_YOUT_L);//读取AY的低位地址
     *ACCELY=(DATAH << 8)| DATAL;//C语言将自动数据转为十进制数呈现
    
     DATAH=MPU6050_R_REG(MPU6050_ACCEL_ZOUT_H);//读取AZ的高位地址
     DATAL=MPU6050_R_REG(MPU6050_ACCEL_ZOUT_L);//读取AZ的低位地址
     *ACCELZ=(DATAH << 8)| DATAL;//C语言将自动数据转为十进制数呈现
    
    DATAH=MPU6050_R_REG(MPU6050_GYRO_XOUT_H	);//读取GX的高位地址
     DATAL=MPU6050_R_REG(MPU6050_GYRO_XOUT_L);//读取GX的低位地址
     *GYROX=(DATAH << 8)| DATAL;//C语言将自动数据转为十进制数呈现
     
     DATAH=MPU6050_R_REG(MPU6050_GYRO_YOUT_H);//读取GY的高位地址
     DATAL=MPU6050_R_REG(MPU6050_GYRO_YOUT_L);//读取GY的低位地址
     *GYROY=(DATAH << 8)| DATAL;//C语言将自动数据转为十进制数呈现
    
     DATAH=MPU6050_R_REG(MPU6050_GYRO_ZOUT_H);//读取GZ的高位地址
     DATAL=MPU6050_R_REG(MPU6050_GYRO_ZOUT_L);//读取GZ的低位地址
     *GYROZ=(DATAH << 8)| DATAL;//C语言将自动数据转为十进制数呈现
    
    
}





