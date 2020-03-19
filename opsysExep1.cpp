#include<stdio.h> 
#include<sys/types.h>  //defind pid t
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
#include<stdlib.h>

void *Thread1(void* arg){
	printf("This is thread1 of process4,fuction:Prime number\n");	
	
	int n = 0;	
	printf( "Enter a value :");
    	scanf("%d", &n);
    	int a = 0;
    	for(int i = 2; i < n; i++){
        	if(n%i == 0){
            		a++;  
        	}
    	}
    	if(a==0){
        	printf("%dis Prime number\n", n);
    	}else{
        	printf("%dnot Prime number\n", n);
    	}
	
}

int Fibonacci(int n)
{	int N = 10007;
	int Fn;
	if (n==1 || n==2)
	{
		Fn=1;
	}
	else
	{
		Fn = (Fibonacci(n-1) + Fibonacci(n-2))%N;
	}
	return Fn;
}
void *Thread2(void* arg){
	printf("This is thread2 of process4,fuction:Fibonacci\n");	
	
	int n = 0;
	printf( "Enter a value :");
    	scanf("%d", &n);
    	int result;
    	result = Fibonacci(n);
    	printf("result = %d \n", result);
	
}

int process4(){
	printf("This is process4,fuction:Create 2 pthread\n");	
	
	pthread_t mthread1, mthread2;
	mthread1 = pthread_create(&mthread1,NULL,Thread1,NULL);
	if(mthread1 != 0){
		printf("Error happened in thread_create function\n");
		return 1;
	}
	else( mthread1 == 0 );{
		printf("create success\n");
		
	}	
	mthread2 = pthread_create(&mthread2,NULL,Thread2,NULL);
	if(mthread2 != 0){
		printf("Error happened in thread_create function\n");
		return 1;
	}
	else( mthread2 == 0 );{
		printf("create success\n");
		
	}
	
	pthread_join(mthread1, NULL);
	pthread_join(mthread2, NULL);
	printf("main thread exit!\n");
	return 0;
	
}

void process5(){
	printf("This is process5,fuction:exe\n");
	printf("Hello world\n");

}

void process2(){
	printf("This is process2,fuction:system commend\n");	
	system("ls");
	system("ps");
	system("free");
}

void fun(int i)
{
	switch(i)
	{
		case 4: process4();
			break;
		case 5: process5(); //printf hello world
			break;
	}
	_exit(0);

}

int process3(){
	printf("This is process3,fuction:create process4 and process5\n");
	
	for(int i = 4; i <= 5; i++){
		pid_t child;
		child = fork();
		if(child == -1){
			printf("Error happened in fork function\n");
			return 0;
		}
		else if( child == 0 ){
			printf("create success\n");
			fun(i);
		}			
	}
	for (int j = 0; j < 2;j++)
	{
		pid_t cpid = wait(NULL);
		printf("the process % d exit \n", cpid);
	}
	//parent process exit
	printf("The no.1 parent process ID is %d exit\n", getpid());
	return 0;
	
}

void childfun(int i){
	switch(i){
		case 2 : process2();
		case 3 : process3();
		
	}
	_exit(0);
}

int Createprocess(){
	printf("Will Create processes...\n");

	for(int i = 2; i <= 3; i++){
		pid_t child;
		child = fork();
		if(child == -1){
			printf("Error happened in fork function\n");
			return 0;
		}
		else if( child == 0 ){
			printf("create success\n");
			childfun(i);
		}			
	}
	for (int j = 0; j < 2;j++)
	{
		pid_t cpid = wait(NULL);
		printf("the process % d exit \n", cpid);
	}
	//parent process exit
	printf("The no.1 parent process ID is %d exit\n", getpid());
	return 0;
}

//main fuction
int main(){
	Createprocess();
	return 0;
}
