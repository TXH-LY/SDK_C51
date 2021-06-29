#include "hw_Timer1.h"

#ifdef TIMER1_CONFIG

//#ifndef GTIMER_CONFIG


static u8 timer_h;
static u8 timer_l;

static bit mode_flg = 0;

int (*pointer_interupt_timer1)(void *arg);

static int interupt_timer_function (void *arg) 
{
	void *ptr = arg;
	return 0;
}



/*******************************************************************************
* �� �� ��         : Timer1Init
* ��������		   : ��ʱ��1��ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Timer1Init(uint mode, uint us, void *callback)
{
	switch (mode)
	{
		case TIMER1_MODE_0:TMOD   |= 0X00;
		                   timer_h = (8192-us) / 8;
		                   timer_l = (8192-us) % 8;
		                   break;
		case TIMER1_MODE_1:TMOD   |= 0X10;
		                   timer_h = (65536-us) / 256;
		                   timer_l = (65536-us) % 256;
		                   break;
		case TIMER1_MODE_2:TMOD   |= 0X20;
		                   timer_h = (256-us) % 256;
		                   timer_l = timer_h;
		                   break;
		default:return ;   break;
	}
	
	if (callback == NULL) {
		pointer_interupt_timer1 = interupt_timer_function;
	} else {
		pointer_interupt_timer1 = callback;
	}
	
	TH1   = timer_h;	//����ʱ������ֵ
	TL1   = timer_l;	
	ET1=1;//�򿪶�ʱ��1�ж�����
	EA=1;//�����ж�
	TR1=1;//�򿪶�ʱ��			
}




void Timer1Init_NoOpen(uint mode, uint us, void *callback)
{
	TR1   = 0;//�رն�ʱ��
	ET1   = 0;//�رն�ʱ��1�ж�����
	switch (mode)
	{
		case TIMER1_MODE_0:TMOD   |= 0X00;
		                   timer_h = (8192-us) / 8;
		                   timer_l = (8192-us) % 8;
		                   break;
		case TIMER1_MODE_1:TMOD   |= 0X10;
		                   timer_h = (65536-us) / 256;
		                   timer_l = (65536-us) % 256;
		                   break;
		case TIMER1_MODE_2:TMOD   |= 0X20;
		                   timer_h = (256-us) % 256;
		                   timer_l = timer_h;
		                   mode_flg = 1;
		                   break;
		default:return ;   break;
	}
	
	if (callback == NULL) {
		pointer_interupt_timer1 = interupt_timer_function;
	} else {
		pointer_interupt_timer1 = callback;
	}
	
	TH1   = timer_h;	//����ʱ������ֵ
	TL1   = timer_l;	
	ET1   = 0;//�رն�ʱ��1�ж�����
	EA    = 1;//�����ж�
	TR1   = 0;//�򿪶�ʱ��
}

void Timer1Open(void)
{
	TH1   = timer_h;	//����ʱ������ֵ
	TL1   = timer_l;
	ET1   = 1;//�򿪶�ʱ��0�ж�����
	TR1   = 1;//�򿪶�ʱ��
}

void Timer1Close(void)
{
	TR1   = 0;//�رն�ʱ��
	ET1   = 0;//�رն�ʱ��0�ж�����
	TH1   = timer_h;	//����ʱ������ֵ
	TL1   = timer_l;	
}

void Timer1Pause(void)
{
	TR1   = 0;//�رն�ʱ��
	ET1   = 0;//�رն�ʱ��0�ж�����
}

void Timer1Start(void)
{
	ET1   = 1;//�򿪶�ʱ��0�ж�����
	TR1   = 1;//�򿪶�ʱ��
}





/*******************************************************************************
* �� �� ��         : void Timer1() interrupt 3
* ��������		   : ��ʱ��0�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Timer1() interrupt 3
{
	if (mode_flg == 0) {
		TH1 = timer_h;	//����ʱ������ֵ
		TL1 = timer_l;
	}
	
	pointer_interupt_timer1(NULL);
}



//#endif /* GTIMER_CONFIG */
#endif /* TIMER1_CONFIG */

