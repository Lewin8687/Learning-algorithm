#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int experiment =20000;
int N=6;
double c1=-0.05,c2=0.7;

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
	int beta = Env(c1/2,c2/2,action);
	if(beta==0)
	{
		return Reward(N,i);
	}
	else
	{
		return Penalty(N,i);
	}
}
	
int K_Reward(int N,int i)
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

int K_Penalty(int N,int i)
{
	int left = int(rand()/(float)RAND_MAX+0.5);
	if(i==N)
	{
		if(left==0)
		{
			return N-1;
		}
		else
		{
			return 2*N;
		}
	}
	else if(i==2*N)
	{
		if(left==0)
		{
			return 2*N-1;
		}
		else
		{
			return N;
		}
	}
	else if(i==1)
	{
		if(left==0)
		{
			return 1;
		}
		else
		{
			return 2;
		}	
	}
	else if(i==(N+1))
	{
		if(left==0)
		{
			return i;
		}
		else
		{
			return i+1;
		}
	}
	else
	{
		if(left==0)
		{
			return i-1;
		}
		else
		{
			return i+1;
		}
	}
}
int K_Env(double c1,double c2,int action)
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
int Krylov(int N,int i)
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
	int beta = K_Env(c1,c2,action);
	if(beta==0)
	{
		return K_Reward(N,i);
	}
	else
	{
		return K_Penalty(N,i);
	}
}

int main()
{
	srand((unsigned)time(NULL));	

	int i,j,k;
	int count2,count1;
	for(k=0;k<7;k++)
	{
		c1=c1+0.1;
		j=0;
		count1=0,count2=0;
		i= int(rand()/(float)RAND_MAX*2*N);
		while(j<experiment)
		{
			j++;
			//printf("%d\n",i);
			i = Krylov(N,i);
			if(i<=N)
			{
				count1++;
			}
			else
			{
				count2++;
			}
		}
		printf("Krylov\n");
		printf("c1£º%.2lf   c2:%.2lf\n",c1,c2);
		printf("count1:%d  ",count1);
		printf("count2:%d\n",count2);
		printf("p1:%.4lf\n\n",double(count1)/double(experiment));
		
		j=0;
		count1=0,count2=0;
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
		printf("Tsetlin\n");
		printf("count1:%d  ",count1);
		printf("count2:%d\n",count2);
		printf("p1:%.4lf\n",double(count1)/double(experiment));
		printf("----------------------------------------------\n");
	}
	
	
	return 0;
} 
