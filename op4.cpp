#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10	 //number of page
#define M 1000	 // size of page : 1000 data/page
				
struct VPage   //Page massege
{	
	int pageNum;	//the page number	
	int cometime;		//al FIFO
	int accesstime;		//al URL
	int ubit;			// al CLOCK u
}PAGE[N];

void initPage(VPage PAGE[N]){	
	for(int i=0;i<N;i++){ 		//every page		
		PAGE[i].pageNum = -1;
		PAGE[i].cometime = -1;
		PAGE[i].accesstime = -1;
		PAGE[i].ubit = 0;	//usebit
	}
}
void showPage(VPage PAGE[N]){	
	printf("Show Page\n");
	for(int i=0;i<N;i++){ 		//every page
		printf("ubit:%d ",PAGE[i].ubit);	
		printf("pageNum:%d ",PAGE[i].pageNum);	
		printf("cometime:%d ",PAGE[i].cometime);	
		printf("accesstime:%d \n",PAGE[i].accesstime);		
	}
}
void FIFO(VPage PAGE[N]){
	//printf("FIFO-------------------------------------\n");	
	struct 	VPage temp;	
	//sort VPage according to cometime,and chose min cometime	
	for(int i=0;i<N;i++){
		for(int j=0;j<N-i;j++){
			if(PAGE[j].cometime > PAGE[j+1].cometime){	// > change; P0 is min
				temp = PAGE[j];
				PAGE[j] = PAGE[j+1];
				PAGE[j+1] = temp;
			}
		}	
	}
}

void URL(VPage PAGE[N]){
	//printf("URL--------------------------------------\n");
	struct 	VPage temp;	
	//sort VPage according to cometime,and chose min cometime	
	for(int i=0;i<N;i++){
		for(int j=0;j<N-i;j++){
			if(PAGE[j].accesstime > PAGE[j+1].accesstime){	// > change; P0 is min,is far
				temp = PAGE[j];
				PAGE[j] = PAGE[j+1];
				PAGE[j+1] = temp;
			}
		}	
	}
}
void CLOCK(VPage PAGE[N]){
	//printf("CLOCK------------------------------------\n");
	struct VPage temp;
	int repeat = 1;
	while(repeat){
		for(int i=0;i<N;i++){
			if(PAGE[i].ubit == 0){
				temp = PAGE[0];
				PAGE[0] = PAGE[i];
				PAGE[i] = temp;
				repeat = 0;
				break;
			}
			else{
				PAGE[i].ubit = 0;
			}
		}	
	}
	for(int j=1;j<N;j++){
		PAGE[j].ubit = 1;
	}
}
int main(){
	printf("Algorithm: CLOCK \n");
	printf("Page: 1000 \n");
	int pageNumber;
	int flag;
	int flagMiss;
	int fifotime;
	int urltime;
	int cout,hitcout;
	float misscout;
	float missRate;
 	char fileName[6][15] = {"workload7.txt","workload8.txt","workload9.txt","workload10.txt","workload11.txt","workload12.txt"};		
	struct VPage PAGE[N];	
	//printf("%d\n",PAGE[0].pageNum);
	for(int file=0;file<6;file++){
		printf("%s \n",fileName[file]);
		//initPage(PAGE);
		//open file   and    read   data

		for(int l=0;l<N;l++){ 		//every page		
			PAGE[l].pageNum = -1;
			PAGE[l].cometime = -1;
			PAGE[l].accesstime = -1;
			PAGE[l].ubit = 0;	//usebit
		}

		fifotime = 0;
		urltime = 0;
		cout = hitcout = 0;
		misscout = 0.0;
		missRate = 0.0;

		FILE* fp;	
		if((fp=fopen(fileName[file],"r")) == NULL){
			printf("can not open file\n");
			return -1;
		}
			//read file data
		while(!feof(fp)){		//every data					
			flag = 0;
			flagMiss = 1;
				
			fscanf(fp,"%d",&pageNumber);	// get a data 
			urltime = urltime + 1;		//if read data,will access page, time forword
			//printf("access: %d ",pageNumber);//output access
			pageNumber = pageNumber/M; 	// cout data page number
			//printf("Page:%d ",pageNumber);	//output page
											//will change accesstime
			for(int i=0;i<N;i++){		//compare with every pageNum			
				if(PAGE[i].ubit==1 && PAGE[i].pageNum==pageNumber){//hit
					//printf("Hit! \n");
					PAGE[i].accesstime = urltime;
					PAGE[i].ubit = 1; //set ubit
					flag = 1;
					hitcout = hitcout + 1;
					break;
				}
						
			}
			if(flag == 0){		//miss 
				//printf("Miss... ");
				misscout = misscout + 1;
				fifotime = fifotime + 1;	//if miss,new page will come,time forword( time+1 )
												//because miss will change page,and change cometime
				for(int j=0;j<N;j++){
	// miss :update PAGE
					if(PAGE[j].ubit == 0){//exit empty page
						//printf("Have empty page!\n");
						PAGE[j].pageNum = pageNumber;
						PAGE[j].ubit = 1;
						PAGE[j].cometime = fifotime;
						PAGE[j].accesstime = urltime;
						flagMiss = 0;
						break;	//jump out "for"
					}
				}
					 //no exit empty page,will change
				if(flagMiss == 1){
					//printf("No empty page...\n ");
					//FIFO(PAGE);
					URL(PAGE);
					//CLOCK(PAGE);
					PAGE[0].pageNum = pageNumber;
					PAGE[0].cometime = fifotime;
					PAGE[0].accesstime = urltime;
					PAGE[0].ubit = 1;
					//	showPage(PAGE);
						
				}				
			}		
			cout = cout + 1;	//sum of data	
		}	
		missRate = misscout/(hitcout+misscout);
		printf("Miss rate: %f\n\n",missRate);				
		fclose(fp);
		//showPage(PAGE);
	}			
	return 0;
}



