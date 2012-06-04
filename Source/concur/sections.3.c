// sections.c - Synchronization sections for unisex restroom

// sections.bad2.c

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include "util.h"
#include "scheduler/sched.h"

// TODO: Declare shared variables here
pthread_mutex_t numMutex;
pthread_mutex_t limit_female;
pthread_mutex_t limit_male;
sem_t men;
sem_t women;
unsigned menCount;
unsigned womenCount;


void
initGlobals()
{
  // LEAVE THIS STATEMENT
  pthread_mutex_init(&numMutex, NULL);
  pthread_mutex_init(&limit_female, NULL);
  pthread_mutex_init(&limit_male, NULL);
  sem_init(&men,0,1);
  sem_init(&women,0,1);
  menCount = 0;
  womenCount = 0;
  addLock("numMutex", &numMutex);
  addLock("limit_female", &limit_female);
  addLock("limit_male", &limit_male);
  addSemaphore("women", 1, &women);
  addSemaphore("men", 1, &men);
}

void 
entrySection(int id)
{
  bool isFemale = id % 2;

  // TODO: Complete this function
  if(isFemale) {
    mutexLock(id, &limit_female);
    mutexLock(id, &numMutex);
    womenCount++;
    if(womenCount == 1)
      semWait(id, &men);
    mutexUnlock(id, &numMutex);
    mutexUnlock(id, &limit_female);
  }
  else {
    mutexLock(id, &limit_male);
    mutexLock(id, &numMutex);
    menCount++;
    if(menCount == 1)
      semWait(id, &women);
    mutexUnlock(id, &numMutex);
    mutexUnlock(id, &limit_male);
  }
  
}

void 
exitSection(int id)
{
  bool isFemale = id % 2;
  // TODO: Complete this function
  if(isFemale) {
    mutexLock(id, &limit_female);
    womenCount--;
    if(womenCount == 0)
      semPost(id, &men);
    mutexUnlock(id, &limit_female);
  }
  else {
    mutexLock(id, &limit_male);
    menCount--;
    if(menCount == 0)
      semPost(id, &women);
    mutexUnlock(id, &limit_male);
  }
  
}

void
remainderSection(int id)
{
  rand_sleep();
}

void
criticalSection(int id)
{
  rand_sleep();
}

