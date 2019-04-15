# TSig

Project Two for EOPSY classes at WUT.

Overwiev
Program creates children processes, number of which is defined as NUM_CHILD. Delay between consecutive creation request is defined as PARENT_SLEEP.
If creation of child process is unsuccessful, terminate already existing processes(SIGTERM signal) and exit program with code 1.
Newly created processes are set to sleep for time defined as CHILD_SLEEP. After \'nap\' children are terminated with exit code 0. Parent process awaits(synchronise) termination of created children and saves its id and exit status.
Then summary is displayed(id and exit status of each created process during run-time).

Author Michal Tchorzewski
