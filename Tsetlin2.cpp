#include <stdio.h>
#include <math.h>

int low=3,high=20;
double c1=-0.05,c2=0.7;


double calculate(double _c1,double _c2,int N)
{
	double exact = 1/(1+pow(_c1/_c2,N)*(2*_c1-1)/(2*_c2-1)*(pow(_c2,N)-pow(1.0-_c2,N))/(pow(_c1,N)-pow(1.0-_c1,N)));
	return exact;
}


void backtrack(int _low, int _high)
{
	printf("low=%d,%.3lf;high=%d,%.3lf\n",_low,calculate(c1,c2,_low),_high,calculate(c1,c2,_high));
	if(_low<_high-1)
	{
		double middle=calculate(c1,c2,(_low+_high)/2);
		if(middle<0.95)
		{
			backtrack((_low+_high)/2,_high);
		}
		else if(middle>0.95)
		{
			backtrack(_low,(_low+_high)/2);
		}
		else
		{
			printf("N=%d,0.95\n",(_low+_high)/2);
			return;
		}
	}
	else
	{
		if(calculate(c1,c2,_low)>=0.95)
		{
			printf("N=%d,%.3lf\n",_low,calculate(c1,c2,_low));
		}
		else
		{
			printf("N=%d,%.3lf\n",_high,calculate(c1,c2,_high));
		}
	}
}

int main()
{
	int i=0;
	for(i=0;i<7;i++)
	{
		c1=c1+0.1;
		printf("c1=%.2lf  c2=%.2lf\n",c1,c2);
		backtrack(low,high);
		printf("-----------------------------------------------------\n");
	}
	
	return 0;
} 
