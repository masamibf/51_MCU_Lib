#include"DS18B20.h"
	

extern uchar tflag;//�¶�������־λ



bit	RESET_DS18B20(void)  //��λ
{
	EA=0;
	DS18B20_DQ = 1;
	DS18B20_DQ = 0;
	Delay_Us(247);
	DS18B20_DQ = 1;
	Delay_Us(27);
	EA=1;
	if(DS18B20_DQ == 0)
	{
		while(DS18B20_DQ == 0);
		return 0;
	}
	else
	{
		return 1;
	}
}

void Write_DS18B20_DATA(uchar Value)  //д��һ���ֽ�����
{
	uchar i=0;
	EA=0;
	for(i=0;i<8;i++)
	{
		DS18B20_DQ = 1;
		DS18B20_DQ = 0;
		Delay_Us(5);			
		DS18B20_DQ = Value & 0x01;
		Delay_Us(20);
		DS18B20_DQ = 1;
		Value >>= 1;
	}
	EA=1;
}

uchar Read_DS18B20_DATA(void) //��ȡһ���ֽ�
{
	uchar i=0;
	uchar Value=0;
	EA=0;
	for(i=0;i<8;i++)
		{
			DS18B20_DQ = 1;
			DS18B20_DQ = 0;
			Delay_Us(1);
			DS18B20_DQ = 1;
			Delay_Us(1);
			if(DS18B20_DQ)
				{
					Value|=0x01<<i;
				}
			Delay_Us(17);
			DS18B20_DQ = 1;
			_nop_();
		}
		EA=1;
	return Value;
}

uint Read_DS18B20_TEMP(void) //��ȡ�¶�
{
	uchar Temp_L = 0;
	uchar Temp_H = 0;
	uint Temp = 0;
	float tt=0;
	RESET_DS18B20();
	Write_DS18B20_DATA(0xCC);
	Write_DS18B20_DATA(0x44);
	RESET_DS18B20();
	Write_DS18B20_DATA(0xCC);
	Write_DS18B20_DATA(0xBE);
	Temp_L = Read_DS18B20_DATA();
	Temp_H = Read_DS18B20_DATA();
	Temp = Temp_H;
	Temp <<=8;
	Temp = Temp | Temp_L;
	if(Temp<0x0fff)		//�ж��¶�����
   	tflag=0;	     	//tflag=0�¶�Ϊ��
    else
    {
		Temp=~Temp+1;			//�¶�Ϊ����,��ֵ�Բ�����,���ｫ�仹ԭΪԭ��
		tflag=1;		//tflag=1�¶�ֵΪ��
   	}
	
	tt=Temp*0.0625;
	Temp= tt*10;
	return Temp;
}

void Delay_Us(uchar i)
{
	while(-- i);
}