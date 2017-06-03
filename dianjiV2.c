//直流电机PWM调速系统设计

#include <reg52.h>

int i,d0,v;
int table[]={0xc0,0xf9,0xa4,0xb0,0x99,
             0x92,0x82,0xf8,0x80,0x90};
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit key1 = P3^5;
sbit key2 = P3^4;
sbit key3 = P3^3;
sbit key4 = P3^2;

void main()
{
	int j,m1,m2,m3,m4;
	
	d0 = 1;
	v = 1;
	m4 = 1;
	P1 = 0xff;
	
	TMOD = 0x01;
	TH0 = 0xff;
	TL0 = 0xd8;
	EA = 1;		
	ET0 = 1;	
	TR0 = 1 ;		
		
	while(1)
	{
		P0 = table[m1];
		P2_0 = 0;
		for(j=0;j<20;j++);
		P2_0 = 1;

		P0 = table[m2];
		P2_1 = 0;
		for(j=0;j<20;j++);
		P2_1 = 1;

		P0 = table[m3];
		P2_2 = 0;
		for(j=0;j<20;j++);
		P2_2 = 1;

		P0 = table[m4];
		P2_3 = 0;
		for(j=0;j<20;j++);
		P2_3 = 1;
		
		if(key1==0)
		{
			while(key1==0);
			d0 = !d0;
			m2 = !m2;
		}

		if(key3==0)
		{
			while(key3==0);
			if(v<5)
				v++;
			m4 = v;
		}

		if(key4==0)
		{
			while(key4==0);
			if(v>0)
				v--;
			m4 = v;
		}				
	}
}

void t0(void) interrupt 1
{
	TH0 = 0xff;
	TL0 = 0xd8;

	i++;
	if(i>=5)
		i = 0;
	if(i<v)
	{
	 	if(d0==1)
			P1_0 = 0;
		else
			P1_1 = 0;	
	}
	else
	{	P1_0 = 1;
		P1_1 = 1;
	}
}
