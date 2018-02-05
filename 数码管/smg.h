#ifndef __SMG_H__
#define __SMG_H__

#include "reg52.h"

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
	
#define SMGDUAN P0                        //�궨���������ܶ�ѡ�Ķ˿�ΪP0
#define SMGWEI P2                         //�궨����������λѡ�Ķ˿�ΪP2��P2����λP2.0 P2.1 P2.2��



void LedScan();
void LedShowNum(ulong num);
void Timer0Init(uint ms);

#endif