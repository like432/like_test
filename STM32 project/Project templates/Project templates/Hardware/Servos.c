#include "stm32f10x.h"                  // Device header

void Servos_Init(void )
{
   //RCC_APB1PeriphClockCmd 函数用于启用或禁用位于APB1总线上的外设的时钟。APB1（Advanced Peripheral Bus 1）是一个低功耗总线，通常用于连接低速外设
   // RCC_APB2PeriphClockCmd 函数用于启用或禁用位于APB2总线上的外设的时钟。APB2（Advanced Peripheral Bus 2）是一个高性能总线，通常用于连接需要更高时钟频率的外设。
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //初始化时钟RCC_APB1Periph_TIM2，TIM2为通用定时器，开启时钟TIM2的时钟线是APB1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//初始化时钟RCC_APB2Periph_GPIOA，RCC_APB2Periph_GPIOA 是GPIOA端口的时钟
   //初始化引脚
    GPIO_InitTypeDef GPIO_Instructure;//创建结构体
    GPIO_Instructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用输出模式
    GPIO_Instructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_1;//引脚为PA1,PA2和PA0(GPIO_Pin_2 |GPIO_Pin_1可以替换为0x0003)
    GPIO_Instructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Instructure);
   //外部时钟控制
    TIM_InternalClockConfig(TIM2);//使用内部时钟TIM2
  //定时器初始化结构体
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstructure;//创建结构体
   TIM_TimeBaseInitstructure.TIM_ClockDivision=TIM_CKD_DIV1;//TIM_时钟分频系数（TIM_CKD_DIV1是一倍分频系数=不分）
   TIM_TimeBaseInitstructure.TIM_CounterMode=TIM_CounterMode_Up;//TIM_计数模式（TIM_CounterMode_Up是向上计数）
   TIM_TimeBaseInitstructure.TIM_Period=20000-1;//定时器周期（ARR值设定）
   TIM_TimeBaseInitstructure.TIM_Prescaler=72-1;//预分频系数值（PSC值）
   TIM_TimeBaseInitstructure.TIM_RepetitionCounter=0; //重复计时器（高级计数器才有，TIM2无）0表示不使用
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitstructure);
    
   //ARR为20000 
   //RCC/ARR(0.5/20->2.5/20)
   //RCC(500->2500) ，舵机从 -90°->  90°（0°-> 180°）
   
   //设置定时器为PWM输出模式
   TIM_OCInitTypeDef TIM_OCInitstructure;//对OC功能进行设置
   TIM_OCStructInit(&TIM_OCInitstructure);//对结构体初始化，目的是为了初始化初始比较器的一个变量
   TIM_OCInitstructure.TIM_OCMode=TIM_OCMode_PWM1;//指定TIM模式为PWM1模式
   TIM_OCInitstructure.TIM_OCPolarity=TIM_OCPolarity_High;//输出比较的极性，输出极性，选择为高
   TIM_OCInitstructure.TIM_OutputState=TIM_OutputState_Enable;//指定TIM输出比较状态，定时器输出比较单元的极性 就是输出
   TIM_OCInitstructure.TIM_Pulse=0;//(ARR开始输出值)指定要加载到捕获比较寄存器中的脉冲值
   //初始化定时器通道
   TIM_OC1Init(TIM2,&TIM_OCInitstructure);//初始化TIM2的CH1(1通道)
   TIM_OC2Init(TIM2,&TIM_OCInitstructure);//初始化TIM2的CH2(2通道)
   TIM_OC3Init(TIM2,&TIM_OCInitstructure);//初始化TIM2的CH3(3通道)
   
   //起振定时器
   TIM_Cmd(TIM2,ENABLE);//启动TIM2
}

//输出过程中动态改变CCR值，进而改变占空比

void wind_set(uint8_t time)//操作风扇
{
    TIM_SetCompare1(TIM2,time*200);//初始化舵机1
}

void Servos1_set(uint8_t time)//操作舵机1
{
    TIM_SetCompare2(TIM2,500+time*(2000/180));//初始化舵机1
}

void Servos2_set(uint8_t time)//操作舵机2
{
    TIM_SetCompare3(TIM2,500+time*(2000/180));//初始化舵机2
}









