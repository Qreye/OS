#include<stdio.h>
#include<sys/types.h>  //defind pid t
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
#include<stdlib.h>

struct VirtualPCB
{
	int id;
	int priority;	
	int arrivetime;	
	int runtime; 
	int rtime;
	//int waitingtime;
	//VirtualPCB *next;
}PCBs[20];
void sort(int a[20]){
	int i,j,temp;
	for(i=0;i<20;i++){
		for(j=0;j<20-1-i;j++){
			if(a[j] > a[j+1]){
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}	
	}
	for(int k=0; k<20; k++){
		printf("%d ",a[k]);
	}
}
void handleFCFS(VirtualPCB PCBs[20]){
	printf("FCFS Scheduling--------------------------------------------\n");
	struct 	VirtualPCB temp;
	for(int i=1;i<=20;i++){
		for(int j=1;j<=20-i;j++){
			if(PCBs[j].arrivetime > PCBs[j+1].arrivetime){
				temp = PCBs[j];
				PCBs[j] = PCBs[j+1];
				PCBs[j+1] = temp;
			}
		}	
	}		
	printf("The turns of threadPCB and cputime:\n");
	int time=0;
	int cputime;
	int waitingtime=0;
	int awtime;
	for(int k=1;k<=20;k++){
		time = time + PCBs[k].runtime;
		printf("Thread%d : %d \n",PCBs[k].id,time);
		waitingtime = waitingtime + (time - PCBs[k].arrivetime);
	}	
	awtime = waitingtime/20;
	printf("The average waitingtime: %d\n",awtime);
	printf("\n");
}

void handleSJF(VirtualPCB PCBs[20]){
	printf("SJF Scheduling---------------------------------------------\n");
	struct 	VirtualPCB temp;
	for(int i=1;i<=20;i++){
		for(int j=1;j<=20-i;j++){
			if(PCBs[j].runtime > PCBs[j+1].runtime){
				temp = PCBs[j];
				PCBs[j] = PCBs[j+1];
				PCBs[j+1] = temp;
			}
		}	
	}		
	printf("The turns of threadPCB and cputime:\n");
	int time=0;
	int cputime;
	int waitingtime=0;
	int awtime;
	for(int k=1;k<=20;k++){
		time = time + PCBs[k].runtime;
		printf("Thread%d : %d \n",PCBs[k].id,time);
		waitingtime = waitingtime + (time - PCBs[k].arrivetime);
	}	
	awtime = waitingtime/20;
	printf("The average waitingtime: %d\n",awtime);
	printf("\n");
}

void handlePriority(VirtualPCB PCBs[20]){
	printf("Priority Scheduling----------------------------------------\n");
	struct 	VirtualPCB temp;
	for(int i=1;i<=20;i++){
		for(int j=1;j<=20-i;j++){
			if(PCBs[j].priority > PCBs[j+1].priority){
				temp = PCBs[j];
				PCBs[j] = PCBs[j+1];
				PCBs[j+1] = temp;
			}
		}	
	}	
	printf("The turns of threadPCB and cputime:\n");
	int time=0;
	int cputime;
	int waitingtime=0;
	int awtime;
	for(int k=1;k<=20;k++){
		time = time + PCBs[k].runtime;
		printf("Thread%d : %d \n",PCBs[k].id,time);
		waitingtime = waitingtime + (time - PCBs[k].arrivetime);
	}	
	awtime = waitingtime/20;
	printf("The average waitingtime: %d\n",awtime);
	printf("\n");
}
void handleRR(VirtualPCB PCBs[20],int r){
	printf("RR Scheduling----------------------------------------------\n");
	struct 	VirtualPCB temp;
	struct VirtualPCB rPCBs[20];
	printf("The turns of threadPCB and cputime:\n");	
	int time=0;  //time line,will output
	int cputime;
	int waitingtime=0;  //time -
	int awtime;	
	for(int i=1;i<=20;i++){
		for(int j=1;j<=20-i;j++){
			if(PCBs[j].arrivetime > PCBs[j+1].arrivetime){
				temp = PCBs[j];
				PCBs[j] = PCBs[j+1];
				PCBs[j+1] = temp;
			}
		}	
	}
	for(int b=1;b<=20;b++){
		rPCBs[b].id = PCBs[b].id;
		rPCBs[b].priority = PCBs[b].priority;
		rPCBs[b].arrivetime = PCBs[b].arrivetime;
		rPCBs[b].runtime = PCBs[b].runtime;
		rPCBs[b].rtime = rPCBs[b].runtime;
	}
	int cnt=20;
	while(cnt){
	for(int k=1;k<=cnt;k++){
		if(rPCBs[k].rtime < r){	
			time = time + rPCBs[k].rtime;
			rPCBs[k].rtime = 0;
			printf("Thread%d : %d \n",rPCBs[k].id,time);
			waitingtime = waitingtime + (time - rPCBs[k].arrivetime);
			//update rPCB 
			for(int a=1;a<=cnt;a++){
				if(a<k){
					rPCBs[k] = rPCBs[k];
				}
				else{
					rPCBs[k] = rPCBs[k+1];
				}
			}
			cnt = cnt - 1;
		}
		else{		
			time = time + r;
			rPCBs[k].rtime = rPCBs[k].rtime - r;	 	
			printf("Thread%d : %d \n",rPCBs[k].id,time);
			waitingtime=waitingtime+(time-(rPCBs[k-1].arrivetime+r));
		}	
	}
	}
	awtime = waitingtime/20;
	printf("The average waitingtime: %d\n",awtime);
	printf("\n");	

}
void *Children(void* arg){
	//printf("The first Thread was created\n");
}
int main(){
	int ret1;
	int arrive[20];
	struct VirtualPCB PCBs[20];
	//create main_pthread 
	pthread_t tid1;
	ret1 = pthread_create(&tid1,NULL,&Children,NULL);
	if(ret1 == 0)
	{
		//creating child threads
		sleep(2);
		//create child pthread-init PCB,output starttime
		printf("Will Create child pthreads and PCB...\n");
		for(int i = 1; i <= 20; i++){	
					
			pid_t child;
			child = fork();		
			if(child == -1){
				printf("Error happened in fork function\n");
				return 0;
			}
			else if( child == 0 ){				
				//initPCB(PCBs[i],i,arrive);
	printf("Thread %d PCB__",i);
	PCBs[i].id = i;
	PCBs[i].arrivetime = rand() % 10; 
	PCBs[i].runtime = rand() % 10 + 1;
	PCBs[i].rtime = PCBs[i].runtime;
	if(i <= 4){
		PCBs[i].priority = 1;
	}
	else if(4 < i && i <= 8){
		PCBs[i].priority = 2;
	}
	else if(8 < i && i <= 12){
		PCBs[i].priority = 3;
	}
	else if(12 < i && i <= 16){
		PCBs[i].priority = 4;
	}
	else{
		PCBs[i].priority = 5;
	}

	//output the massege of thread PCB
	printf("id:%d__",PCBs[i].id);
	printf("priority:%d__",PCBs[i].priority);
	printf("arrivetime:%d__",PCBs[i].arrivetime);
	printf("runtime:%d\n",PCBs[i].runtime);
	arrive[i] = PCBs[i].arrivetime;	

			}
			pthread_join(child,NULL);	
		}		
	}
	else{
		printf("Create Main Thread failed!\n");
	}
	pthread_join(tid1,NULL);
	int cputime = 0;
//child pthread scheduling use different al,count the time
	handleFCFS(PCBs);	
	handleSJF(PCBs);
	handlePriority(PCBs);
	printf("RR time is 5 \n");
	int rr = 5;			//get RR time
	//scanf("%d", &rr);
	handleRR(PCBs,rr);
	return 0;
}





