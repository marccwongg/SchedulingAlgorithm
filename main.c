// algorithm and code referred from
//https://www.geeksforgeeks.org/program-for-fcfs-cpu-scheduling-set-1/
//https://www.geeksforgeeks.org/program-for-fcfs-cpu-scheduling-set-2-processes-with-different-arrival-times/
//https://gist.github.com/debashisbarman/63018fceacf1284b51c2
//https://myprogworld.wordpress.com/2015/09/10/shortest-job-first-scheduling-non-preemptive/
//https://www.edureka.co/blog/sjf-scheduling-in-c/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//function prototyping
void fcfs(int n, int bt2[], int at2[]);
void SJF(int n, int bt1[], int at1[]);
void RR(int n, int bt3[], int at3[]);
void compare();
void workload1();
void workload2();

//global variables

float avg_wtsjf, avg_ttsjf, avg_wtfcfs;
float avg_ttfcfs, avg_wtrr, avg_ttrr;

int main()
{
  int worktype;
  int flagwl1=0;
  int flagwl2=0;
    // ask user to choose workload to run
    while (flagwl1==0 && flagwl2==0){
    printf("1 = Character reading or 2 = multiplication by 2\n");
    printf("Please select the workload:");
    scanf("%d", &worktype);
    printf("\n" );
    if (worktype == 1){
      flagwl1=1;
      workload1();
    }

    else if (worktype == 2){
      flagwl2=1;
      workload2();
    }

    else {
    printf("Invalid workload chosen\n");
    }
    }
    int n;
    //ask user for number of process
    printf("\nWorkload %d:\n How many processes are there? (Maximum amount of processes to put is 10)\n",worktype);
    scanf("%d",&n);
    if (n <=10 )
    {

        printf("number of process chosen from workload %d is %d",worktype,n);
          int bt[n],at[n];
          int at1[n],bt1[n],at2[n],bt2[n],at3[n],bt3[n];
       for (int k = 0; k < n; k++)
       {
          //Ask for arrival time
	      printf("\nEnter arrival time for process [%d] :", k+1);
          scanf("%d",&at[k]);
          at1[k] = at[k];
           at2[k] = at[k];
           at3[k] = at[k];

          //Ask for burst time
          printf("\nEnter burst time for process [%d] :", k+1);
          scanf("%d",&bt[k]);
          bt1[k] = bt[k];
          bt2[k] = bt[k];
          bt3[k] = bt[k];
       }
       int flaga=0,flagb=0,flagc=0;
       int algotype;
    //ask user to choose scheduler algorithm
    while (flaga==0 || flagb==0 || flagc==0){
      printf("\nKey in the number of your desired algorithm to run:\n1.First Come First Serve\n2.Shortest Job First\n3. Round Robin\n");
      scanf("%d",&algotype);
      if (algotype == 1){
      fcfs(n,bt2,at2);
      flaga=1;
      }
      else if(algotype == 2){
      SJF(n,bt1,at1);
      flagb=1;
      }
      else if (algotype == 3){
      RR(n,bt3,at3);
      flagc=1;
      }
      else
      printf("Invalid algorithm chosen!\n");
      }
     compare();

    }
    else
	  {
      printf("Please keep number of processes within 10");
    }

  return 0;
}//end of main()

//Read Character function (workload 1)
void workload1()
{
    printf("Character reading \n");
    char psetw1[10] = {'c','o','m','p','u','t','e','r','s','\0'};
    for (int i= 0; i<10; i++)
    {
        printf("[p(%d)] : %c\n",i,psetw1[i]);
    }
    printf("Note that last process is a null character\n");
}

// workload 2
void workload2(){
   int psetw2[10];
   printf("Multiplication by 2\n");
     psetw2[0] = 2;
     printf("[p(1)] : %d\n",psetw2[0]);
    for(int i=1; i < 10 ; i++){
        psetw2[i] = psetw2[i-1]*2;
        printf("[p(%d)] : %d\n",i+1,psetw2[i]);
    }
}

//SJF Function
void SJF(int n, int bt1[], int at1[])
{
    int x, y, z;
    int i,p[10]={1,2,3,4,5,6,7,8,9,10},min,k=1,btime=0, ct[10];
    int temp,j,wt[10],tt[10],ta=0,sum=0;
    float tsum=0,wsum=0;


    printf(" -------Shortest Job First Scheduling ( NP )-------\n");
    /*Sorting According to Arrival Time*/

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(at1[i]<at1[j])
            {
                temp=p[j];
                p[j]=p[i];
                p[i]=temp;
                temp=at1[j];
                at1[j]=at1[i];
                at1[i]=temp;
                temp=bt1[j];
                bt1[j]=bt1[i];
                bt1[i]=temp;
            }
        }
    }

/*Arranging the table according to Burst time,
Execution time and Arrival Time
Arrival time <= Execution time
*/

    for(j=0;j<n;j++)
    {
        btime=btime+bt1[j];
        min=bt1[k];
        for(i=k;i<n;i++)
        {
            if (btime>=at1[i] && bt1[i]<min)
            {
                temp=p[k];
                p[k]=p[i];
                p[i]=temp;
                temp=at1[k];
                at1[k]=at1[i];
                at1[i]=temp;
                temp=bt1[k];
                bt1[k]=bt1[i];
                bt1[i]=temp;
            }
        }
        k++;
    }
    wt[0]=0;
    for(i=1;i<n;i++)
    {
        sum=sum+bt1[i-1];
        wt[i]=sum-at1[i];
        if (wt[i] < 0)
        {
            wt[i] = 0;
        }
        wsum=wsum+wt[i];
    }

    avg_wtsjf=((float)wsum/(float)n);
    for(i=0;i<n;i++)
    {
        ta=ta+bt1[i];
        tt[i]=ta-at1[i];
        tsum=tsum+tt[i];
    }

    avg_ttsjf=((float)tsum/(float)n);
    printf("******************************************************************");
    printf("\n RESULT:-");
    printf("\nProcess\t Burst\t Arrival\t Waiting\t Turn-around\t Completion");
    for(i=0;i<n;i++)
    {
        ct[i] = at1[i] + tt[i];
        printf("\n P[%d]\t %d\t %d\t\t %d\t\t\t%d\t\t%d",p[i], bt1[i],at1[i],wt[i],tt[i], ct[i]);
    }

    printf("\n\nAVERAGE WAITING TIME : %.2f",avg_wtsjf);
    printf("\nAVERAGE TURN AROUND TIME : %.2f\n",avg_ttsjf);
}

//fcfs function
void fcfs( int n, int bt2[], int at2[])
{
	int wt[n], tat[n], ctime,totalwt = 0, totaltat = 0;
  int temp[n];
  temp [0] = 0;
		wt[0] = 0;  //first process wait time is always 0
	    for (int g = 1; g < n ; g++ ) // calculating waiting time for 2nd process onwards
	    {
        temp[g] = temp[g-1] + bt2[g-1];
         wt[g] = temp[g] - at2[g];
		       if (wt[g] < 0)     // If waiting time for a process is in negative
           {wt[g] = 0;}       // that means it is already in the ready queue
      }                       // before CPU becomes idle so its waiting time is 0
        for (int u = 0; u < n ; u++)  // turnaround time is wait time and cpu burst time together
		      {tat[u] = bt2[u] + wt[u];}
printf("No  Arrival Time  Waiting Time  Burst Time  Turnaround Time  Completion Time\n");

  // Calculate total waiting time and total turn around time
    for (int i=0; i<n; i++)
  {totalwt += wt[i];
    totaltat += tat[i];
    ctime = tat[i] + at2[i];
    printf("P[%d]\t",i+1);//iocp[i]
    printf("%d\t\t",at2[i]);
    printf("%d\t\t",wt[i]);
    printf("%d\t\t",bt2[i]);
    printf("%d\t\t",tat[i]);
    printf("%d\n",ctime);}
	avg_wtfcfs=(float)totalwt / (float)n;
	avg_ttfcfs=(float)totaltat / (float)n;
	printf("Average waiting time = %.2f\n",avg_wtfcfs);
	printf("Average turnaround time = %.2f\n",avg_ttfcfs);
}


//RR Function
struct process
	{
		int at,bt,wt,tt,rt;
		int procno,completed,overhead;
	}
	p[10];
	int n;
	int q[10]; //queue
	int front=-1,rear=-1;

void enqueue(int i)
	{
		if(rear==10)
		printf("overflow");
		rear++;
		q[rear]=i;
		if(front==-1)
		front=0;

	}

int dequeue()
	{
		int temp;
		if(front==-1)
		printf("underflow");
		temp=q[front];
		if(front==rear)
		front=rear=-1;
		else
		front++;
		return temp;
	}
int isInQueue(int i)
{
	int k;
	for(k=front;k<=rear;k++)
	{
	if(q[k]==i)
	return 1;
	}
	return 0;
}
void sortByArrival()
	{
		struct process temp;
		int i,j;
	for(i=0;i<n-1;i++)
		{
			for(j=i+1;j<n;j++)
			{
				if(p[i].at>p[j].at)
				{
					temp=p[i];
					p[i]=p[j];
					p[j]=temp;
				}
			}
		}
	}

void RR(int n, int bt3[], int at3[])
{
	int i,j,time=0,sum_bt=0,tq,useroh;
	int c;
	float avgwt=0,avgtt=0;
	for(i=0,c=1;i<n;i++,c++)
	{
		p[i].procno=c;
		p[i].at=at3[i];
		p[i].bt=bt3[i];
		p[i].rt=p[i].bt;
		p[i].completed=0;
		sum_bt+=p[i].bt;
	}

	printf("\nEnter the time quantum:");
	scanf("%d",&tq);

    //User choose with overhead or without
    printf("\nOverhead = 2\n");
    printf("\nChoose with overhead or without overhead:\n");
    printf("\n1 = With Overhead\n 2 = Without Overhead\n:");
	scanf("%d",&useroh);

	sortByArrival();
	enqueue(0); // enqueue the first process
	printf("Process execution order: ");
	for(time=p[0].at;time<sum_bt;) // run until the total burst time reached
	{
		i=dequeue();

		if(p[i].rt<=tq)
		{ /* for processes having remaining time with less than or equal to time quantum */

			time+=p[i].rt;
			p[i].rt=0;
			p[i].completed=1;
			printf(" %d ",p[i].procno);
			p[i].wt=time-p[i].at-p[i].bt;
			p[i].tt=time-p[i].at;
		for(j=0;j<n;j++) /*enqueue the processes which have come while scheduling */
		{
			if(p[j].at<=time && p[j].completed!=1&& isInQueue(j)!=1)
			{
				enqueue(j);

			}
		}
	}
			else // more than time quantum
			{
				time+=tq;
				p[i].rt-=tq;
				printf(" %d ",p[i].procno);
                // if user input "With Overhead" then Turnaround time + Overhead time
                if (useroh ==1){
                    p[i].overhead +=2;
                }
				for(j=0;j<n;j++) /*first enqueue the processes which have come while scheduling */
				{
					if(p[j].at<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1)
					{
						enqueue(j);

					}
				}
				enqueue(i); // then enqueue the uncompleted process
			}



	}
	printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time\t Completion Time");
	for(i=0;i<n;i++)
	{
		p[i].tt += p[i].overhead;
		p[i].wt += p[i].overhead;
 		avg_wtrr+= (float)p[i].wt;
     	avg_ttrr+= (float)p[i].tt;
	printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].procno,p[i].at,p[i].bt,p[i].wt,p[i].tt,p[i].tt+p[i].at);
	}
  avg_wtrr = avg_wtrr/(float)n;
  avg_ttrr = avg_ttrr/(float)n;
	printf("\nAverage Waiting Time:%.2f\n",avg_wtrr);
    printf("\nAverage Turnaround Time:%.2f\n",avg_ttrr);

}

/*comparing average wait time and turnaround time
  of all 3 algorithms on the same workload*/
//comparison function
void compare(){
  //COMPARING WAITING TIME
if (avg_wtfcfs < avg_wtsjf && avg_wtfcfs < avg_wtrr)
{
    printf("Based on waiting time, for this current workload, FCFS is best suitable!\n");
}

else if (avg_wtsjf < avg_wtfcfs && avg_wtsjf < avg_wtrr)
{
    printf("Based on waiting time, for this current workload, SJF(non preemptive) is best suitable!\n");
}
else if (avg_wtrr < avg_wtfcfs && avg_wtrr < avg_wtsjf)
{
    printf("Based on waiting time, for this current workload, RoundRobin is best suitable!\n");
}
else if (avg_wtsjf == avg_wtfcfs && avg_wtsjf < avg_wtrr){
    printf("Based on waiting time, for this current workload, SJF(non preemptive) and FCFS is best suitable!\n");
}
else if (avg_wtsjf == avg_wtrr && avg_wtsjf < avg_wtfcfs){
   printf("Based on waiting time, for this current workload, SJF(non preemptive) and RoundRobin is best suitable\n!");
}
else if (avg_wtfcfs == avg_wtrr && avg_wtfcfs < avg_wtsjf){
   printf("Based on waiting time, for this current workload, FCFS and RoundRobin is best suitable!\n");
}
else if (avg_wtsjf == avg_wtrr && avg_wtsjf == avg_wtfcfs){
    printf("All 3 have the same average waiting time.\n All 3 are suitable for the curernt workload!\n");
}
else
printf("Invalid Comparison\n");

//COMPARING TURNAROUND TIME
if(avg_ttfcfs < avg_ttsjf && avg_ttfcfs < avg_ttrr)
{
    printf("Based on turnaround time, for this current workload, FCFS is best suitable!\n");
}

else if(avg_ttsjf < avg_ttfcfs && avg_ttsjf < avg_ttrr)
{
    printf("Based on turnaround time, for this current workload, SJF(non preemptive) is best suitable!\n");
}

else if(avg_ttrr < avg_ttfcfs && avg_ttrr < avg_ttsjf)
{
    printf("Based on turnaround time, for this current workload, RoundRobin is best suitable!\n");
}
else if (avg_ttsjf == avg_ttfcfs && avg_ttsjf < avg_ttrr){
    printf("Based on turnaround time, for this current workload, SJF(non preemptive) and FCFS is best suitable!\n");
}
else if (avg_ttsjf == avg_ttrr && avg_ttsjf <avg_ttfcfs){
   printf("Based on turnaround time, for this current workload, SJF(non preemptive) and RoundRobin is best suitable!\n");
}
else if (avg_ttfcfs == avg_ttrr && avg_ttfcfs < avg_ttsjf){
   printf("Based on turnaround time, for this current workload, FCFS and RoundRobin is best suitable!\n");
}
else if (avg_ttsjf == avg_ttrr && avg_ttsjf == avg_ttfcfs){
    printf("All 3 have the same average turnaround time.\n All 3 are suitable for the curernt workload!\n");
}
else
printf("Invalid Comparison!\n");
}
