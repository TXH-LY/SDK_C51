#include "independent_key_4.h"

#ifdef KEY4X4_CONFIG



static void __key_delay_ms (uint ms)
{
	uint i = 0;
	while (ms > 0){
		for (i = 0; i < 110; i++);
		ms--;
	}
}


/*******************************************************************************
* �� �� ��         : KeyDown
* ��������		   : ����а������²���ȡ��ֵ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
u8 KeyDown(void)
{
	u8    KeyValue = 17;
	
	GPIO_KEY=0xF0;
	if(GPIO_KEY!=0xF0)
  {
		__key_delay_ms(20);
		if(GPIO_KEY!=0x0f)
		{
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0XE0):	KeyValue=0;break;
				case(0XD0):	KeyValue=1;break;
				case(0XB0): KeyValue=2;break;
				case(0X70):	KeyValue=3;break;
				default:	KeyValue=17;
			}
			//������
			GPIO_KEY=0X0F;
			__key_delay_ms(20);
			switch(GPIO_KEY)
			{
				case(0X0E):	KeyValue=KeyValue;   break;
				case(0X0D):	KeyValue=KeyValue+4; break;
				case(0X0B): KeyValue=KeyValue+8; break;
				case(0X07):	KeyValue=KeyValue+12;break;
				default:	KeyValue=17;
			}
			while(GPIO_KEY != 0x0f)	 //�������ּ��
			{
				__key_delay_ms(10);
			}
		}
	}
	
	return KeyValue;
}

#endif /* KEY4X4_CONFIG */