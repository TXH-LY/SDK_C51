#include "lcd12864.h"


#ifdef LCD12864_CONFIG

static void delay_10us(uint z)
{
	uint i;
	while(z--)
	{
		for(i=0;i<10;i++) _nop_();
	} 
}

/*------------------------------------------------
                     æ��
������    LCD12864_Busy()
�������  ��
��������  result
------------------------------------------------*/
bit LCD12864_Busy()
{
   bit result;
   LCD12864_RS = 0;
   LCD12864_RW = 1;
   LCD12864_EN = 1;
   result = (bit)(LCD12864_Data & 0x80);
   LCD12864_EN = 0;
   return result;
}



/*------------------------------------------------
                     д����
������    LCD12864_Write_Data()
�������  dat
��������  ��
------------------------------------------------*/
void LCD12864_Write_Data(uchar dat)
{
	while(LCD12864_Busy());
	LCD12864_RS = 1;
	LCD12864_RW = 0;
	LCD12864_EN = 0;
	delay_10us(1);
	LCD12864_Data = dat;
	delay_10us(1);
	LCD12864_EN = 1;
	delay_10us(20);
	LCD12864_EN = 0;
}


/*------------------------------------------------
                     д����
������    LCD12864_Write_Com()
�������  com
��������  ��
------------------------------------------------*/
void LCD12864_Write_Command(uchar com)
{
	while(LCD12864_Busy()); 
	LCD12864_RW = 0;
	LCD12864_RS = 0;
	LCD12864_EN = 0;
	delay_10us(1);
	LCD12864_Data = com;
	delay_10us(1);
	LCD12864_EN = 1;
	delay_10us(20);
	LCD12864_EN = 0;
}


/*------------------------------------------------
                     ��ʼ��
������    LCD12864_Init()
�������  ��
��������  ��
------------------------------------------------*/
void LCD12864_Init()
{
	LCD12864_PSB = 1;
	delay_10us(20);
	LCD12864_Write_Command(0x34);
	LCD12864_Write_Command(0x30);
	LCD12864_Write_Command(0x08);
	LCD12864_Write_Command(0x01);
	LCD12864_Write_Command(0x06);
	LCD12864_Write_Command(0x0c);
}



/*------------------------------------------------
                    ��ʾ����
������    LCD12864_Display_Char() ;LCD12864_Display_Str()    
�������  x,y,dat                  x,y,*dat
��������  ��                       ��
------------------------------------------------*/
uchar addresses[] = {0x80,0x90,0x88,0x98};
void LCD12864_Display_Char(uchar x,uchar y,uchar dat)
{
	LCD12864_Write_Command(0x30);
	LCD12864_Write_Command(0x06);
	LCD12864_Write_Command(addresses[x-1]+(y-1));
	LCD12864_Write_Data(dat);
}

void LCD12864_Display_Str(uchar x,uchar y,uchar *dat)
{
	LCD12864_Write_Command(0x30);
	LCD12864_Write_Command(0x06);
	LCD12864_Write_Command(addresses[x-1]+(y-1));
	while(*dat != '\0')
	{
		LCD12864_Write_Data(*dat);
		dat++;
	}
}

#endif /* LCD12864_CONFIG */
