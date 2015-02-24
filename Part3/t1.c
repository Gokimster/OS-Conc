#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

void * dummy (void * arg)
{
   return arg;
}

double xelapsed (struct timespec a, struct timespec b)
{
   return (a.tv_sec - b.tv_sec) * 1000000.0
          + (a.tv_nsec - b.tv_nsec) / 1000.0;
}

void measure_fork (int n)
{
  struct timespec start, stop, finish;
  pid_t pids[n];
  int i;

   clock_gettime (CLOCK_REALTIME, &start);
   /*
    * Make N forks, call dummy in every child.
    */

    for(i=0;i<n;i++){
      if ((pids[i] = fork()) < 0) {
        perror("fork");
        abort();
      }else if (pids[i] == 0) {
        dummy(dummy);
        exit(0);
      
      }
    }

   clock_gettime (CLOCK_REALTIME, &stop);
   /*
    * Wait for the forks.
    */

  int status;
  pid_t pid;
  int no = n;
  while (no > 0) {
    pid = wait(&status);
    --no;  // TODO(pts): Remove pid from the pids array.
  }
   clock_gettime (CLOCK_REALTIME, &finish);

   printf ("%d proc: fork=%5.0f (mics) wait=%5.0f (mics) sum=%5.0f (mics)\n",
           n, xelapsed (stop, start),
           xelapsed (finish, stop), xelapsed (finish, start));
   printf ("per proc: fork=%5.0f (mics) wait=%5.0f (mics) sum=%5.0f (mics)\n",
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
  measure_fork( n);

  return(0);
}
