// util.c - Utility functions for synchronization framework

// DO NOT MODIFY THIS FILE

#include <stdlib.h>
#include <time.h>

void
rand_sleep()
{
  struct timespec time_struct;
  int sleep_time = random() % 1000 + 1;

  time_struct.tv_sec = 0;
  time_struct.tv_nsec = sleep_time * 1000000;
  nanosleep(&time_struct, NULL);
}

/*
 * Returns a random number between 0 and 1000
 */
int 
getRandom(int seed)
{
    srand( seed );
    return rand() % 1001;
}

int 
getSeed() {
  int seed = time(NULL);
  return seed;
}
