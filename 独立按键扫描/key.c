//**********************Disigned By F H X***************************//
//*********************4λ��������ɨ�����**************************//
//*****1 ������������ ����ⰴ������ ִ�� mian.c �а�����������*****//
//*****2 ����ɨ�躯�� ��ɨ�谴��״̬ ��main.c �е��жϺ���������****//


#include "key.h"

uchar code KeyCodeMap[4] = {0x1B,0x26,0x0D,0x28,};         // ASC���ֵ : ESC�� ���ϼ� �س��� ���¼� 
uchar KeySta[4] = {1,1,1,1};                              // ������ǰ״̬ Ĭ��Ϊ����
ulong pdata KeyDownTime[4] = {0,0,0,0};                   // ��������ʱ�� Ĭ��Ϊ0

extern void KeyDown(uchar keycode);

/**********������������**********/
void KeyDrive()
{
	uchar i;
	static uchar backup[4] = {1,1,1,1};                     //�����ϴΰ���״̬ Ĭ�϶�Ϊ����
	static ulong pdata TimeTh[4] = {1000,1000,1000,1000};   //��������ʱ����ֵ ������ֵ��Ϊ����ģʽ
	for(i=0;i<4;i++)
	{
		if(backup[i]!=KeySta[i])                              //��ⰴ������
		{
			if(KeySta[i]==0)                                    //����������	
			{
				KeyDown(KeyCodeMap[i]);                           //ִ�а�����������
			}
			backup[i]=KeySta[i];                                //���浱ǰ����״̬
		}
    if(KeyDownTime[i]>0)                                  //��ⰴ������ʱ��
		{
			if(KeyDownTime[i]>=TimeTh[i])                       //��������ʱ�������ֵ ִ�а�����������
			{
				KeyDown(KeyCodeMap[i]);
				TimeTh[i]+=200;                                   //��ֵ����
			}
		}
		else 
		{
			TimeTh[i]=1000;                                     //��������ʱ�ָ���ֵʱ��
		}
	}
}

/**********����ɨ�躯��**********/
void KeyScan()
{
	uchar i;
	static uchar Keybuff[4]={0xFF,0xFF,0xFF,0xFF};          //����ɨ�軺����
	
	Keybuff[0]=(Keybuff[0]<<1)|KEY_1;                       //���ɨ��4���������� ����ʱ��������
	Keybuff[1]=(Keybuff[1]<<1)|KEY_2;
	Keybuff[2]=(Keybuff[2]<<1)|KEY_3;
	Keybuff[3]=(Keybuff[3]<<1)|KEY_4;
	for(i=0;i<4;i++)
	{
		if((Keybuff[i]&0x0F)==0x00)                           //��⵽ĳ������������
		{
			KeySta[i]=0;                                        //�ı�ð���״̬
			KeyDownTime[i]+=4;                                  //�ð�������ʱ���ۼ�
		}
		else if((Keybuff[i]&0x0F)==0x0F)                      //��⵽ĳ����������
		{
			KeySta[i] = 1;                                      //�ı�ð���״̬
      KeyDownTime[i] = 0;                                 //�ð�������ʱ������
		}
  }
}