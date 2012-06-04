// sections.c - Synchronization sections for unisex restroom

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include "util.h"
#include "scheduler/sched.h"


// Shared variables
pthread_mutex_t outMutex;

// TODO: Declare shared variables here
int maleCount, femaleCount;
sem_t female, male;
pthread_mutex_t limitMaleMutex, limitFemaleMutex, maleCountMutex, femaleCountMutex;

// sem values
int SEM_MALE_INITIAL = 1;
int SEM_FEMALE_INITIAL = 1;

// for testing
int femaleOnly = 1;


void
initGlobals()
{
  // LEAVE THIS STATEMENT
  pthread_mutex_init(&outMutex, NULL);

  // TODO: Complete this function
  maleCount = 0;
  femaleCount = 0;
  sem_init(&male, 0, 1);
  sem_init(&female, 0, 1);
  pthread_mutex_init(&limitMaleMutex, NULL);
  pthread_mutex_init(&limitFemaleMutex, NULL);
  pthread_mutex_init(&maleCountMutex, NULL);
  pthread_mutex_init(&femaleCountMutex, NULL);

  // TODO:  Complete for scheduler
  addLock("limitMaleMutex", &limitMaleMutex);
  addLock("limitFemaleMutex", &limitFemaleMutex);
  addLock("maleCountMutex", &maleCountMutex);
  addLock("femaleCountMutex", &femaleCountMutex);
  addSemaphore("female", SEM_FEMALE_INITIAL, &female);
  addSemaphore("male", SEM_MALE_INITIAL, &male);
}

void 
entrySection(int id)
{
  // LEAVE THESE STATEMENTS
  int isFemale = femaleOnly ? 1 : (id % 2 == 0);

  // TODO: Complete this function
  if (isFemale) {
    mutexLock(id, &limitFemaleMutex);
    //pthread_mutex_lock(&limitFemaleMutex);

    //  sem_wait(&female);
    semWait(id, &female);

    mutexLock(id, &femaleCountMutex);
    //pthread_mutex_lock(&femaleCountMutex);

    femaleCount++;
    if (femaleCount == 1) {
      //   sem_wait(&male);
      semWait(id, &male);
    }

    mutexUnlock(id, &femaleCountMutex);
    //pthread_mutex_unlock(&femaleCountMutex);

    //  sem_post(&female);
    semPost(id, &female);

    mutexUnlock(id, &limitFemaleMutex);
    //pthread_mutex_unlock(&limitFemaleMutex);
  }
  else {
    mutexLock(id, &limitMaleMutex);
    //pthread_mutex_lock(&limitMaleMutex);

    //sem_wait(&male);
    semWait(id, &male);

    mutexLock(id, &maleCountMutex);
    //pthread_mutex_lock(&maleCountMutex);

    maleCount++;
    if (maleCount == 1) {
      //sem_wait(&female);
      semWait(id, &female);
    }

    mutexUnlock(id, &maleCountMutex);    
    //pthread_mutex_unlock(&maleCountMutex);

    //sem_post(&male);
    semPost(id, &male);

    mutexUnlock(id, &limitMaleMutex);    
    //pthread_mutex_unlock(&limitMaleMutex);
  }
}

void 
exitSection(int id)
{
  // LEAVE THESE STATEMENTS
  int isFemale = femaleOnly ? 1 : (id % 2 == 0);

  // TODO: Complete this function
  if (isFemale) {
    mutexLock(id, &femaleCountMutex);
    //pthread_mutex_lock(&femaleCountMutex);
    femaleCount--;
    if (femaleCount == 0) {
      //  sem_post(&male);
      semPost(id, &male);
    }
    mutexUnlock(id, &femaleCountMutex);
    //pthread_mutex_unlock(&femaleCountMutex);
  }
  else {
    mutexLock(id, &maleCountMutex);
    //pthread_mutex_lock(&maleCountMutex);
    maleCount--;
    if (maleCount == 0) {
      //  sem_post(&female);
      semPost(id, &female);
    }
    mutexUnlock(id, &maleCountMutex);
    //pthread_mutex_unlock(&maleCountMutex);
  }
}

void
criticalSection(int id)
{
  // DO NOT TOUCH THIS FUNCTION
  int isFemale = femaleOnly ? 1 : (id % 2 == 0);
  rand_sleep();
}

void
remainderSection(int id)
{
  // DO NOT TOUCH THIS FUNCTION
  int isFemale = femaleOnly ? 1 : (id % 2 == 0);
  rand_sleep();
}

