#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define NUM_CHILD 7
#define CHILD_SLEEP 10
#define PARENT_SLEEP 1

struct process{
        int id;
        int exitStatus;
};

struct process table[NUM_CHILD]; // GLOBAL: Create array capable of storing all of the child id.

void terminate(){
	for(int terminated=0; terminated<NUM_CHILD; terminated++){
		if(table[terminated].id>0)
			printf("*(fun terminate)\tKilled child: %d - %d\n", table[terminated].id, kill(table[terminated].id, SIGTERM));
		else
			break;
	}
}

pid_t create_process(){ // Description of functionality below.
	// fun: Creates child process, whenever called.
	// fun: Terminates program if child process creation is unsuccessful with approperiate message.
	// fun: Sets new process to sleep for time defined in CHILD_SLEEP, after sleep completion exit child process with code 0. 
	//      Informs user about current state of child process.
	// fun: Displays child and parent process id.
	// fun: Returns child process(creation successful) id or -1(creation unsuccessful) 
	
	pid_t new_process=fork(); // Create new process and store its status.

	if(new_process<0){ // Fork returns negative value if allocation of new process was unsuccessful.
		fprintf(stderr, "*(fun create_process)\tSomething went wrong\n"); // Display Error Message. 
	}else if(new_process==0){ // 0 - is returned to child process.
		printf("*(fun create_process)\tChild Process created successfully.\n");
		printf("*(fun creatr_process)\tSleep Child - Sleep for %d sec...\n", CHILD_SLEEP); 
		// Display Creation Message.
		sleep(CHILD_SLEEP); // Set to sleep.
		printf("*(fun create_process)\tChild is awake\n"); // Display Awake Message.
		exit(0); // Exit child process with exit code 0.
	}else if(new_process>0){ // Newly created process id is returned to parent process.
		printf("*(fun create_process)\tChild ID returned to Parent Process %i, Parent Process %i\n", new_process, getpid()); 
		// Display Child and Parent process id.
	}

	return new_process; // Child process id is returned or -1
}

void children_factory(){
	// fun: creates defined children number.
	// fun: saves child id into table.
	for(int created=0; created<NUM_CHILD; created++){ // Create number of children processes defined in NUM_CHILD
		if ((table[created].id=(int)create_process())<0){ // Store Child Process inside array. Cast pid_t to int.
                	terminate(); // Terminate already created processes.
			exit(1); // Exit parent process with code 1.
		}
			
		sleep(PARENT_SLEEP); // sleep parent process for time defined in PARENT_SLEEP, before calling for new process creation.
        }
}

void synchronise(){
	// fun: awaits children processes to be terminated.
	// fun: saves exit status of each child process.
	int status; // variable holds exit status of process.

        for(int terminated=0; terminated<NUM_CHILD; terminated++){ // Wait for all children processes to terminate.
                pid_t terminatedChildId=waitpid(table[terminated].id, &status, 0); // Wait for child process with correspond id
                // to one stored in table.
                table[terminated].exitStatus=WEXITSTATUS(status); // Set&Save exit code of child process. 
                // 0 - no option, parent has to wait for child termination.
        }
}

void summary(){ 
	// fun: displays id and exit status of child process, stored in elemnt of array.
        for(int element=0; element<NUM_CHILD; element++){ // Program Summary 
                printf("\tChild %d, terminated with status: %d\n", table[element].id, table[element].exitStatus);
        }
}

int main(void){

	printf("Main:\r\tTSig process: %i\n\n", getpid()); // Display Parent Process Id

	children_factory(); // Create NUM_CHILD processes.

	synchronise(); // Wait for processes termination then carry on execution.

	if(wait(NULL)==-1) // Check whethere there is no more children processes.
		printf("\nThere is no more Children Processes.\n\nSummary:\n");
	
	summary(); // Display id and exit status of children processes.

	return 0;
}
