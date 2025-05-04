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
		if(KeyNum)               		 	//�ж��Ƿ���
		{
			if(KeyNum<=10)        			//�涨���밴������S1-S10��
			{
				if(Count<4)      		 	//��֤��ά����
				{
					PassWord*=10;    		 	//��������һλ��0001->0010��
					PassWord+=KeyNum%10 ;   	//��֤�����0-9,ͬʱ������һλ����
					Count++;
				}
				LCD_ShowNum(2,1,PassWord,4);	//������ʾ
					
			}
			if(KeyNum==11)						//ȷ�ϼ�
			{
					if(PassWord==1122)			//�����������Ϊ��ȷ����
					{
						LCD_ShowString(1,14,"OK ");//���OK
					}
					else						//����
					{
						LCD_ShowString(1,14,"ERR");//���ERR
						PassWord=0;
						Count=0;
						LCD_ShowNum(2,1,PassWord,4);
					}
			}
			if(KeyNum==12)						//�����
			{
				LCD_ShowString(1,14,"CLE");
				PassWord=0;
				Count=0;
				LCD_ShowNum(2,1,PassWord,4);
			}
		}
		
		
	}
	
	
	
	
	
	
}