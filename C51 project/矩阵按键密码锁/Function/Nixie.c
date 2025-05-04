#include <REGX52.H>
#include "Delay.h"

unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00,0xCF};

//  0     1     2     3     4     5     6     7     8     9    
//0x3F  0x06  0x5B   0x4F  0x66  0x6D  0x7D  0x07  0x7F  0x6F 
// A(10)  b(11)   C(12)     D(13)    E(14)     F(15)     ��(16)
// 0x77   0x7C    0x39      0x5E      0x79      0x71     0x00 



void Nixie(unsigned char Location,Number)
{
	switch(Location)//(Ƭѡ)ѡ�������λ�ã�ʵ�壺�����ң�
	{
		//P2_4��ʾ138�������ϵ�C(��)  P2_3 B���У� P2_2 A���ͣ�
		case 1 : P2_4=1,P2_3=1,P2_2=1;break;//�����
		case 2 : P2_4=1,P2_3=1,P2_2=0;break;
		case 3 : P2_4=1,P2_3=0,P2_2=1;break;
		case 4 : P2_4=1,P2_3=0,P2_2=0;break;
		case 5 : P2_4=0,P2_3=1,P2_2=1;break;
		case 6 : P2_4=0,P2_3=1,P2_2=0;break;
		case 7 : P2_4=0,P2_3=0,P2_2=1;break;
		case 8 : P2_4=0,P2_3=0,P2_2=0;break;//���ұ�
	}
	//����ѡ��ѡ������ַ�
	P0=NixieTable[Number];
	Delay(1);//ʹ��ʾ�ȶ�
	P0=0x00;//��Ӱ
}
