// sections.c - Synchronization sections for unisex restroom

// sections.2.c
// sections.bad1.c

#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include "util.h"
#include "scheduler/sched.h"

// TODO: Declare shared variables here
pthread_mutex_t mutex_mem; 

bool isFemaleUsingBathroom;
int cntBathroomUse;

void
initGlobals()
{
	pthread_mutex_init(&mutex_mem, NULL ); 
	addLock("mutex_mem", &mutex_mem);
	
	cntBathroomUse = 0; 
	isFemaleUsingBathroom = false; 
}

void 
entrySection(int id)
{	
	bool isFemale = id % 2;
	while( isFemale != isFemaleUsingBathroom );

	mutexLock(id, &mutex_mem); 
	{
		++cntBathroomUse;
	}
	mutexUnlock(id, &mutex_mem); 
}

void 
exitSection(int id)
{
	bool isFemale = id % 2;
	mutexLock(id, &mutex_mem);
	{
		--cntBathroomUse;
		
		if( cntBathroomUse == 0 )
			isFemaleUsingBathroom = !isFemaleUsingBathroom;
	}
	mutexUnlock(id, &mutex_mem); 
}

void
remainderSection(int id)
{
	rand_sleep();
}

void
criticalSection(int id, bool isFemale)
{
	rand_sleep();
}

