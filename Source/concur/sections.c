// sections.c - Synchronization sections for unisex restroom

// sections.1.c
// sections.good.c


#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include "util.h"
#include "scheduler/sched.h"


// Shared variables
pthread_mutex_t outMutex;

// TODO: Declare shared variables here
// Creating Mutex variables semaphores, and counters.
pthread_mutex_t limitMale, limitFemale, maleMutex, femaleMutex;
sem_t male, female;
// Counter for males and females.
int countMale, countFemale = 0;


// Initializing global variables
void initGlobals()
{
  // LEAVE THIS STATEMENT
  pthread_mutex_init(&outMutex, NULL);

  // TODO: Complete this function
  // Initializing Mutex variables and Semaphores
  pthread_mutex_init(&maleMutex, NULL);
  pthread_mutex_init(&femaleMutex, NULL);  
  pthread_mutex_init(&limitMale, NULL);
  pthread_mutex_init(&limitFemale, NULL);
  sem_init(&male, 0, 1);
  sem_init(&female, 0, 1);  

  addLock("limitMale", &limitMale);
  addLock("limitFemale", &limitFemale);
  addLock("maleMutex", &maleMutex);
  addLock("femaleMutex", &femaleMutex);
  addSemaphore("female", 1, &female);
  addSemaphore("male", 1, &male);
}

// Processes the action of males and females
// when they enter the restroom.
void entrySection(int id)
{
  bool isFemale = id % 2;
  // TODO: Complete this function
  if (!isFemale) { // Male
	mutexLock(id, &limitMale);
	semWait(id, &male); // other males wait
	mutexLock(id, &maleMutex); // only current male
	countMale++; 
	if (countMale == 1)
	  semWait(id, &female); // females wait
	mutexUnlock(id, &maleMutex); // other males
	semPost(id, &male);
	mutexUnlock(id, &limitMale);	
  } else { // Female
	mutexLock(id, &limitFemale); // Only females
	semWait(id, &female); // other females wait
	mutexLock(id, &femaleMutex); // only current female
	countFemale++; // increment female count
	if (countFemale == 1)
	  semWait(id, &male); // males wait if female
	mutexUnlock(id, &femaleMutex); // other females
	semPost(id, &female);
	mutexUnlock(id, &limitFemale);	
  }
}

// Processes male/female action when they leave
// the restroom.
void exitSection(int id)
{
  bool isFemale = id % 2;
  // TODO: Complete this function
  if(!isFemale) { // Male
	mutexLock(id, &maleMutex); // Male lock
	countMale--;
	if (countMale == 0) // No more males
	  semPost(id, &female); // Females can continue
	mutexUnlock(id, &maleMutex);
  } else { // Female
	mutexLock(id, &femaleMutex); // Female lock
	countFemale--; 
	if (countFemale == 0) // No more females
	  semPost(id, &male); // Males can leave
	mutexUnlock(id, &femaleMutex);
  }
}

void criticalSection(int id)
{
  // DO NOT TOUCH THIS FUNCTION
  rand_sleep();
}

void remainderSection(int id)
{
  // DO NOT TOUCH THIS FUNCTION
  rand_sleep();
}

