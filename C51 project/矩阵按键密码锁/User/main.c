#include <REGX52.H>
#include "MatrixKey.h"
#include "LCD1602.h"

unsigned char KeyNum;
unsigned int PassWord,Count;

void main()
{
	
	LCD_Init();
	LCD_ShowString(1,1,"PassWord");
	while(1)
	{
		KeyNum=MatrixKey();
		if(KeyNum)               		 	//判断是否按下
		{
			if(KeyNum<=10)        			//规定密码按键区域（S1-S10）
			{
				if(Count<4)      		 	//保证四维密码
				{
					PassWord*=10;    		 	//密码左移一位（0001->0010）
					PassWord+=KeyNum%10 ;   	//保证密码从0-9,同时增加下一位密码
					Count++;
				}
				LCD_ShowNum(2,1,PassWord,4);	//更新显示
					
			}
			if(KeyNum==11)						//确认键
			{
					if(PassWord==1122)			//如果输入密码为正确密码
					{
						LCD_ShowString(1,14,"OK ");//输出OK
					}
					else						//否则
					{
						LCD_ShowString(1,14,"ERR");//输出ERR
						PassWord=0;
						Count=0;
						LCD_ShowNum(2,1,PassWord,4);
					}
			}
			if(KeyNum==12)						//清零键
			{
				LCD_ShowString(1,14,"CLE");
				PassWord=0;
				Count=0;
				LCD_ShowNum(2,1,PassWord,4);
			}
		}
		
		
	}
	
	
	
	
	
	
}