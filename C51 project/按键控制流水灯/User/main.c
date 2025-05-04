#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include <INTRINS.H>

unsigned char KeyNum,LEDMode;

void main()
{
	P2=0xFE;				            //使P2_0亮
	Timer0Init();
	while(1)
	{	
		KeyNum=Key();		 
		if(KeyNum)			             //判断是否按下
		{
			if(KeyNum==1)
			{
				LEDMode++;
				if(LEDMode>=2)LEDMode=0;  //设置模式
			}
			
			
		}
		
	}

}



void Timer0_Routine() interrupt 1		//当执行中断程序时，跳入该函数
{
	static unsigned int T0Count;
	TL0 = 0x18;			//设置定时初值，设置低4位
	TH0 = 0xFC;			//设置定时初值，设置高4位
	T0Count++;
	if(T0Count>=500)	  //计时时间记为1S
	{
		T0Count=0;		  //重新开始计时
		if(LEDMode==0)
		{
			P2=_crol_(P2,1);//_crol_（）函数的作用是向左循环移位，当到达最大时变成最小
			
		}
		if(LEDMode==1)
		{
			P2=_cror_(P2,1);//_crol_（）函数的作用是向右循环移位，当到达最小时变成最大
			
		}
	}
}
