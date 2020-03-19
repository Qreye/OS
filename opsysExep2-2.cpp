#include<stdio.h> 
#include<sys/types.h>  //defind pid t
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/ipc.h>

typedef struct mymsg //msg stru
{
	long mytype;	//define msg stru
	char mytext[128];
}mymsg;
void sendmsg(int msqid, mymsg msg){
	//write msg into queue	
	printf("-------------------send msg------------------------------\n");
	strcat(msg.mytext,"ok");
	if((msgsnd(msqid, msg.mytext, sizeof(msg.mytext), IPC_NOWAIT)) != 0)//send msg
	{		
		printf("msg cannot sent.\n");//if cannot sent
	}
	else
	{
		printf("msg suceess sent.\n");//if can sent
	}
} 
int getqid()//create queue
{
	key_t key = ftok(".", 't');//create key,get key
	//create msg q
	int msqid = msgget(key, 0666 | IPC_CREAT);// q id
}
int writetofile(){
//open file write
	FILE *fp;
	fp=fopen("2.txt","w");
	if(fp==NULL){ // no file,crete file
		printf("cannot create file\n");
		return 1;
	}
	fprintf(fp,"data:123456");
	printf("Have writen data\n");
}
int readfromfile(char *buffer){
//open file read file
	char str[128];
	if(buffer[0]=='o' && buffer[1]=='k'){
		FILE *fp1;
		fp1=fopen("2.txt","r");
		if(fp1 == NULL){ 
			printf("cannot create file\n");
			return 0;
		}
		//print data
		printf("Print the data in file: \n");
		while(!feof(fp1)){
			if(fgets(str,128,fp1)!= NULL)
			printf("%s",str);
		}
  	  	printf("\n");						
		fclose(fp1);
	}
}
int main(){
	int msqid = getqid();//create msg queue
	//create process1
	struct mymsg msg;
	pid_t child1;
	child1 = fork();
	if(child1 == -1){
		printf("Error happened in fork function\n");
		return 0;
	}
	else if( child1 == 0 ){ //file write data send msg
//process1	
		printf("process1,will open file and write...\n");
		writetofile();	
		sendmsg(msqid, msg); //send msg
	}
	pid_t cpid1 = wait(NULL);

	pid_t child2;
	child2 = fork();
	if(child2 == -1){
		printf("Error happened in fork function\n");
		return 0;
	}
	else if( child2 == 0 ){
//process2
		printf("process2,will open file and read...\n");
		int rec = msgrcv(msqid,msg.mytext,sizeof(msg.mytext),msg.mytype,IPC_NOWAIT);
		if( rec != -1 ) //recive msg,try to open file
		{
			printf("-------------------receive msg-------------------\n");
			readfromfile(msg.mytext);//printf it
		}
	}	
	pid_t cpid2 = wait(NULL);
	return 0;	
} 
