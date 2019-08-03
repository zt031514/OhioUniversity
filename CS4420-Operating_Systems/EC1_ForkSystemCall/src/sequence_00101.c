//CS4420 in-class exercise extra credit
//Produces sequence 00101

#include<stdio.h>

int main(){
	int flag = 0;
	const int WAIT_TIME = 1; // wait 10 ms
	int d,e;
	int f,g;
	d = fork(); // fork 1
	if(d == 0){
		e = fork(); // fork 2
		if(e > 0)
			sleep(WAIT_TIME);
		if( e > 0 ){
			f = fork(); //fork 3
			if(f > 0 )
				sleep(WAIT_TIME);
		}
	}		
	else
		fork();	// fork4
	 
	if( wait(NULL) > 0)
		flag = 1;
	
	printf("%d  ", flag);
	sleep(WAIT_TIME);
	return(0);
}