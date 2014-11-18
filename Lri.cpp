#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double c[2]={
	-0.05,0.7 
};

double kr_low = 0.01;
double kr_high = 0.99;
int experiment = 1000;
int count;

int action(double p1)
{
	if(rand()/(float)RAND_MAX<p1)
	{//action 1
		return 0;
	}
	else
	{//action 2
		return 1;
	}
}

int env(int action,double _c1,double _c2)
{
	if(action==0)
	{
		if(rand()/(float)RAND_MAX<_c1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if(rand()/(float)RAND_MAX<_c2)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

double simulate(double kr)
{
	int i=0;
	double p[2]={0.5,0.5};
	int act;
	int beta;
	
	while(0.005<p[0]&&p[0]<0.995)
	{
		count++;
		act = action(p[0]);
		beta = env(act,c[0],c[1]);
		if(beta==0)
		{
			p[1-act]=kr*p[1-act];
			p[act]=1-p[1-act];
		}
	}
	return p[0];
}

void search(double kr_low,double kr_high)
{
	if(kr_high-kr_low<0.001)
	{
		printf("kr=%.3lf\n",kr_low);
	}
	else
	{
		int i;
		
		double kr_middle = (kr_low+kr_high)/2;
		int p1,p2;
		double p;
	
		p1=0;p2=0;
		count=0;
		for(i=0;i<experiment;i++)
		{
			p = simulate(kr_middle);
			if(p<=0.005)
			{
				p2++;
			}
			else
			{
				p1++;
			}
		}
		printf("kr:%.3lf  avg_count:%d\n",kr_middle,count/experiment);
		if(p1<experiment*0.95)
		{
			printf("kr_low=%.3lf  kr_high=%.3lf\n",kr_middle,kr_high);
			search(kr_middle,kr_high);
		}
		else
		{
			printf("kr_low=%.3lf  kr_high=%.3lf\n",kr_low,kr_middle);
			search(kr_low,kr_middle);
		}
		
	}	
}

int main()
{
	srand((unsigned)time(NULL));
	
	int i,j;
	for(i=0;i<7;i++)
	{
		c[0]=0.1+c[0];
		int p1,p2;
		double p;
		printf("c1=%.2lf  c2=%.2lf\n",c[0],c[1]);
	
		p1=0;p2=0;
		count=0;
		for(j=0;j<experiment;j++)
		{
			p = simulate(kr_low);
			if(p<=0.005)
			{
				p2++;
			}
			else
			{
				p1++;
			}
		}
		printf("kr_low=%.3lf  accuracy:%lf  avg_count:%d\n",kr_low,double(p1)/experiment,count/experiment);
		
		if(p1>experiment*0.95)
		{
			printf("out of range!\nkr=%.3lf\n",kr_low);
			printf("----------------------------------------\n");
			break;
		}
		
		p1=0;p2=0;
		count=0;
		for(j=0;j<experiment;j++)
		{
			p = simulate(kr_high);
			if(p<=0.005)
			{
				p2++;
			}
			else
			{
				p1++;
			}
		}
		printf("kr_high=%.3lf  accuracy:%lf  avg_count:%d\n",kr_high,double(p1)/experiment,count/experiment);
		
		if(p1<experiment*0.95)
		{
			printf("out of range!\nkr=%.3lf\n",kr_high);
			printf("----------------------------------------\n");
			break;
		}
		
		search(kr_low,kr_high);
		printf("----------------------------------------\n");
	}
	return 0;
}
