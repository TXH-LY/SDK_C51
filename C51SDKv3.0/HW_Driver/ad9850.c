#include "ad9850.h"

#ifdef AD9850_CONFIG




void ad9850_reset_serial()
{
	AD9850_CLK=0;
	AD9850_UD=0;
	//rest�ź�
	AD9850_REST=0;
	AD9850_REST=1;
	AD9850_REST=0;
	//w_clk�ź�
	AD9850_CLK=0;
	AD9850_CLK=1;
	AD9850_CLK=0;
	//fq_up�ź�
	AD9850_UD=0;
	AD9850_UD=1;
	AD9850_UD=0;
}

void ad9850_wr_serial(unsigned char w0,double frequence)
{
	unsigned char i,w;
	long int y;
	double x;
	//����Ƶ�ʵ�HEXֵ
	x=4294967295/125;//�ʺ�125M����
	//���ʱ��Ƶ�ʲ�Ϊ180MHZ���޸ĸô���Ƶ��ֵ����λMHz  ������
	frequence=frequence/1000000;
	frequence=frequence*x;
	y=frequence;
	//дw4����
	w=(y>>=0);
	for(i=0;i<8;i++)
	{
		AD9850_DATA=(w>>i)&0x01;
		AD9850_CLK=1;
		AD9850_CLK=0;
	}
	//дw3����
	w=(y>>8);
	for(i=0;i<8;i++)
	{
		AD9850_DATA=(w>>i)&0x01;
		AD9850_CLK=1;
		AD9850_CLK=0;
	}
	//дw2����
	w=(y>>16);
	for(i=0;i<8;i++)
	{
		AD9850_DATA=(w>>i)&0x01;
		AD9850_CLK=1;
		AD9850_CLK=0;
	}
	//дw1����
	w=(y>>24);
	for(i=0;i<8;i++)
	{
		AD9850_DATA=(w>>i)&0x01;
		AD9850_CLK=1;
		AD9850_CLK=0;
	}
	//дw0����
	w=w0;   
	for(i=0;i<8;i++)
	{
		AD9850_DATA=(w>>i)&0x01;
		AD9850_CLK=1;
		AD9850_CLK=0;
	}
	//����ʼ��
	AD9850_UD=1;
	AD9850_UD=0;
}


#endif /* AD9850_CONFIG */

