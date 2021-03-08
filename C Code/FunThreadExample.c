/*
This program gives an example of how threads are created and executed.
To compile: gcc -pthread FunThreadExample.c
To run: ./a.out
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//define constant NUMBERTHREADS as 10
#define NUMBERTHREADS 10

void * printworld(void * tid)
{
	int status;
	/* This function prints the thread’s identifier and then exits. */
	printf("Hello World. Greetings from thread %d\n", tid);

	/*create a bash command to run*/
	char command[50];
	//sprintf(command, "ps 'aux' | grep 'mtcummins' >> processesowned.txt");
	printf("       __           __\n");
	printf("      / / _       _ \\ \\\n");
	printf("     | |_//       \\""\\_| |\n");
	printf("     |  _/ (O) (O) \\_  |\n");
	printf("     | |  __|___|__  | |\n");
	printf("      \\ \\/         \\/ /\n");
	printf("       \\|           |/\n");
	printf("         \\_________/\n");
	printf("        ////     \\""\\""\\""\\""\n");
	printf("        \\""\\""\\""\\     ////\n");
	printf("Bow Down To the Crab Over Loards!\n");

	/*run the command*/
	status = system(command);

	/*print a farewell message*/
	printf("Bye World from thread %d\n", tid);
	pthread_exit(NULL);
}

int main(int argc, char * argv[])
{
/* The main program creates 10 threads and then exits. */
	pthread_t threads[NUMBERTHREADS];
	int status, i;
	//count through 10 threads
	for(i=0; i < NUMBERTHREADS; i++) {
		//run main thread
		printf("Main here. Creating thread %d\n", i);
		//create 10 threads
		status = pthread_create(&threads[i], NULL, printworld, (void *)i);
		//check for errors with creating threads
		if (status != 0) {
			printf("Oops. pthread create returned error code %d\n", status);
			exit(-1);
		}
	}
	for (i = 0; i < NUMBERTHREADS; i++){
		pthread_join(threads[i],NULL);
	}
	
	exit(0);
}
