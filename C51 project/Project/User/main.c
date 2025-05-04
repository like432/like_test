#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include "LCD1602.h"

unsigned char Hour,Min,Sec;

void main()
{
	LCD_Init();
	Timer0Init();
	LCD_ShowString(1,1,"CLOCK:");
	LCD_ShowString(2,3,":");
	LCD_ShowString(2,6,":");
	while(1)
	{	
		LCD_ShowNum(2,1,Hour,2);
		LCD_ShowNum(2,4,Min,2);
		LCD_ShowNum(2,7,Sec,2);
	}

}



void Timer0_Routine() interrupt 1		//��ִ���жϳ���ʱ������ú���
{
	static unsigned int T0Count;
	TL0 = 0x18;			//���ö�ʱ��ֵ�����õ�4λ
	TH0 = 0xFC;			//���ö�ʱ��ֵ�����ø�4λ
	T0Count++;
	if(T0Count>=1000)	  //��ʱʱ���Ϊ1S
	{
		T0Count=0;		//���¿�ʼ��ʱ
		Sec++;
		if(Sec>=60)
		{
			Min++;
			Sec=0;
			if(Min>=60)
			{
				Min=0;
				Hour++;
			}

		}
			
		
	}
}
