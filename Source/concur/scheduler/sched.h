/* Scheduler header file
 *
 */
#ifdef __cplusplus
extern "C"
#endif


// Initialization functions
//void setSchedulerMode();
//void setNumThreads(int numThreads);
void addThread(int id, pthread_t *thread);
void addLock(char *name, pthread_mutex_t *lock);
void addSemaphore(char *name, int initial, sem_t *semaphore);

// Thread functions
//void initializeScheduler(int id);
void initializeScheduler(int numThreads, int numRounds, char* mode, char* logLevel, int seed);
void initializeThread(int id);
void invokeScheduler(int id, int lineNum);
void setThreadCompleted(int threadIndex);
void pauseThread(int id);
// Lock functions
void mutexLock(int id, pthread_mutex_t *lock);
void mutexUnlock(int id, pthread_mutex_t *lock);

// Semaphore functions
void semWait(int id, sem_t *sem);
void semPost(int id, sem_t *sem);


void printStatus();
