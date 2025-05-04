#include <REGX52.H>
#include "Delay.h"

/**
  * 简介      @brief  获取按键键码
  * 参数      @param  无
  * 返回值    @retval 按下按键时获取对应键码值，没按下时返回0，范围是0-4
  */

unsigned char Key()
{
	unsigned int KeyNumber=0;
	
	if(P3_1==0){Delay(20);while(P3_1==0);Delay(20);KeyNumber=1;}
	if(P3_0==0){Delay(20);while(P3_0==0);Delay(20);KeyNumber=2;}
	if(P3_2==0){Delay(20);while(P3_2==0);Delay(20);KeyNumber=3;}
	if(P3_3==0){Delay(20);while(P3_3==0);Delay(20);KeyNumber=4;}
	
	return KeyNumber;
}