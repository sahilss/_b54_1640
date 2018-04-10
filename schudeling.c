#include<stdio.h>
#include<stdlib.h>

struct process{
	int name;//stores the process name as integer value 
	float burst_time;//the time the process will take in CPU
	float arrival_time;//the time when the process arrives into the queue
	float status;//tell the status of the process whether done or still not done
	//0 for 'in queue' and 1 for 'Done'
	float waiting_time;//the time proces waits to gets executed
	float turnAroundTime;//the total time taken from getting to ready queue to finnaly getting executed
	
};

void display(struct process proc[],int num){
	int i;
	printf("The input process details are as shown below\n");
	printf("Process\tBurst-time\tArrival-time\n");
	for(i=0;i<num;i++){
		printf("p%d\t%f\t%f\n",proc[i].name,proc[i].burst_time,proc[i].arrival_time);
		
	}
	printf("\n");
}

void sort(struct process proc[],int num){
	int i,j;//iterative variables
	struct process temp;//a temp variable od struct process type so swap the entire process all together
	for(i=0;i<num-1;i++)//selection sort 
    {
        for(j=i+1;j<num;j++)
        {
            if(proc[i].arrival_time>proc[j].arrival_time){
				//swap the process with lesser arrival time
                temp=proc[i];
                proc[i]=proc[j];
                proc[j]=temp;
			}
        }
        
 		/*
 		Manual part
        temp=proc[i].burst_time;
        proc[i].burst_time=proc[pos].burst_time;
        proc[pos].burst_time=temp;
 
        temp1=p[i];
        p[i]=p[pos];
        p[pos]=temp1;
        
        temp=proc[i].arrival_time;
        proc[i].arrival_time=proc[pos].arrival_time;
        proc[pos].arrival_time=temp;
        */
    }
    
    //display(proc,num);//to check if it works
}

void schedule(struct process proc[],int num,int sum){
	int i,j;
	float f,avgWaitingTime=0,avgTurnaroundTime=0;
	sort(proc,num);//sort according to the process arrival time
	printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n");
	for(f=proc[0].arrival_time;f<(float)sum;){
		float pr=-9999;//priority
		int nxt;//hold the the next process
		float temp;	
		for(i=0;i<num;i++){
			//checking if the process is already complete
			if(proc[i].arrival_time<=f && proc[i].status!=1){
				temp=(proc[i].burst_time + (f - proc[i].arrival_time)) / proc[i].burst_time;
				if(pr<temp){
					//if higher priority take it as next process
					pr=temp;
					nxt=i;
				}
			}
		}
		//modify time	
		f=proc[nxt].burst_time+f;
		//waiting time
		proc[nxt].waiting_time=f-(proc[nxt].arrival_time)-(proc[nxt].burst_time);
		//Turn around time
		proc[nxt].turnAroundTime=f-proc[nxt].arrival_time;
		//average waiting time
		avgWaitingTime+=proc[nxt].waiting_time;
		//average turn around time
		avgTurnaroundTime+=proc[nxt].turnAroundTime;
		//update status
		proc[nxt].status=1;
		
		printf("p%d\t%f\t%f",proc[nxt].name,proc[nxt].burst_time,proc[nxt].arrival_time);
		printf("\t%f\t%f\n",proc[nxt].waiting_time,proc[nxt].turnAroundTime);
		
	}
	printf("Average waiting time=%f\n",avgWaitingTime/num);
	printf("Average turn-around time=%f\n",avgTurnaroundTime/num);
	
}

int main(){
	int i;//loop variable
	float arrival,burst,sum=0;
	static int num;//holds number of process
	struct process proc[10];//array of struct to hold multiple propeties of a single process

	printf("Enter the number of process:");
	scanf("%d",&num);
	
	printf("\nNow, enter the data for the %d processes:\n",num);

	//inputting the arrival time and burst time from the user.
	for(i=0;i<num;i++){
		
		proc[i].name=i+1;
		printf("Process p%d\n",proc[i].name);
		
		printf("Burst time:");
		scanf("%f",&burst);
		proc[i].burst_time=burst;
		
		printf("Arrival time:");
		scanf("%f",&arrival);
		proc[i].arrival_time=arrival;
		
		proc[i].status=0;
		sum+=proc[i].burst_time;

		printf("\n");
	} 	
	//output the input pricess details
	display(proc,num);
	
	//sort acc to arrival time
	sort(proc,num);
	
	//schedule
	schedule(proc,num,sum);
	
}
