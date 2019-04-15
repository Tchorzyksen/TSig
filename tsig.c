#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

pid_t create_process(){

	pid_t new_process=fork();

	if(new_process<0)
		printf("*(fun)\r\tSomething went wrong\n");
	else if(new_process==0){
		printf("*(fun)\r\tSleep %i - Wait for 10\'\'...\n", new_process);
		sleep(10);
		printf("*(fun)\r\tChild is awake\n");
		exit(0);
	}else if(new_process>0){
		printf("*(fun)\r\tChild ID returned to Parent Process %i - %i\n", new_process, getpid());
	}

	return new_process;
}

int main(void){

	printf("Main:\r\tTSig process: %i\n\n", getpid());
	int processIdTable[2];
	
	processIdTable[0]=(int)create_process();
	sleep(2);
	processIdTable[1]=(int)create_process();
	sleep(2);

	printf("\n---------------------------------------------------------------------------------------------\n");
	printf("1.\r\tReturned value is %i\n\r\tChild process %i was terminated.\n", processIdTable[0], wait(NULL));
	printf("\n---------------------------------------------------------------------------------------------\n");
	printf("2.\r\tReturned value is %i\n\r\tChild process %i was terminated.\n", processIdTable[1], wait(NULL));
	printf("\n---------------------------------------------------------------------------------------------\n");

	
	return 0;
}
