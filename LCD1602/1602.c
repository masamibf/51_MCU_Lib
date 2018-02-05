#include"1602.h"
	

/**********���Lcd�Ƿ�æ**********/
void LcdWriteReady()
{
	uchar sta;                                
	LCD1602_DB=0xFF;                          
	LCD1602_RS=0;                             
	LCD1602_RW=1;
	do                                         
  {
		LCD1602_E=1;
		sta=LCD1602_DB;
		LCD1602_E=0;
	}while(sta&0x80);                       
}

/**********Lcdд�����**********/
void LcdWriteCmd(uchar cmd)
{
	LcdWriteReady();                           
	LCD1602_RS=0;                             
	LCD1602_RW=0;
	LCD1602_DB=cmd;
	LCD1602_E=1;
	LCD1602_E=0;
}

/**********Lcd��ʼ������**********/
void InitLcd1602()
{
	LcdWriteCmd(0x38);                         
	LcdWriteCmd(0x0c);                        
	LcdWriteCmd(0x06);                      
	LcdWriteCmd(0x01);  
}

/**********Lcd���ó�ʼ���**********/
void LcdSetCursor(uchar x,uchar y)          
{
	uchar addr;
	if(y==0)
	{
		addr=0x00+x;                         
	}
	else
	{
		addr=0x40+x;                             
	}
	LcdWriteCmd(addr|0x80);                   
}

/**********Lcdд���ݺ���**********/
void LcdWriteDat(uchar dat)
{
	LcdWriteReady();                           
	LCD1602_RS=1;                             
	LCD1602_RW=0;
	LCD1602_DB=dat;
	LCD1602_E=1;
	LCD1602_E=0;
}

/**********Lcd��ʾ�ַ�������**********/
void LcdShowStr(uchar x,uchar y,uchar *str)
{
	LcdSetCursor(x,y);                         //������ʼ����
	while(*str!='\0')                          //���ַ���û�н���ʱ����д��
	{
		LcdWriteDat(*str++);                     //��ȡstrָ������� �ٽ�str+1
	}
}

/**********Lcd��ʾ���ݺ���**********/
void LcdShowDat(uchar x,uchar y,uchar num)
{
	LcdSetCursor(x,y);
	LcdWriteDat(num);
}

/**********�򿪹����ʾ**************/
void LcdOpenCursor()
{
	LcdWriteCmd(0x0F);
}

/**********�رչ����ʾ**************/
void LcdCloseCursor()
{
	LcdWriteCmd(0x0C);
}

