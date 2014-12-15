//L RI
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define n 6
double E[n]={
	0.1,0.1,0.4,0.2,0.1,0.1
};
double L[n]={
	0.2,0.1,0.1,0.1,0.1,0.4
};
double M[n]={0};

double step = 0.0025;	

int Random_i(double ls[n])
{
	double x = rand()%100/(double)100;
	int i=0;
	double sum=0;
	while(i<n)
	{
		sum += ls[i];
		if(sum>x)
		{
			return i;
		}
		i++;
	}
}

int main()
{
	srand((unsigned)time(NULL));
	int i;
	for(i=0;i<6;i++)
	{
		M[i]=(double)1/6;
	}
	
	//run
	int k,m,j;
	int inaction=0;
	int action=0;
	
	int loops = 0;
	int flag = 0;
	j = Random_i(L);
	while(loops<100000)
	{
		loops++;
		m = Random_i(M);
		i = Random_i(E);
		
		
		
		//penalty or reward
		inaction += abs(j-i);
		action += abs(m-i)+abs(j-m)/2;
		if(abs(j-i)<=(abs(m-i)+abs(j-m)/2))
		{//penalty
			//do nothing
		}
		else
		{//reward
			double increase = 0;
			for(k=0;k<n;k++)
			{
				if(k!=m)
				{
					if(M[k] - step>0)
					{
						increase += step;
						M[k] = M[k] - step;
					}
				}
			}
			M[m] += increase;
			if(flag==0&&M[m]>0.99)
			{
				flag = 1;
				printf("loops:%d\n",loops);
			}
		}
		
		j = Random_i(L);
		while(i==j){
			j = Random_i(L);
		} 
	}
	
	printf("inaction:%d\naction:%d\n",inaction,action);
	for(i=0;i<6;i++)
	{
		printf("E:%.3lf,",E[i]);
	}
	printf("\n");
	for(i=0;i<6;i++)
	{
		printf("M:%.3lf,",M[i]);
	}
	
	return 0;
}
