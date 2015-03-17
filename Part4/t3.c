#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define N_THREADS 3
#define BUFFER_SIZE 200
#define NO_DATA 1000//100000
#define WORKLOAD1 100000
#define WORKLOAD2 100000
#define WORKLOAD3 100000
#define OUTPUT 100000

struct timespec start[NO_DATA], stop[NO_DATA];
double minLatency=100000.00;
double maxLatency=0;
double avgLatency=0;
int N_DATA = NO_DATA;

pthread_mutex_t lock;

/*******************************************************************************
 **  
 ** Here, the buffer implementation:
 **  
 ******************************************************************************/

typedef struct buffer buffer_t;

struct buffer {
  volatile int head;
  volatile int tail;
  int size;
  volatile int *elems;
};

buffer_t *createBuffer( int size)
{
  buffer_t *buf;

  buf = (buffer_t *)malloc( sizeof(buffer_t));
  buf->head = 0;
  buf->tail = 0;
  buf->size = size+1;
  buf->elems = (int *)malloc( (size+1)*sizeof(int));

  return( buf);
}

int pop( buffer_t* buf, int *data)
{
  int res;

  
  if(buf->head == buf->tail) {
      res = 0;  
  } else {
    pthread_mutex_lock(&lock);
    *data = buf->elems[buf->head];
    buf->head = (buf->head+1) % buf->size;
    res = 1;
  }

  return( res);
}


int push( buffer_t* buf, int data)
{
  int nextTail;
  int res;

  nextTail = (buf->tail + 1) % buf->size;
  if(nextTail != buf->head)   { 
    buf->elems[buf->tail] = data;
    buf->tail = nextTail;
    res = 1;
  } else {
    res = 0;
  }
  pthread_mutex_unlock(&lock);
  
  return( res);
}

/*******************************************************************************
 **  
 ** Now, the thread functions for the pipelining:
 **  
 ******************************************************************************/

typedef struct threadArgs threadArgs_t;

struct threadArgs {
  int tid;
  buffer_t *in_buf;
  buffer_t *out_buf;
  int workload;
};

int workUnit( int data)
{
  if( data < 0)
    data++;

  return( data);
}

int process( int tid, int data, int  workload)
{
  int i;

#ifdef OUTPUT
    //printf( "[%d] processing item %d!\n", tid, data);
#endif

  for( i=0; i<workload; i++)
    data = workUnit( data);

#ifdef OUTPUT
   // printf( "[%d] item %d done!\n", tid, data);
#endif

  return( data);
}

void * pipeline( void *arg)
{
  int data;
  int workload;
  int i = 0;
  buffer_t *in;
  buffer_t *out;
  int tid;
  struct timespec startOne, stopOne;
  in = ((threadArgs_t *)arg)->in_buf;
  out = ((threadArgs_t *)arg)->out_buf;
  tid = ((threadArgs_t *)arg)->tid;
  workload = ((threadArgs_t *)arg)->workload;
  while(i<N_DATA)
  {
    if(pop(in, &data) == 1)
    {
      if(tid == 0)
        clock_gettime (CLOCK_REALTIME, &start[i]);
      data = process(tid, data, workload);
      push(out, data);
      if(tid == (2))
      {
        clock_gettime (CLOCK_REALTIME, &stop[i]);
      }
      i++;
    }
  }

}

double xelapsed (struct timespec a, struct timespec b)
{
   return (a.tv_sec - b.tv_sec) * 1000000.0
          + (a.tv_nsec - b.tv_nsec) / 1000.0;
}

void calculateLatency ()
{
  int i;
  for(i = 0; i< N_DATA; i++)
  {
    double tmp = xelapsed(stop[i], start[i]);
    if (tmp<minLatency)
      minLatency = tmp;
    if(tmp>maxLatency)
      maxLatency = tmp;
    if(i == 0)
      avgLatency = tmp;
    else
      avgLatency = (avgLatency + tmp)/2;
  }
   
}

double throughput(double latency)
{
  return 1000000.0/latency;
}
/*******************************************************************************
 ** 
 ** main
 ** 
 ******************************************************************************/

void main(int argc, char *argv[])
{
  int i, suc;
  int data;
  threadArgs_t args[N_THREADS];
  pthread_t threads[N_THREADS];
  buffer_t *in, *inter1, *inter2, *out;
  double tput;

  if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }


  if( argc == 2) {
     N_DATA = atoi( argv[1]);
  }
  in = createBuffer( N_DATA+1);
  inter1 = createBuffer( BUFFER_SIZE);
  inter2 = createBuffer( BUFFER_SIZE);
  out = createBuffer( N_DATA+1);
  
  /**
   *
   * First, we start our threads:
   */
  args[0].in_buf = in;
  args[0].out_buf = inter1;
  args[0].workload = WORKLOAD1;
  args[1].in_buf = inter1;
  args[1].out_buf = inter2;
  args[1].workload = WORKLOAD2;
  args[2].in_buf = inter2;
  args[2].out_buf = out;
  args[2].workload = WORKLOAD3;

  for(i=0;i<N_THREADS;i++){
    pthread_t tid;
    args[i].tid = i;
    int res=(int) pthread_create (&tid, NULL, pipeline, (void *)&args[i]);
    if (res < 0) {
      perror("error creating thread");
      abort();
    }else if (res==0) {

      threads[i]=tid;
      pipeline;
      //printf("Created thread %d \n", i);
    }
  }
  /**
   * Then, we fill the input buffer:
   */

  for(i=0; i<N_DATA;i++)
  {
    push(in, i);
  }

  for(i=0; i<N_THREADS; i++)
  {
    pthread_join (threads[i], NULL); 
  }
  pthread_mutex_destroy(&lock);

  calculateLatency();
  tput = throughput(avgLatency);
  for(i=0; i<N_DATA;i++)
  {
    suc = 0;
    while (suc == 0)
    {
      suc = pop(out, &data);
    }
  }

  printf ("minLatency=%5.0f (mics) maxLatency=%5.0f (mics) avgLatency=%5.0f (mics) throughput=%5.0f \n",
           minLatency, maxLatency, avgLatency, tput);
  printf ("N_DATA=%d ; workload1=%d ; workload2=%d ; workload3=%d \n",
           N_DATA, WORKLOAD1, WORKLOAD2, WORKLOAD3);
}

  

