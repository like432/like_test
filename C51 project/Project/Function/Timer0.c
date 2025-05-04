#include <REGX52.H>

/**
  * 简介    @brief  定时器0初始化，1s，12MHz
  * 参数    @param  无
  * 返回值  @retval 无  
  */

void Timer0Init(void)		
{
	TMOD &= 0xF0;		//设置定时器模式，将寄存器的低四位清零，高四位不变
	TMOD |= 0x01;		//设置定时器模式，将寄存器的最低位清零，高四位不变
	TL0 = 0x18;			//设置定时初值，设置低4位
	TH0 = 0xFC;			//设置定时初值，设置高4位
	TF0 = 0;			//清除TF0标志
	TR0 = 1;			//定时器0开始计时
	ET0=1;              //中断允许控制寄存器
	EA=1;               //中断允许控制寄存器
	PT0=0;              //选择中断控制寄存器优先级
}


//定时器中断函数模板

//void Timer0_Routine() interrupt 1		//当执行中断程序时，跳入该函数
//{
//	static unsigned int T0Count;
//	TL0 = 0x18;			//设置定时初值，设置低4位
//	TH0 = 0xFC;			//设置定时初值，设置高4位
//	T0Count++;
//	if(T0Count>=1000)	  //计时时间记为1S
//	{
//		T0Count=0;		  //重新开始计时
		
//	}
//}







