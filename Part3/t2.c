#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
 #include <pthread.h>

void * dummy (void * arg)
{
   return arg;
}

double xelapsed (struct timespec a, struct timespec b)
{
   return (a.tv_sec - b.tv_sec) * 1000000.0
          + (a.tv_nsec - b.tv_nsec) / 1000.0;
}

void measure_thread (int n)
{
  struct timespec start, stop, finish;
  pthread_t pids[n];
  int i;
  int no = n;
  //int status;

   clock_gettime (CLOCK_REALTIME, &start);
   /*
    * Make N threads, call dummy in every child.
    */

    for(i=0;i<n;i++){
       pthread_t pid;
       int res=(int) pthread_create (&pid, NULL, dummy, NULL);
      if (res < 0) {
        perror("error creating thread");
        abort();
      }else if (res==0) {
       //printf("creating and executing thread\n");
        dummy;
        pids[i]=pid;
        
        
        //exit(0);
      }
    }

    //printf("Length of array: %d\n", (int)( sizeof(pids) / sizeof(pids[0]) ));
    int j;
    for(j=0; j<n; j++){
         void *result;
        pthread_join (pids[j], &result);  
        clock_gettime (CLOCK_REALTIME, &stop);
    }
     
   clock_gettime (CLOCK_REALTIME, &finish);

   printf ("%d proc: thread=%5.0f (mics) wait=%5.0f (mics) sum=%5.0f (mics)\n",
           n, xelapsed (stop, start),
           xelapsed (finish, stop), xelapsed (finish, start));
   printf ("per proc: thread=%5.0f (mics) wait=%5.0f (mics) sum=%5.0f (mics)\n",
           xelapsed (stop, start)/n,
           xelapsed (finish, stop)/n, xelapsed (finish, start)/n);
    }


int main(int argc, char*argv[])
{
   int n;

   if( argc == 2) {
     n = atoi( argv[1]);
  } else {
     n = 10;
  }
  measure_thread( n);

  return(0);
}
