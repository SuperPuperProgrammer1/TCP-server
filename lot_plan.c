#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int jobs, max_tic, work_time, quant, OK_status,help_status, last_proc, counter, rand_tic, num;
int counter = 0;
int alive_proc = 0;
int quant = 10;
int last_proc = 0;
int OK_status = 0;
int help_status = 0;
int main(void){
	printf("Enter count of jobs: ");
	scanf("%d", &jobs);
	alive_proc = jobs;
	printf("\n");
	printf("Now, enter max tickets: ");
	scanf("%d", &max_tic);
	printf("\n");
	int proc[jobs];
	int proc_time[jobs];
	int proc_status[jobs];
	int proc_worked_time[jobs];
	for(int i = 0; i <jobs; i++){
		proc_status[i]=0;
		proc_worked_time[i]=0;
	}
	for(int i = 0; i < jobs-1; i++){
	        printf("Enter %d job's count of tickets: ", i);
	        scanf("%d", &num);
		printf("\n");
		printf("Enter %d job's work time: ", i);
		scanf("%d", &work_time);
		printf("\n");
		last_proc+=num;
		proc[i]=last_proc;
		proc_time[i]=work_time;
		proc_status[i]=0;
		 
	}
	printf("\n");
	printf("Enter %d job's work time: ", jobs-1);
	scanf("%d", &proc_time[jobs-1]);
	printf("\n");
	proc[jobs-1] = max_tic;
	printf("We did %d job's count of tickets: %d", jobs-1, proc[jobs-1]-last_proc);
	printf("\n");
	while(OK_status==0){
		rand_tic = rand()%max_tic+1;
	        printf("The won ticket is: %d", rand_tic);
	  	printf("\n");
		for(int i = 0; i<jobs; i++){
			for(int c = 0; c <jobs+1; c++){
				if(help_status==jobs){
					OK_status=1;
					c=jobs+1;
				}
				if(proc_status[c]==1){
					help_status+=1;
					break;
				}
				else{
					c=jobs+1;
				}
			}

			if(proc[i]>=rand_tic){
				if(proc_status[i]==1){
					break;
				}
				printf("Won job %d, %d in first %d tickets\n", i, rand_tic, proc[i]);
				for(int b = 1; b < quant+1; b++){
					proc_worked_time[i] += 1; 
					printf("JOB %d NOW IN PROCESS :::::::::::::::::|| %d of %d ||:\n", i, proc_worked_time[i], proc_time[i]);
					if(proc_worked_time[i]==proc_time[i]){
						printf("JOB %d DONE!", i);
						proc_status[i]=1;
						alive_proc-=1;
						b = quant+2;
						int min_tic = 0;
						if(alive_proc!=0){
							 printf("Proc[%d] ==== %d", i, proc[i]);
							 min_tic = floor(proc[i]/alive_proc);
							 max_tic-=min_tic;
						}
						else{
							b = quant+2;
							break;
						}
						proc[i]=0;
						for(int d = 0; d < jobs; d++){
							if(d==i){ continue; }
							else{
								proc[d]+=min_tic;
							}
						}

					}	
					
				}
			}       
		}
	}	


}	

