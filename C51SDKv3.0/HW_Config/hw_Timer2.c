#include "hw_Timer2.h"

#ifdef TIMER2_CONFIG


static u8 timer_h;
static u8 timer_l;

static bit mode_flg = 0;

int (*pointer_interupt_timer2)(void *arg);

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
void Timer2Init(uint mode, uint us, void *callback)
{
	switch (mode)
	{
		case TIMER2_MODE_CAPTURE:T2CON=0X09;  //����T2Ϊ����ģʽ���½���������ж�
		                         timer_h = (65536-us) / 256;
		                         timer_l = (65536-us) % 256;
		                         break;
		case TIMER2_MODE_TIMING :T2CON=0X00;  //����T2Ϊ����ģʽ���½���������ж�
		                         timer_h = (65536-us) / 256;
		                         timer_l = (65536-us) % 256;
		                         break;
		default:                 return ;
                                 break;
	}
	
	if (callback == NULL) {
		pointer_interupt_timer2 = interupt_timer_function;
	} else {
		pointer_interupt_timer2 = callback;
	}
	
	RCAP2H = timer_h;
	RCAP2L = timer_l;
	TH2 = RCAP2H;
	TL2 = RCAP2L;
	
	EA  = 1;
	
	TR2 = 1;
	ET2 = 1;
}




void Timer2Init_NoOpen(uint mode, uint us, void *callback)
{
	TR2   = 0;//�رն�ʱ��
	ET2   = 0;//�رն�ʱ��1�ж�����
	switch (mode)
	{
		case TIMER2_MODE_CAPTURE:T2CON=0X09;  //����T2Ϊ����ģʽ���½���������ж�
		                         timer_h = (65536-us) / 256;
		                         timer_l = (65536-us) % 256;
		                         break;
		case TIMER2_MODE_TIMING :T2CON=0X00;  //����T2Ϊ
		                         timer_h = (65536-us) / 256;
		                         timer_l = (65536-us) % 256;
		                         break;
		default:                 return ;
                                 break;
	}
	
	if (callback == NULL) {
		pointer_interupt_timer2 = interupt_timer_function;
	} else {
		pointer_interupt_timer2 = callback;
	}
	
	RCAP2H = timer_h;
	RCAP2L = timer_l;
	TH2 = RCAP2H;
	TL2 = RCAP2L;
	
	TR2 = 0;
	ET2 = 0;
	
	EA  = 1;
}

void Timer2Open(void)
{
	ET2   = 1;//�򿪶�ʱ��0�ж�����
	TR2   = 1;//�򿪶�ʱ��
}

void Timer2Close(void)
{
	TR2   = 0;//�رն�ʱ��
	ET2   = 0;//�رն�ʱ��0�ж�����
}

void Timer2Pause(void)
{
	TR2   = 0;//�رն�ʱ��
}

void Timer2Start(void)
{
	TR2   = 1;//�򿪶�ʱ��
}





/*******************************************************************************
* �� �� ��         : void Timer2() interrupt 5
* ��������		   : ��ʱ��0�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void Timer2() interrupt 5
{
	TF2   = 0;
	
	pointer_interupt_timer2(NULL);
	
}
#endif /* TIMER2_CONFIG */

