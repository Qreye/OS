#include<stdio.h> 
#include<sys/types.h>  //defind pid t
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
int main(int argc, char const *argv[]){
	int fd[2],nbytes;
	char readbuffer[200];
	
	pipe(fd);           //create the pipe
	int w_fd=fd[1];      //write
	int r_fd=fd[0];      //read
	printf("Will Create processes...\n");
	pid_t child1;		
	child1=fork();	
	if(child1 == -1){
		printf("Error happened in fork function\n");
		return 0;
	}
	else if( child1 == 0 ){//child 1 will read the file
		printf("process1 create successed\n");	
		printf("----------------------------write-----------------\n");
//process1  
		FILE *fp;
		fp=fopen("1.txt","w");
		if(fp==NULL){ // no file,crete file
			printf("cannot create file");
			return 1;
		}
		fprintf(fp,"data:123456");
		printf("Have writen data\n");	
		close(r_fd);			
		write(w_fd,"ok",2);//send 'ok'	
		fclose(fp);	
		_exit(0);
	}			
	pid_t cpid1 = wait(NULL);			
	printf("------------wirte---------------read-----------------\n");
	pid_t child2;
	child2=fork();
	if(child2 == -1){
		printf("Error happened in fork function\n");
		return 0;
	}
	else if( child2 == 0 ){
		printf("process2 create success\n");
		//child 2 will read the file		
//process2
		char str[128];
		nbytes = read(r_fd,readbuffer,sizeof(readbuffer));		
		printf("readbuffer:%s \n\n",readbuffer);
		printf("----------------can read data in file--------------\n");
		if(readbuffer[0]=='o' && readbuffer[1]=='k') 
		{
			FILE *fp1;
			fp1=fopen("1.txt","r");
			if(fp1 == NULL){ 
				printf("cannot create file");
				return 0;
			}
			//print data
			printf("data in file: \n");

			while(!feof(fp1)){
				if(fgets(str,128,fp1)!= NULL)
					printf("%s",str);
			}
    			printf("\n");						
			fclose(fp1);
		}
		_exit(0);
	}			
	pid_t cpid2 = wait(NULL);
	printf("\n");
	printf("the process % d exit \n", cpid2);	
	//parent process exit
	printf("the process % d exit \n", cpid1);		
	printf("The no.1 parent process ID is %d exit\n", getpid());	
	printf("\n\n-----------------------------------------------------\n\n");
	return 0;
}

