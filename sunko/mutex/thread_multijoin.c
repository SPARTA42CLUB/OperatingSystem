/* thread_mutijoin.c

   This program creates one thread for each of its command-line arguments.
   Each thread sleeps for the number of seconds specified in the corresponding
   command-line argument, and then terminates. This sleep interval simulates
   "work" done by the thread.

   The program maintains a global array (pointed to by 'thread') recording
   information about all threads that have been created. The items of this
   array record the thread ID ('tid') and current state ('state', of type 'enum tstats')
   of each threads.

   As each thread terminates, it sets its 'state' to TS_TERMINATED and
   signals the 'threadDied' condition variable. the main thread continuously
   waits on this condition variable, and is thus informed when any of the
   threads that is created has terminated. When 'numLive', which records
   the number of live threads, falls to 0, the main terminates.
*/


#include <pthread.h>
#include "tlpi_hdr.h"

static pthread_cond_t threadDied = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t threadMutex = PTHREAD_MUTEX_INITIALIZER;

static int totThreads = 0; /**/
