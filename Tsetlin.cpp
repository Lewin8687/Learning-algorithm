#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int N=3;
double c1=-0.05,c2=0.35;
int experiment =20000;
	
int Reward(int N,int i)
{
	if(i==1||i==(N+1))
	{
		return i;
	}
	else
	{
		return i-1;
	}
}

int Penalty(int N,int i)
{
	if(i==N)
	{
		return 2*N;
	}
	else if(i==2*N)
	{
		return N;
	} 
	else
	{
		return i+1;
	}
}
int Env(double c1,double c2,int action)
{
	double x=rand()/(float)RAND_MAX;
	if(action==1)
	{
		if(x<c1)
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
		if(x<c2)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}	
int Tsetlin(int N,int i)
{
	int action;
	if(i<=N)
	{
		action=1;
	}
	else
	{
		action=2;
	}
	int beta = Env(c1,c2,action);
	if(beta==0)
	{
		return Reward(N,i);
	}
	else
	{
		return Penalty(N,i);
	}
}

int main()
{
	srand((unsigned)time(NULL));	

	int i,j,k;
	int count1,count2;
	printf("N=3\n");
	for(k=0;k<7;k++)
	{
		i=rand()/(float)RAND_MAX*2*N;
		j=0;
		count2=0;
		count1=0;
		c1=c1+0.1;
		while(j<experiment)
		{
			j++;
			//printf("%d\n",i);
		 	i = Tsetlin(N,i);
		 	if(i<N+1)
			{
				count1++;
			}
			else
			{
				count2++;
			}
		}
		double exact = 1/(1+pow(c1/c2,N)*(2*c1-1)/(2*c2-1)*(pow(c2,N)-pow(1.0-c2,N))/(pow(c1,N)-pow(1.0-c1,N)));
		printf("c1£º%.2lf   c2:%.2lf\n",c1,c2);
		printf("count1:%d  ",count1);
		printf("count2:%d\n",count2);
		printf("exact p1:%lf\n",exact);
		printf("accuracy:%.4lf\n",double(count1)/double(experiment));
		printf("----------------------------------------------\n");
	}
	return 0;
} 
