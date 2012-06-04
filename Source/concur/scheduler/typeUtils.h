// typeUtils.h
#ifndef TYPEUTILS_H
#define TYPEUTILS_H
#include <semaphore.h>


enum SchedulerMode {
  RANDOM,
  FIFO,
  LIFO,
  INTERACTIVE
};

enum LogMode {
  ON,
  OFF
};

struct ThreadNode {
  int id;
  ThreadNode *next;
};

// Thread data type
enum Status {
  UNKNOWN,
  READY,
  WAITING_LOCK,
  WAITING_SEM,
  RUNNING,
  COMPLETED,
  EXITED
};

struct Thread {
  int id;               // id number for thread
  pthread_t threadId;   // thread id
  Status status;        // READY, WAITING, RUNNING, COMPLETED
  char* waitingName;    // name of lock or semaphore thread is waiting on
};

// Lock data type
struct Lock {
  char* name;
  bool isLocked;
  pthread_mutex_t* lock;
  int threadHolding;
  int waitingCount;
  ThreadNode *waitingHead;
};

// Semaphore data type
struct Semaphore {
  char* name;
  int max;
  sem_t* sem;
  int initial;
  int value;
  int waitingCount;
  ThreadNode* waitingHead;
};


std::string getStatus(Status status);
std::string getModeString(SchedulerMode mode);
std::string getLogModeString(LogMode mode);
std::string printThreads(int size, ThreadNode *head);
ThreadNode *retrieveThreadNode(int size, ThreadNode *head, int position);
ThreadNode* addThreadNode(int originalSize, ThreadNode *head, int newNode);
ThreadNode* deleteThreadNode(int size, ThreadNode *head, int position);

#endif
