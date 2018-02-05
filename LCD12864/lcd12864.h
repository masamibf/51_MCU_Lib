#ifndef __LCD12864_H__
#define __LCD12864_H__

#include "reg52.h"
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

/****************************************************************************/
//TS12864��������趨//
sbit MPU_RS_CH=P1^5;						//�Ĵ���ѡ������
sbit MPU_RW_CH=P1^6; 					//��д����
sbit MPU_ENABLE=P1^7;						//ʹ�ܿ���
#define	LCD_DATA	P0							//Һ�����ݿ�
//-----------------------------------------------
#define	OFF			0							//�߼���
#define	ON			1							//�߼���
//-----------------------------------------------

	//0x01					//����ʾָ��
	//0x06					//��������ģʽ
	//0x0c					//���ÿ��Կ���
	//0x30					//�����趨(����ָ��)
	//0x34					//�����趨(����ָ��)
	//0x36					//���û�ͼ����

//�ӳ�������
//void procKey (void);

void LcdInit (void);

void LcdClear (void);

void LcdWriteCmd (uchar cmd); 

void LcdWriteDat (uchar dat); 

void LcdCheckBusy(void); 

void LcdShowPhoto1(uchar *img);

void LcdShowPhoto2(uchar *img);

void LcdShowPhoto3(uchar x,uchar y,uchar sign,uchar tt);

void write1616GDRAM(uchar x,uchar y,uchar sign,uchar *bmp);

void ConvertChar (uchar CX,uchar CY,uchar width); 

void LcdSetCursor (void);

void LcdShowStr (uchar X,uchar Y,uchar speed,uchar *msg);

//void init_dz();

void Clear_img();
#endif