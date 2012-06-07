//  sched.cpp : Scheduler for synchronization problems

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <errno.h> 
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
    
#include "logger.h"
#include "typeUtils.h"
#include "utilities.h"
using namespace std;


// collections
const int MAX_THREADS = 50;
const int MAX_LOCKS = 10;
const int MAX_SEMS = 10;
int roundsCount = 0;
int threadCount = 0;
int lockCount = 0;
int semCount = 0;
Thread *threadArray;	// array of threads
Lock *lockArray;	// array of locks
Semaphore *semArray;	// array of semaphores

// for initialization
bool inInitialization = true;
sem_t semInitialBlock;
int numAddedThreads = 0;
int initialThread = -1; // thread to stay awake during initialization while all other threads go to sleep
bool allThreadsAdded = false;

bool tracing = false;

unsigned int seed = -1;
int numReadyThreads = 0;
ThreadNode* readyThreadsHead = NULL;
int numThreadsCompleted = 0;
sigset_t sigSet;
SchedulerMode schedMode = LIFO;

// locks
pthread_mutex_t printOutMutex;
pthread_mutex_t numReadyThreadsLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t readyThreadsCondVar = PTHREAD_COND_INITIALIZER;


// Mutator functions
  // Initialization
extern "C" void setSchedulerMode();
void setSchedulerMode(char* mode);
extern "C" void initializeScheduler(int numThreads, int numRounds, char* mode, char* logLevel, int seed);
extern "C" void initializeThread(int id);
extern "C" void setNumThreads(int numThreads);
extern "C" void addThread(int id, pthread_t &thread);
extern "C" void addLock(char *name, pthread_mutex_t &lock);
extern "C" void addSemaphore(char *name, int initial, sem_t &semaphore);
extern "C" void setThreadCompleted(int threadIndex);
void initializeSeed(int userSeed);
  // Thread 
extern "C" void invokeScheduler(int id, int lineNum);
extern "C" void pauseThread(int id);
  // Lock 
extern "C" void mutexLock(int id, pthread_mutex_t &lock);
extern "C" void mutexUnlock(int id, pthread_mutex_t &lock);
  // Semaphore
extern "C" void semWait(int id, sem_t &sem);
extern "C" void semPost(int id, sem_t &sem);

// Accessor functions
  // Status
extern "C" void printStatus();
void logStatusToFile();
string getThreadStatus();
string getLockStatus();
string getSemaphoreStatus();
int getReadyThreadIndex(SchedulerMode schedMode, int min, int max);
int getCurrentThreadId();
string getThreadList(int count, Thread* threads);
Lock* getLock(pthread_mutex_t &lock);
Semaphore* getSemaphore(sem_t &ptSem);
bool allThreadsCompleted();
void log(string message);

/******************************************************************************************************
 *                      MUTATOR FUNCTIONS
 *****************************************************************************************************/

/*
 * 
 *
 */
extern "C" void initializeScheduler(int numThreads, int numRounds, char* mode, char* logLevel, int runSeed) {  
  roundsCount = numRounds;
  setNumThreads(numThreads);
  setSchedulerMode(mode);
  initializeLogging(logLevel);
  initializeSeed(runSeed);

  stringstream ss;
  ss << "  -- numThreads=" << threadCount << ", numRounds=" << roundsCount << ", schedMode=" << getModeString(schedMode) << ", logMode=" << getLogModeString().c_str() << ", seed=" << intToStr( (schedMode == RANDOM) ? seed : -1);
  const char* initMsg = ss.str().c_str();
  printf("%s\n", initMsg);
  logToFile(initMsg);
}

/*
* Set scheduler mode
*/
void setSchedulerMode(char* mode) {
  stringstream ss;
  ss << mode;
  string modeStr = ss.str();
  stoupper(modeStr); // convert to all caps
  const char* modeUpper = modeStr.c_str();
  if ( strcmp(modeUpper, "RANDOM") == 0 ) {
    schedMode = RANDOM;
  } else if ( strcmp(modeUpper, "INTERACTIVE") == 0 ) {
    schedMode = INTERACTIVE;
  } else if ( strcmp( modeUpper, "FIFO") == 0 ) {
    schedMode = FIFO;
  } else if ( strcmp(modeUpper, "LIFO") == 0 ) {
    schedMode = LIFO;
  } else { //this should never happen
    printf("Error:  received an invalid scheduler mode choice: %d\n", mode);
    exit(EXIT_FAILURE); 
  }
  
  if (tracing) {
    printf("Setting Scheduler Mode to %s\n", mode);
  }
}

/*
* Sets seed for running in RANDOM mode.
*/
void initializeSeed(int userSeed) {
  if (tracing) {
    printf("-  sched.initializeSeed:  userSeed=%d\n", userSeed);
  }

  if (schedMode == RANDOM) {
    if (userSeed > 0) {
      seed = userSeed;
    } else {
      seed = time(NULL);
      srand( seed );
   }
  } else {
    // don't set seed for any mode other than RANDOM
  }

  if (tracing) {
    printf("-  sched.initializeSeed:  seed=%d\n", seed);
  }
}

/*
 *
 */
extern "C" void setNumThreads(int numThreads) {
  if(numThreads > MAX_THREADS) {
    pthread_mutex_lock(&printOutMutex);
    printf("Entered more than allowed number of threads.  max=%d, entered:%d", MAX_THREADS, numThreads);
    pthread_mutex_unlock(&printOutMutex);
    exit(-1);
  }
  threadCount = numThreads;
  if (tracing) {
    printf("Setting threadCount to %d\n", threadCount);
  }
  threadArray = (struct Thread*) calloc(threadCount, sizeof(struct Thread));
}

/*
 * Adds a new thread to the thread collection.
 * Assume id = [0, numThreads-1];
 */
extern "C" void addThread(int id, pthread_t &thread) {
  //printf("sched.addThread - id=%d\n",id);

  threadArray[id].id = id;
  threadArray[id].threadId = thread;
  threadArray[id].status = UNKNOWN;
  threadArray[id].waitingName = "";
  numAddedThreads++;

  if (tracing) {
    printf("numAddedThreads=%d, threadCount=%d\n", numAddedThreads, threadCount);
  }

  if (numAddedThreads == threadCount) {
    // for thread initialization
    int index = getReadyThreadIndex(LIFO, 0, threadCount);
    initialThread = threadArray[index].id;
    sem_init(&semInitialBlock, 0, 0);
    allThreadsAdded = true;
    if (tracing) {
      printf("index=%d, initialThread=%d\n", index, initialThread);
    }
  }
}

extern "C" void addLock(char name[], pthread_mutex_t &lock) {
  //printf("sched - addLock");

  // initalize lock collection if not already done so
  if (lockCount == 0) {
    lockArray = (Lock*) calloc(MAX_LOCKS, sizeof(Lock));
  }
  // add lock to collection
  lockArray[lockCount].name = name;
  lockArray[lockCount].lock = &lock;
  lockArray[lockCount].isLocked = false;
  lockArray[lockCount].threadHolding = -1;
  lockArray[lockCount].waitingCount = 0;
  lockArray[lockCount].waitingHead = NULL;
  lockCount++;
}

/*
 *
 */
extern "C" void addSemaphore(char name[], int initial, sem_t &sem) {
  //printf("sched - addSemaphore");

  // initalize semaphore collection if not already done so
  if (semCount == 0) {
    semArray = (Semaphore*) calloc(MAX_SEMS, sizeof(Semaphore));
  }
  // add semaphore to collection
  semArray[semCount].name = name;
  semArray[semCount].sem = &sem;
  semArray[semCount].initial = initial;
  semArray[semCount].value = initial;
  semArray[semCount].waitingCount = 0;
  semArray[semCount].waitingHead = NULL;
  semCount++;
}

/*
 * Precondition:  All threads are in the READY state and asleep.
 * Postcondition:  Only one thread is selected to be awake.  All threads are still in the READY state.
 */
extern "C" void initializeThread(int id) {
  while(true) {
    if (allThreadsAdded) {
      break;
    }
  }

  if (tracing) {
    printf("[%d] : sched - initializeThread: initialThread to stay awake=%d\n", id, initialThread);
  }

  // put thread to sleep unless if it's the selected initial thread
  if(id != initialThread) {
    threadArray[id].status = READY;
    // block SIGUSR1 signal
    if( pthread_sigmask( SIG_BLOCK, &sigSet, NULL) == -1) {
      perror("pthread_sigmask error");
      pthread_exit((void *)1);
    }
    pauseThread(id);
  }
  else {
    if (tracing) {
      printf("[%d] : sched - initializeThread:  staying awake; waiting for semInitialBlock\n", id);
    }
    int value; 
    while (true) {
      sem_getvalue(&semInitialBlock, &value);
      if (value == (threadCount-1)) {
        if (tracing) {
          printf("[%d] : sched - initializeThread:  done waiting for semInitialBlock\n", id);
        }
        inInitialization = false;
        // add all other threads to readyThreads queue
        for (int i=0; i < threadCount; i++) {
          int readyId = threadArray[i].id;
          if (readyId != initialThread) {
            readyThreadsHead = addThreadNode(i, readyThreadsHead, readyId);
            if (tracing) {
              printf("[%d] : sched - initializeThread:  i=%d, readyId=%d, readyThreads=%s\n", id, i, readyId, printThreads(i+1, readyThreadsHead).c_str());
            }
          }
        }
        threadArray[id].status = RUNNING;
        numReadyThreads = threadCount-1;
        if (tracing) {
          printf("[%d] : sched - initializeThread:  done initializing ready threads queue; readyThreads=%s\n", id, printThreads(threadCount-1, readyThreadsHead).c_str());
        }
        break;
      } // end if
    } // end while
  } // end else
}

/*
 * Pauses thread (sleeps until a signal is received to wake it up).
 *
 */
extern "C" void pauseThread(int id) {
  if (tracing) {
    printf("[%d] : sched - pauseThread:  going to sleep\n", id);
  }

  // setup signals
  sigemptyset(&sigSet);
  if( sigaddset(&sigSet, SIGUSR1) == -1 ) {
    perror("Sigaddset error");
    pthread_exit((void *)1);
  } 
  if( sigaddset(&sigSet, SIGUSR2) == -1 ) { // for thread initialization
    perror("Sigaddset error");
    pthread_exit((void *)1);
  }

  // wait for signal(s)
  int sigNum;
  int rc;
  while(true) {
    if(inInitialization) {
      sem_post(&semInitialBlock);
      if (tracing) {
        int value; 
        sem_getvalue(&semInitialBlock, &value);
        printf("[%d] : sched - pauseThread: semInitialBlock.value=%d\n", id, value);
      }
    }
    rc = sigwait(&sigSet, &sigNum);
    if (rc != 0) {
      perror("sigwait error");
      pthread_exit((void *)1);
    }
    // handle signals
    if (sigNum ==  SIGUSR1) {
      // block signal
      if( pthread_sigmask( SIG_BLOCK, &sigSet, NULL) == -1) {
        perror("pthread_sigmask error");
        pthread_exit((void *)1);
      }
      if (tracing) {
        printf("[%d] : sched - pauseThread:  received a SIGUSR1 signal.  Waking up now.\n", id);
      }
      break;
    } else { // should normally not happen
      printf("%s,\nUnexpected signal %d\n", stderr, sigNum);
      pthread_exit((void *)1);
    }
  }
}

/*
 *
 */
extern "C" void invokeScheduler(int id, int lineNum) {
  if (tracing) {
    printf("[%d] [%d]: sched - invokeScheduler: numReadyThreads=%d, readyThreads=%s\n", id, lineNum, numReadyThreads, printThreads(numReadyThreads, readyThreadsHead).c_str());
  }

  printStatus();

  int currThreadId = id;
  Thread* currThread = &threadArray[currThreadId];
  if(currThread->status == RUNNING) { // add currThread to pool of threads to be scheduled
    currThread->status = READY;
    readyThreadsHead = addThreadNode(numReadyThreads, readyThreadsHead, currThreadId);
    numReadyThreads++;
  }

  if( allThreadsCompleted() ) {
    // do nothing, just return;
    logToFile("All threads have completed.\n");
  }
  else if(numReadyThreads < 1) { // no READY threads to schedule
    stringstream ss;
    ss << "[" << id << "] [" << lineNum << "] - ";
    ss << "No ready threads available to schedule; possible DEADLOCK detected.  Exiting.\n";
    log(ss.str());
    if (getLogMode() == ON) {
      endLogging();
    }
    exit(EXIT_FAILURE);
  }
  else { // there are READY threads to schedule
    // get next ready thread (random mode vs. interactive mode)
    int nextReadyThreadIndex = getReadyThreadIndex(schedMode, 0, numReadyThreads); // TDOD:  handle error if = -1
    ThreadNode* nextThread = retrieveThreadNode( numReadyThreads, readyThreadsHead, nextReadyThreadIndex );
    int nextThreadId = nextThread->id;
    
    if(tracing) {
      printf("[%d] [%d]: sched - invokeScheduler:  numReadyThreads=%d, readyThreads=%s, nextThreadId=%d\n", id, lineNum, numReadyThreads, printThreads(numReadyThreads, readyThreadsHead).c_str(), nextThreadId);
    }

    threadArray[nextThreadId].status = RUNNING;  // switch from READY to RUNNING
    readyThreadsHead = deleteThreadNode(numReadyThreads, readyThreadsHead, nextReadyThreadIndex);
    numReadyThreads--;

    if( currThreadId == nextThreadId) {
      // just continue; current thread will run again
      stringstream ss;
      ss << "[" << id << "] " << "[" << lineNum << "] - Selected next thread to run= " << nextThreadId << ", which is the same as current thread.\n";
      log(ss.str());
    }
    else {
      // wake up nextThread, and put currThread to sleep
      stringstream ss;
      ss <<  "[" << id << "] " << "[" << lineNum << "] - Switching from thread " << currThreadId << " to thread " << nextThreadId << ".\n";
      log(ss.str());

      // block SIGUSR1 signal
      if( pthread_sigmask( SIG_BLOCK, &sigSet, NULL) == -1) {
        perror("pthread_sigmask error");
        pthread_exit((void *)1);
      }

      // wake up nextThread 
      int status;
      status = pthread_kill( threadArray[nextThreadId].threadId, SIGUSR1 );
      if (status <  0) {
        perror("pthread_kill failed");
        exit(EXIT_FAILURE);
      }
      else if (threadArray[currThreadId].status != COMPLETED) {
        if (tracing) {
          printf("[%d] [%d]: sched - invokeScheduler: thread=%d sent signal to wake up thread %d and is proceeding to sleep\n", id, lineNum, currThreadId, nextThreadId);
        }

        // put current thread to sleep
        pauseThread(currThreadId);
      }
      else {
        // just continue
      }
    }
  }
}

/*
 *
 */
extern "C" void setThreadCompleted(int id) {
  if (tracing) {
    printf("[%d] : sched - setThreadCompleted\n",id);
  }

  threadArray[id].status = COMPLETED;
  numThreadsCompleted++;
  // switch threads if not all are completed
  if( !allThreadsCompleted() ) {
    invokeScheduler(id, -1);
  } else {
    logStatusToFile();
    log("Completed run successfully.");
  }
}

/*
 * Thread takes a lock, or gets added to waitlist if lock is already taken
 */
extern "C" void mutexLock(int id, pthread_mutex_t &lock) {
  if (tracing) {  
    printf("[%d] : sched - mutexLock\n", id);
  }

  // find lock
  Lock* myLock = getLock(lock);
  char* lockName;
  if(myLock == NULL) {
    stringstream ss;
    ss << "[ " << id << "] : sched - mutexLock: ERROR:  Unable to find lock.  Verify lock was added to scheduler.  Exiting program now.\n";
    log(ss.str());
    exit(EXIT_FAILURE);
  } 
  else {
    lockName = myLock->name;

    if (tracing) {
      printf("[%d] : sched - mutexLock:  found lock, id:%s\n", id, lockName);
    }

    // if lock is available, set holding thread to current thread, lock
    if(!myLock->isLocked) {
      stringstream ss;
      ss <<  "[" << id << "] " << "[" << -1 << "] - mutexLock:  lock is free; thread " << id << " will now hold lock " << lockName << endl;
      log(ss.str());
      myLock->isLocked = true;
      myLock->threadHolding = id;
    }  
    else { // if lock is unavailable, add thread
      stringstream ss;
      ss <<  "[" << id << "] " << "[" << -1 << "] - mutexLock:  lock " << lockName << " is taken and held by thread " << myLock->threadHolding;
      ss << "; thread " << id << " will be added to the thread waiting list\n";
      log(ss.str());

      ThreadNode* newWaitList = addThreadNode(myLock->waitingCount, myLock->waitingHead, id);
      myLock->waitingHead = NULL;
      myLock->waitingHead = newWaitList;
      ++(myLock->waitingCount);
      if(myLock->waitingHead == NULL) {
        if (tracing) { 
          printf("[%d] : sched - mutexLock:  lock %s has no waiting threads\n", id, lockName);
        }
      }
      threadArray[id].waitingName = lockName;
      threadArray[id].status = WAITING_LOCK; // switch from RUNNING to WAITING_LOCK
      invokeScheduler(id, -1);
    }
  }
}

/*
 *
 */
extern "C" void mutexUnlock(int id, pthread_mutex_t &ptLock) {
  if (tracing) {
    printf("[%d] : sched - mutexUnlock\n", id);
  }

  // find lock
  Lock* lock = getLock(ptLock);
  char* lockName;
  if(lock == NULL) {
    stringstream ss;
    ss << "[" << id << "]  : sched - mutexUnlock: ERROR - Unable to find lock.  Verify lock was added to scheduler.  Exiting program now.\n";
    log(ss.str());
    exit(EXIT_FAILURE);
  } 
  else {
    lockName = lock->name;
    if (tracing) {
      printf("[%d] : sched - mutexUnlock:  found lock, id:%s\n", id, lockName);
    }

    // release lock and transfer to a waiting thread
    if(lock->waitingCount == 0) { // release lock
      lock->isLocked = false;
      lock->threadHolding = -1;
      // log
      stringstream ss;
      ss <<  "[" << id << "] " << "[" << -1 << "] - mutexUnlock:  No threads waiting for lock " << lockName << endl;
      log(ss.str());
    }
    else { // transfer lock
      // select next thread
      int numWaitingThreads = lock->waitingCount;
      int waitingIndex = getReadyThreadIndex(schedMode, 0, numWaitingThreads); // TDOD:  handle error if -1
      ThreadNode *nxtThread = retrieveThreadNode(numWaitingThreads, lock->waitingHead, waitingIndex);
      int nxtThreadId = nxtThread->id;
      // log
      stringstream ss;
      ss <<  "[" << id << "] " << "[" << -1 << "] - mutexUnlock:  Transferring lock " << lockName << " from thread " << id << " to thread " <<  nxtThreadId << "\n";  
      log(ss.str());
  
      threadArray[nxtThreadId].status = READY;
      threadArray[nxtThreadId].waitingName = "";
      lock->threadHolding = nxtThreadId;
      (lock->waitingHead) = deleteThreadNode(numWaitingThreads, lock->waitingHead, waitingIndex);
      (lock->waitingCount)--;
      // add to ready queue
      readyThreadsHead = addThreadNode(numReadyThreads, readyThreadsHead, nxtThreadId);
      numReadyThreads++;
    }
  }
}

/*
 * Thread takes a sem, or gets added to waitlist if no more sems available
 */
extern "C" void semWait(int id, sem_t &sem) {
  if (tracing) {
    printf("[%d] : sched - semWait\n", id);
  }

  // find sem
  Semaphore* mySem = getSemaphore(sem);
  char* semName;
  if(mySem == NULL) {
    stringstream ss;
    ss << "[" << id << "] : sched - semWait: ERROR:  Unable to find semaphore.  Verify semaphore was added to scheduler.  Exiting program now.\n";
    log(ss.str());
    exit(EXIT_FAILURE);
  }
  else {
    semName = mySem->name;
    if (tracing) {
      printf("[%d] : sched - semWait:  found semaphore, id:%s\n", id, semName);
    }

    int initial = mySem->initial;
    int preWaitValue = (mySem->value)--; // decrement sem value
    int value = mySem->value;
    
    if(value < 0) { // if sem is unavailable, add thread to waiting list
      int waitingCount = mySem->waitingCount;

      // log
      stringstream ss;
      ss <<  "[" << id << "] " << "[" << -1 << "] - semWait:  sem " << semName << " is taken and has value=" << value;
      ss << "; thread " << id << " will be added to thread waiting list.\n";
      log(ss.str());

      ThreadNode* newWaitList = addThreadNode(waitingCount, mySem->waitingHead, id);
      mySem->waitingHead = NULL;
      mySem->waitingHead = newWaitList;
      (mySem->waitingCount)++;
      if(mySem->waitingHead == NULL) {
        if (tracing) {
          printf("[%d] : sched - semWait:  sem %s has no waiting threads\n", id, semName);
        }
      }
      threadArray[id].waitingName = semName;
      threadArray[id].status = WAITING_SEM;  // switch from RUNNING to WAITING_SEM
      invokeScheduler(id, -1);
    } else {
      // log
      stringstream ss;
      ss <<  "[" << id << "] " << "[" << -1 << "] - semWait:  semaphore " << semName << " is available for thread " << id << "'s use.\n";
      log(ss.str());
    }
  }
}

/*
 * Thread releases a semaphore.
 */
extern "C" void semPost(int id, sem_t &ptSem) {
  if (tracing) {
    printf("[%d] : sched - semPost\n", id);
  }

  // find sem
  Semaphore* sem = getSemaphore(ptSem);
  char* semName;
  if(sem == NULL) {
    stringstream ss;
    ss << "[" << id << "] : sched - semPost: ERROR - Unable to find semaphore.  Verify semaphore was added to scheduler.  Exiting program now.\n";
    log(ss.str());
    exit(EXIT_FAILURE);
  }
  else {
    semName = sem->name;
    // if sem is available, add current thread to list of holding threads
    int initial = sem->initial;
    int prePostValue = (sem->value)++; // increment sem value
    int value = sem->value;
    int waitingCount = sem->waitingCount;

    if (tracing) {
      printf("[%d] : sched - semPost:  found sem, id:%s, initial=%d, value=%d, waitingCount=%d\n", id, semName, initial, value, waitingCount);
    }

    if(waitingCount == 0) {
      stringstream ss;
      ss <<  "[" << id << "] " << "[" << -1 << "] - semPost:  No threads waiting for sem " << semName << "\n";
      log(ss.str());
    }
    else { // "wake-up" thread waiting for sem
      int nextSemHolderIndex = getReadyThreadIndex(schedMode, 0, waitingCount); // TDOD:  handle error 
      ThreadNode *nxtThread = retrieveThreadNode(waitingCount, sem->waitingHead, nextSemHolderIndex);
      int nxtThreadId = nxtThread->id;

      stringstream ss;
      ss << "[" << id << "] " << "[" << -1 << "] - semPost:  Granting semaphore " << semName << " to thread " <<  nxtThreadId << "\n";
      log(ss.str());

      threadArray[nxtThreadId].status = READY; // switch from WAITING_SEM to READY
      threadArray[nxtThreadId].waitingName = "";
      (sem->waitingHead) = deleteThreadNode(waitingCount, sem->waitingHead, nextSemHolderIndex);
      (sem->waitingCount)--;
      (sem->value)--;
      // add to ready queue
      readyThreadsHead = addThreadNode(numReadyThreads, readyThreadsHead, nxtThreadId);
      numReadyThreads++;
    }
  }
}

/******************************************************************************************************
 *			ACCESSOR METHODS
 *****************************************************************************************************/

/*
 * Prints thread, lock, and semaphore status.
 */
extern "C" void printStatus() {
  // print status to console
  if (schedMode != RANDOM) {
    printf("**********************************************************************************\n");
    printf("%s\n", getThreadStatus().c_str());
    printf("__________________________________________________________________________________\n");
    printf("%s\n", getLockStatus().c_str());
    printf("__________________________________________________________________________________\n");
    printf("%s\n", getSemaphoreStatus().c_str());
    printf("**********************************************************************************\n");
  }

  // print status to file
  logStatusToFile();
}

/*
 * Outputs status to file in logMode == ON.
 */
void logStatusToFile() {
  logToFile("**********************************************************************************\n");
  logToFile(getThreadStatus().c_str());
  logToFile("__________________________________________________________________________________\n");
  logToFile(getLockStatus().c_str());
  logToFile("__________________________________________________________________________________\n");
  logToFile(getSemaphoreStatus().c_str());
  logToFile("**********************************************************************************\n");
}

/*
 * Returns thread status.
 */
string getThreadStatus() {
  Thread* thread;
  stringstream threadStatus;
  threadStatus << left;
  threadStatus << "THREAD Status: numThreads: " << threadCount << "\n";
  threadStatus << std::setw(26) <<  "|ID" << std::setw(14) << "|STATUS" << std::setw(42) <<  "|WAITING_NAME" << "|\n";

  for(int i=0; i < threadCount; i++) {
    thread = &(threadArray[i]);
    threadStatus << "|" << std::setw(25) << thread->id;
    threadStatus << "|" << std::setw(13) << getStatus(thread->status).c_str();
    threadStatus << "|" << std::setw(41) << thread->waitingName << "|\n";;
  }
  return threadStatus.str();
}


/*
 * Returns lock status.
 */
string getLockStatus() {
  Lock* lock;
  int threadHolding = -1;
  int waitingCount = -1;
  ThreadNode *waitingHead;
  
  stringstream lockStatus;
  lockStatus << left;
  lockStatus << "LOCK Status: numLock: " << lockCount << "\n";
  lockStatus << std::setw(26) << "|NAME" << std::setw(14) <<  "|LOCKED" << std::setw(21) << "|HOLDING_THREAD" << std::setw(21) <<  "|WAITING_THREADS" << "|\n";

  for(int i=0; i < lockCount; i++) {
    lock = &(lockArray[i]);
    threadHolding = lock->threadHolding;
    waitingCount = lock->waitingCount;
    waitingHead = lock->waitingHead;
    lockStatus << "|" << std::setw(25) << lock->name;
    lockStatus << "|" << std::setw(13) << boolToStr(lock->isLocked).c_str();
    lockStatus << "|" << std::setw(20) << (threadHolding == -1 ? "" : intToStr(threadHolding).c_str());
    lockStatus << "|" << std::setw(20) << (waitingHead == NULL ? "" : printThreads(waitingCount, waitingHead).c_str()) << "|\n";
  }
  return lockStatus.str();
}

/*
 * Prints semaphore status.
 */
string getSemaphoreStatus() {
  Semaphore* sem;
  int threadHolding = -1;
  int usingCount = -1;
  int waitingCount = -1;
  ThreadNode *usingHead;
  ThreadNode *waitingHead;

  stringstream semStatus;
  semStatus << left;
  semStatus << "SEMAPHORE Status: numSems: " << semCount << "\n";
  semStatus << std::setw(26) << "|NAME" << std::setw(14) << "|VAL/INITIAL" << std::setw(42) << "|WAITING_THREADS" << "|\n";


  for(int i=0; i < semCount; i++) {
    sem = &(semArray[i]);
    waitingCount = sem->waitingCount;
    waitingHead = sem->waitingHead;
    semStatus << "|" << std::setw(25) << sem->name;
    semStatus << "|" << sem->value << "/" << std::setw(11) << sem->initial; 
    semStatus << "|" << std::setw(41) << (waitingHead == NULL ? "" : printThreads(waitingCount, waitingHead).c_str())  << "|\n";
  }
  return semStatus.str();
}


/******************************************************************************************************
 *                      HELPER FUNCTIONS
 *****************************************************************************************************/

void log(string message) {
  const char* msg = message.c_str();
  // log to console if tracing or if not in RANDOM mode
  if (tracing || (schedMode != RANDOM)) {
    printf("%s\n", msg);
  }
  // log to file
  logToFile(msg);
}

/*
* Returns whether or not all threads have status COMPLETED
*/
bool allThreadsCompleted() {
  return numThreadsCompleted == threadCount;
}

/*
* Returns an index into the ready threads collection based on scheduler mode.
*/
int getReadyThreadIndex(SchedulerMode mode, int min, int max) {
  int index = -1;
  int userChoice = -1;
  bool validChoice = false;

  if(max > 0) {
    switch(mode) {
      case RANDOM:
          //printf("sched - getReadyThreadIndex:  random seed=%d\n", seed);

          index = rand() % max;
          break;
      case INTERACTIVE:
          do {
  	    printf("\nAvailable threads [<INDEX>]<threadId>:  %s\n", printThreads(numReadyThreads, readyThreadsHead).c_str());
  pthread_mutex_unlock(&printOutMutex);
            printf("Enter a thread INDEX %d to %d: ", 0, max-1);
            scanf("%d", &userChoice);
            if( (userChoice >= 0) && (userChoice < max) ) {
                index = userChoice;
                validChoice = true;
            }
            else
              printf("You entered an invalid thread ID: %d\n", userChoice);
          } while(!validChoice);

          break;
      case FIFO:
          index = 0;
          break;
      case LIFO:
          index = max-1;
          break;
      default:
          printf("sched - getReadyThreadIndex:  Unsupported mode.\n");
    }
  }
  else {
      printf("sched - getReadyThreadIndex:  There are no ready threads to choose from.\n");
  }

  //printf("sched - getReadyThreadIndex:  min=%d, max=%d, returning index:%d\n", min, max, index);

  return index;
}


/*
 * Returns a comma deliminated list of thread ids.
 */
string getThreadList(int count, Thread* thread) {
  stringstream threadListing;
  int index=0;

  for(int i=0; i<count; i++) {
    threadListing << thread[index].id;
    if( i<count-1 )
      threadListing << ",";
  }
  return threadListing.str();
}

/*
 * Returns user defined thread id.
 */
int getCurrentThreadId() {
  int id = -1;
  pthread_t curThread = pthread_self();
  for(int i=0; i < threadCount; i++) {
    //printf("pthread_equal=%d\n", pthread_equal(curThread, threadArray[i].threadId));
    if( pthread_equal(curThread, threadArray[i].threadId) ) { // 0 if differerent, non-zero otherwise
      id = i;
      //printf("Found matching thread\n");
      break;
    }
  }
  return id;
}

// returns Lock, else NULL if no lock found
Lock* getLock(pthread_mutex_t &ptLock) {
  // find lock index
  int lockIndx = -1;
  for(int i=0; i<lockCount; i++) {
    pthread_mutex_t* tempLk = lockArray[i].lock;
    if(tempLk == &ptLock) {
      lockIndx = i;
      break;
    }
  }
  // get lock
  Lock* lock = NULL;
  if(lockIndx != -1)
    lock = &(lockArray[lockIndx]);
  return lock;
}

// returns semaphore, else NULL if no semaphore found
Semaphore* getSemaphore(sem_t &ptSem) {
  // find sem index
  int semIndx = -1;
  for(int i=0; i<semCount; i++) {
    sem_t* tempSem = semArray[i].sem;
    if(tempSem == &ptSem) {
      semIndx = i;
      break;
    }
  }
  // get sem
  Semaphore* sem = NULL;
  if(semIndx != -1)
    sem = &(semArray[semIndx]);
  return sem;
}

