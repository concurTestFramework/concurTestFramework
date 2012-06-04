// main.c - synchronization framework

// DO NOT MODIFY THIS FILE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "sections.h"
#include "scheduler/sched.h"
#include "util.h"

// Parameter struct
struct ThreadParam {
  int id;		// id number for thread
  int numRounds;	// number of rounds 
};

// Function prototype for initial thread function
void *threadStart(void *param);


int 
main(int argc, char *argv[])
{
  int i; 				// loop traversal variable
  int numThreads;			// number of threads to simulate
  int numRounds;			// number of rounds
  int status;				// status of pthread calls
  pthread_t *tidArray;			// array of thread ids
  struct ThreadParam *paramPtr;		// parameter pointer
  char *mode;				// mode: RANDOM | INTERACTIVE | FIFO | LIFO
  char *logLevel = "OFF";		// logLevel:  OFF | ON
  int seed = -1;

  //printf("argc=%d\n", argc);

  if ( (argc != 5) && (argc != 6)) {
    printf("Usage: concur <num-of-threads> <num-of-rounds> <mode> <log-level> <optional-seed>\n");
    exit(-1);
  }

  // Initialize variables
  numThreads = atoi(argv[1]);
  numRounds = atoi(argv[2]);
  mode = argv[3];
  tidArray = (pthread_t *) calloc(numThreads, sizeof(pthread_t));
  logLevel = argv[4];
  if (argc == 6) {
    seed = atoi(argv[5]);
  }

  // initialize global variables
  initGlobals();

  /*** Initialize scheduler ***/
  initializeScheduler(numThreads, numRounds, mode, logLevel, seed);

  // create the threads
  for (i = 0; i < numThreads; i++) {
    paramPtr = (struct ThreadParam *) malloc(sizeof(struct ThreadParam));
    paramPtr->id = i;
    paramPtr->numRounds = numRounds;
    status = pthread_create(&tidArray[i], NULL, threadStart, (void *) paramPtr);
    if (status) {
      printf("pthread_create failure\n");
      exit(-1);
    }

    /*** Add threadId to scheduler ***/
    addThread(i, &tidArray[i]);
  }

//  printf("Done creating %d threads\n", numThreads);

  // wait for the threads to finish
  for (i = 0; i < numThreads; i++) {
    status = pthread_join(tidArray[i], NULL);     
    if (status) {
      printf("pthread_join failure\n");
      exit(-1);
    }
  }

  free(tidArray);

  return 0;
}

// initial thread function
void *threadStart(void *param)
{
  int i;
  struct ThreadParam *paramPtr = (struct ThreadParam *) param;
  int id = paramPtr->id;
  int numRounds = paramPtr->numRounds;
  free(paramPtr);

  initializeThread(id);

  for (i = 0; i < numRounds; i++) {
    entrySection(id);
    criticalSection(id);
    exitSection(id);
    remainderSection(id);
  }
  setThreadCompleted(id);
  pthread_exit(NULL);
}
