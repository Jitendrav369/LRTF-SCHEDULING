#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
struct process
{
	int p_id;
	int arrival_time;
	int burst_time;
	int waiting_time;
	int turn_around_time;
};
int complete(int *a,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(a[i]!=0)
		return 1;
	}
	return 0;
}
int longest_rem(struct process *p,int *b,int n,int time)
{
	int i,j,flag=0,prior;
	int big=0;int t=0;
	for(i=0;i<n;i++)
	{
		
		if(b[i]>big&&p[i].arrival_time<=time)
		{
		big=b[i];
		t=i;
		}
	}
	for(i=0;i<n;i++)
	{
		if(b[i]==big)
		{
			flag++;
			if(flag==1)
			prior=p[i].p_id;
			if(p[i].p_id<prior)
			{
				prior=p[i].p_id;
				t=i;
			}
		}
	}
	return t;	
}

int main()
{
	const char *print;
	int n;
	print="ENTER THE NUMBER OF STUDENTS ARRIVING IN THE MESS\n";
	write(1,print,strlen(print));
	scanf("%d",&n);
	struct process p[n];
	int i=0;
	int b_t[n];
	while(i<n)
	{
		print="*****************************";
		write(1,print,strlen(print));
		print="\nENTER THE ID NUMBER OF THE STUDENT\n";
		write(1,print,strlen(print));
		scanf("%d",&p[i].p_id);
		print="\nENTER THE ARRIVAL TIME OF THE STUDENT\n";
		write(1,print,strlen(print));
		scanf("%d",&p[i].arrival_time);
		print="\nENTER THE FOOD TAKING TIME OF THE STUDENT\n";
		write(1,print,strlen(print));
		scanf("%d",&p[i].burst_time);
		b_t[i]=p[i].burst_time;
		p[i].turn_around_time=0;
		p[i].waiting_time=0;
		i++;
	}
	int current_student=0,j,time_elapsed=0;
	
	while(complete(b_t,n))
	{
		
		current_student=longest_rem(&p,b_t,n,time_elapsed);
		b_t[current_student]--;
		for(i=0;i<n;i++)
		{
			if(p[i].arrival_time<=time_elapsed&&current_student!=i&&b_t[i]>0)
				p[i].waiting_time++;
		}
		time_elapsed++;
	}
		float avg_tat=0.0;
		float avg_wt=0.0;
		printf("\n\nSTUDENT ID\tTurn Around Time\tWaiting Time\n");
		for(i=0;i<n;i++)
		{
			p[i].turn_around_time=p[i].burst_time+p[i].waiting_time;
			
			printf("\n%d\t\t%d\t\t\t%d\n",p[i].p_id,p[i].turn_around_time,p[i].waiting_time);
			
			avg_tat+=p[i].turn_around_time;
			avg_wt+=p[i].waiting_time;				
		}
		avg_tat=avg_tat/n;
		avg_wt=avg_wt/n;
		printf("\nAVERAGE TURN AROUND TIME = %f",avg_tat);
		printf("\nAVERAGE WAITING TIME = %f",avg_wt);
}