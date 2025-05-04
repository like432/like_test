#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"
#include "IIC.h"

//��Ҫ���������б�ʾ uint16_t AX,AY,AZ,GX,GY,GZ;

#define    MPU6050_ADDRESS 0XD0

void MPU6050_W_REG(uint8_t REG_ADDRESS,uint8_t DATA)//MPU6050������������
{
    IIC_Start();//��ʼiicЭ��
    IIC_SendByte(MPU6050_ADDRESS);//����ģ���ַ
    IIC_RceiveACK();//Ӧ��
    IIC_SendByte(REG_ADDRESS);//���ͼĴ�����ַ
    IIC_RceiveACK();//Ӧ��
    IIC_SendByte(DATA);//��������
    IIC_RceiveACK();//Ӧ��
    IIC_Stop();//����iicЭ��
}

uint8_t MPU6050_R_REG(uint8_t REG_ADDRESS)//MPU6050��ȡ����
{
    //ȷ���Ĵ���λ��
   uint8_t DATA;//�������ݱ��� 
   IIC_Start();//��ʼiicЭ��
   IIC_SendByte(MPU6050_ADDRESS);//����ģ���ַ 
   IIC_RceiveACK();//Ӧ�� 
   IIC_SendByte(REG_ADDRESS);//���ͼĴ�����ַ
   IIC_RceiveACK();//Ӧ��
    
    //��ʼ��ȡ����
   IIC_Start();//��ʼiicЭ��
   IIC_SendByte(MPU6050_ADDRESS | 0x01);// ����MPU6050��ʼ��ȡ����
   IIC_RceiveACK();//Ӧ��  
   DATA=IIC_ReceiveByte();//���������ݸ�ֵ��DATA
   IIC_SendACK(0);//�ӻ�����������Ӧ��0ΪӦ��1Ϊ��Ӧ��
   IIC_Stop();//����iicЭ��
   return DATA;
}

void MPU6050_Init(void)//��ʼ��MPU6050
{
  IIC_Init();//��ʼ��Э��  
  MPU6050_W_REG(MPU6050_PWR_MGMT_1,0X01);//��Դ���� 1(�����鿴�Ĵ����ֲ�ó�)
  MPU6050_W_REG(MPU6050_PWR_MGMT_2,0X00);//��Դ���� 2  
  MPU6050_W_REG(MPU6050_SMPLRT_DIV,0x09); //�����ʷ�Ƶ��(10��Ƶ�������) 
  MPU6050_W_REG(MPU6050_CONFIG,0x06);//�������� ���ó����˲�Ƶ��
  MPU6050_W_REG(MPU6050_GYRO_CONFIG,0x18);//���������ã��Ƕȼ����ã�(�ر��Բ⣬�������)
  MPU6050_W_REG(MPU6050_ACCEL_CONFIG,0x18);// ���ٶȼ����� (�ر��Բ⣬�������)
    
}

void MPU6050_GetData(uint16_t *ACCELX,uint16_t *ACCELY,uint16_t *ACCELZ,
                     uint16_t *GYROX, uint16_t *GYROY, uint16_t *GYROZ)
{    
     uint8_t DATAH,DATAL;//�����ߵ�λ����
     DATAH=MPU6050_R_REG(MPU6050_ACCEL_XOUT_H);//��ȡAX�ĸ�λ��ַ
     DATAL=MPU6050_R_REG(MPU6050_ACCEL_XOUT_L);//��ȡAX�ĵ�λ��ַ
     *ACCELX=(DATAH << 8)| DATAL;//C���Խ��Զ�����תΪʮ����������
     
     DATAH=MPU6050_R_REG(MPU6050_ACCEL_YOUT_H);//��ȡAY�ĸ�λ��ַ
     DATAL=MPU6050_R_REG(MPU6050_ACCEL_YOUT_L);//��ȡAY�ĵ�λ��ַ
     *ACCELY=(DATAH << 8)| DATAL;//C���Խ��Զ�����תΪʮ����������
    
     DATAH=MPU6050_R_REG(MPU6050_ACCEL_ZOUT_H);//��ȡAZ�ĸ�λ��ַ
     DATAL=MPU6050_R_REG(MPU6050_ACCEL_ZOUT_L);//��ȡAZ�ĵ�λ��ַ
     *ACCELZ=(DATAH << 8)| DATAL;//C���Խ��Զ�����תΪʮ����������
    
    DATAH=MPU6050_R_REG(MPU6050_GYRO_XOUT_H	);//��ȡGX�ĸ�λ��ַ
     DATAL=MPU6050_R_REG(MPU6050_GYRO_XOUT_L);//��ȡGX�ĵ�λ��ַ
     *GYROX=(DATAH << 8)| DATAL;//C���Խ��Զ�����תΪʮ����������
     
     DATAH=MPU6050_R_REG(MPU6050_GYRO_YOUT_H);//��ȡGY�ĸ�λ��ַ
     DATAL=MPU6050_R_REG(MPU6050_GYRO_YOUT_L);//��ȡGY�ĵ�λ��ַ
     *GYROY=(DATAH << 8)| DATAL;//C���Խ��Զ�����תΪʮ����������
    
     DATAH=MPU6050_R_REG(MPU6050_GYRO_ZOUT_H);//��ȡGZ�ĸ�λ��ַ
     DATAL=MPU6050_R_REG(MPU6050_GYRO_ZOUT_L);//��ȡGZ�ĵ�λ��ַ
     *GYROZ=(DATAH << 8)| DATAL;//C���Խ��Զ�����תΪʮ����������
    
    
}





