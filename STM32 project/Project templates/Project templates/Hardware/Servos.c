#include "stm32f10x.h"                  // Device header

void Servos_Init(void )
{
   //RCC_APB1PeriphClockCmd �����������û����λ��APB1�����ϵ������ʱ�ӡ�APB1��Advanced Peripheral Bus 1����һ���͹������ߣ�ͨ���������ӵ�������
   // RCC_APB2PeriphClockCmd �����������û����λ��APB2�����ϵ������ʱ�ӡ�APB2��Advanced Peripheral Bus 2����һ�����������ߣ�ͨ������������Ҫ����ʱ��Ƶ�ʵ����衣
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //��ʼ��ʱ��RCC_APB1Periph_TIM2��TIM2Ϊͨ�ö�ʱ��������ʱ��TIM2��ʱ������APB1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//��ʼ��ʱ��RCC_APB2Periph_GPIOA��RCC_APB2Periph_GPIOA ��GPIOA�˿ڵ�ʱ��
   //��ʼ������
    GPIO_InitTypeDef GPIO_Instructure;//�����ṹ��
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_AF_PP;//�������ģʽ
    GPIO_Instructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_1;//����ΪPA1,PA2��PA0(GPIO_Pin_2 |GPIO_Pin_1�����滻Ϊ0x0003)
    GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Instructure);
   //�ⲿʱ�ӿ���
    TIM_InternalClockConfig(TIM2);//ʹ���ڲ�ʱ��TIM2
  //��ʱ����ʼ���ṹ��
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstructure;//�����ṹ��
   TIM_TimeBaseInitstructure.TIM_ClockDivision=TIM_CKD_DIV1;//TIM_ʱ�ӷ�Ƶϵ����TIM_CKD_DIV1��һ����Ƶϵ��=���֣�
   TIM_TimeBaseInitstructure.TIM_CounterMode=TIM_CounterMode_Up;//TIM_����ģʽ��TIM_CounterMode_Up�����ϼ�����
   TIM_TimeBaseInitstructure.TIM_Period=20000-1;//��ʱ�����ڣ�ARRֵ�趨��
   TIM_TimeBaseInitstructure.TIM_Prescaler=72-1;//Ԥ��Ƶϵ��ֵ��PSCֵ��
   TIM_TimeBaseInitstructure.TIM_RepetitionCounter=0; //�ظ���ʱ�����߼����������У�TIM2�ޣ�0��ʾ��ʹ��
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitstructure);
    
   //ARRΪ20000 
   //RCC/ARR(0.5/20->2.5/20)
   //RCC(500->2500) ������� -90��->  90�㣨0��-> 180�㣩
   
   //���ö�ʱ��ΪPWM���ģʽ
   TIM_OCInitTypeDef TIM_OCInitstructure;//��OC���ܽ�������
   TIM_OCStructInit(&TIM_OCInitstructure);//�Խṹ���ʼ����Ŀ����Ϊ�˳�ʼ����ʼ�Ƚ�����һ������
   TIM_OCInitstructure.TIM_OCMode=TIM_OCMode_PWM1;//ָ��TIMģʽΪPWM1ģʽ
   TIM_OCInitstructure.TIM_OCPolarity=TIM_OCPolarity_High;//����Ƚϵļ��ԣ�������ԣ�ѡ��Ϊ��
   TIM_OCInitstructure.TIM_OutputState=TIM_OutputState_Enable;//ָ��TIM����Ƚ�״̬����ʱ������Ƚϵ�Ԫ�ļ��� �������
   TIM_OCInitstructure.TIM_Pulse=0;//(ARR��ʼ���ֵ)ָ��Ҫ���ص�����ȽϼĴ����е�����ֵ
   //��ʼ����ʱ��ͨ��
   TIM_OC1Init(TIM2,&TIM_OCInitstructure);//��ʼ��TIM2��CH1(1ͨ��)
   TIM_OC2Init(TIM2,&TIM_OCInitstructure);//��ʼ��TIM2��CH2(2ͨ��)
   TIM_OC3Init(TIM2,&TIM_OCInitstructure);//��ʼ��TIM2��CH3(3ͨ��)
   
   //����ʱ��
   TIM_Cmd(TIM2,ENABLE);//����TIM2
}

//��������ж�̬�ı�CCRֵ�������ı�ռ�ձ�

void wind_set(uint8_t time)//��������
{
    TIM_SetCompare1(TIM2,time*200);//��ʼ�����1
}

void Servos1_set(uint8_t time)//�������1
{
    TIM_SetCompare2(TIM2,500+time*(2000/180));//��ʼ�����1
}

void Servos2_set(uint8_t time)//�������2
{
    TIM_SetCompare3(TIM2,500+time*(2000/180));//��ʼ�����2
}









