#include"key.h"
//**********************Disigned By F H X***************************//
//*********************4*4�������ɨ�����**************************//
//*****1 ������������ ����ⰴ������ ִ�� mian.c �а�����������*****//
//*****2 ����ɨ�躯�� ��ɨ�谴��״̬ ��main.c �е��жϺ���������****//

/*uchar code KeyCodeMap[4][4]={             //ASC�����
     {'1','2','3',0x26},               //���ּ�1�����ּ�2�����ּ�3�����ϼ�
     {'4','5','6',0x25},               //���ּ�4�����ּ�5�����ּ�6�������
     {'7','8','9',0x28},               //���ּ�7�����ּ�8�����ּ�9�����¼� 
     {'0',0x1B,0x0D,0x27}                //���ּ�0,  ESC�� ���س��� �����Ҽ�
};*/

uchar code KeyCodeMap[4][4]={            
     {0x31,0x32,0x33,0x26},               
     {0x34,0x35,0x36,0x25},              
     {0x37,0x38,0x39,0x28},             
     {0x30,0x1B,0x0D,0x27}                
};

uchar KeySta[4][4]={                      //16��������ǰ״̬
	   {1,1,1,1},
     {1,1,1,1},
     {1,1,1,1},
     {1,1,1,1} 
};                                        
ulong pdata KeyDownTime[4][4]={           //16����������ʱ��
     {0,0,0,0},
     {0,0,0,0},
     {0,0,0,0},
     {0,0,0,0} 
};  


/**********������������**********/
void KeyDrive()
{
	uchar i,j;
	static uchar backup[4][4]={             //�����ϴΰ���״̬ Ĭ�϶�Ϊ����
     {1,1,1,1},
     {1,1,1,1},
     {1,1,1,1},
     {1,1,1,1}
	};
	static ulong pdata TimeTh[4][4]={       //��������ʱ����ֵ ������ֵ��Ϊ����ģʽ
     {1000,1000,1000,1000},
     {1000,1000,1000,1000},
     {1000,1000,1000,1000},
     {1000,1000,1000,1000}
	};
	for(i=0;i<4;i++)                        //ѭ��ɨ��4��4�������
	{
		for(j=0;j<4;j++)
		{
			if(backup[i][j]!=KeySta[i][j])      //��ⰴ������
			{
				if(KeySta[i][j]==0)               //����������
				{
					KeyDown(KeyCodeMap[i][j]);      //ִ�а�����������
				}
				backup[i][j]=KeySta[i][j];        //���浱ǰ����ֵ
			}
			if(KeyDownTime[i][j]>0)             //��ⰴ������ʱ��
			{
				if(KeyDownTime[i][j]>=TimeTh[i][j])
				{
					KeyDown(KeyCodeMap[i][j]);      //��������ʱ�������ֵ ִ�а�����������
					TimeTh[i][j]+=200;              //��ֵ����
				}
			}
			else 
			{
				TimeTh[i][j]=1000;                //��������ʱ�ָ���ֵʱ��
			}
		}
	}
}

/**********����ɨ�躯��**********/
void KeyScan()
{
	uchar i;
	static uchar keyout=0;                  //���󰴼�ɨ���������
	static uchar Keybuff[4][4]={            //����ɨ�軺����
		{0xFF,0xFF,0xFF,0xFF},
    {0xFF,0xFF,0xFF,0xFF},
    {0xFF,0xFF,0xFF,0xFF},
    {0xFF,0xFF,0xFF,0xFF}
	};
	                                        //���м�ⰴ���Ƿ񱻰��� �𵽰�����������
  Keybuff[keyout][0]=(Keybuff[keyout][0]<<1)|KEY_IN_1;
	Keybuff[keyout][1]=(Keybuff[keyout][1]<<1)|KEY_IN_2;
	Keybuff[keyout][2]=(Keybuff[keyout][2]<<1)|KEY_IN_3;
	Keybuff[keyout][3]=(Keybuff[keyout][3]<<1)|KEY_IN_4;
	for(i=0;i<4;i++)
	{
		if((Keybuff[keyout][i]&0x0F)==0x00)     //���ĳ������������
		{
			KeySta[keyout][i]=0;                //�ı�ð���״̬
			KeyDownTime[keyout][i]+=4;          //�ð�������ʱ���ۼ�
		}
		else if((Keybuff[keyout][i]&0x0F)==0x0F)//���ĳ����������
		{
			KeySta[keyout][i] = 1;              //�ı�ð���״̬
      KeyDownTime[keyout][i] = 0;         //�ð�������ʱ������
		}
	}
	keyout++;
	keyout&=0x03;                           //keyout��4�Զ�����
	switch(keyout)
	{
		case 0:KEY_OUT_4=1,KEY_OUT_1=0;break; //���ߵ�ǰ����� �����´������
		case 1:KEY_OUT_1=1,KEY_OUT_2=0;break;
		case 2:KEY_OUT_2=1,KEY_OUT_3=0;break;
		case 3:KEY_OUT_3=1;KEY_OUT_4=0;break;
		default:break;
	}
}
