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
	int k,m,action_m1,action_m2,inaction_m1,inaction_m2,j;
	int inaction=0;
	int action=0;
	
	int loops = 0;
	int flag = 0;
	action_m1 = Random_i(M);
	action_m2 = Random_i(M);
	inaction_m1 = action_m1;
	inaction_m2 = action_m2;
	j = Random_i(L);
	int elevator,onestep,inactionstep;
	while(loops<100000)
	{
		loops++;
		
		i = Random_i(E);
		
		//action
		m = Random_i(M);
		if(abs(action_m1-i)<=abs(action_m2-i))
		{
			inactionstep = abs(action_m1-i);
		}
		else
		{
			inactionstep = abs(action_m2-i);
		}
		
		if(abs(action_m1-m)<=abs(action_m2-m))
		{
			action_m1 = m;
			onestep = abs(m-action_m1)/2;
		}
		else
		{
			action_m2 = m;
			onestep = abs(m-action_m2)/2;
		}
		
		if(abs(action_m1-i)<=abs(action_m2-i))
		{
			flag = 1;
			onestep += abs(action_m1-i);
			action += onestep;
		}
		else
		{
			flag = 2;
			onestep += abs(action_m2-i);
			action += onestep;
		}
		
		//penalty or reward
		if(inactionstep<=onestep)
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
		//
		j = Random_i(L);
		while(i==j){
			j = Random_i(L);
		}
		 
	 	//inaction
		if(abs(inaction_m1-i)<=abs(inaction_m2-i))
		{
			inaction += abs(inaction_m1-i);
			inaction_m1 = j;
		}
		else
		{
			inaction += abs(inaction_m2-i);
			inaction_m2 = j;
		}
		//action
		if(elevator==1)
		{
			action_m1 = j;
		}
		else
		{
			action_m2 = j;
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
