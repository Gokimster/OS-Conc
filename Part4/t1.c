#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define N_THREADS 3
#define BUFFER_SIZE 200
#define N_DATA 3//100000
#define WORKLOAD1 100000
#define WORKLOAD2 100000
#define WORKLOAD3 100000
#define OUTPUT 50

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
    printf( "[%d] processing item %d!\n", tid, data);
#endif

  for( i=0; i<workload; i++)
    data = workUnit( data);

#ifdef OUTPUT
    printf( "[%d] item %d done!\n", tid, data);
#endif

  return( data);
}

void * pipeline( void *arg)
{
  printf("in pipeline \n");
  int data;
  int workload;
  int suc;
  buffer_t *in;
  buffer_t *out;
  int tid;
  printf("DAFUK \n");
  in = ((threadArgs_t *)arg)->in_buf;
  out = ((threadArgs_t *)arg)->out_buf;
  tid = ((threadArgs_t *)arg)->tid;
  workload = ((threadArgs_t *)arg)->workload;
  printf("tail %d, head", in->tail);
  while((in->tail < (N_DATA - 1))||(in->tail != in->head))
  {
    printf("tail %d head %d", in->tail, in->head);
    printf("in while pipe \n");
    if(pop(in, &data) == 1)
    {
      data = process(tid, data, workload);
      push(out, data);
      printf("pushing \n");
    }
  }
  printf("DONE YO \n");

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
    int res=(int) pthread_create (&tid, NULL, pipeline, NULL);
    if (res < 0) {
      perror("error creating thread");
      abort();
    }else if (res==0) {

      threads[i]=tid;
      printf("Created thread %d \n", i);
      printf("y u no %d \n", i);
    }
  }
  /**
   * Then, we fill the input buffer:
   */

  for(i=0; i<N_DATA;i++)
  {
    push(in, i);
  }

  printf("PUSHED SHIT %d \n", i);
  for(i=0; i<N_THREADS; i++)
  {
    //pthread_join (threads[i], NULL); 
    printf("done"); 
  }

  for(i=0; i<N_DATA;i++)
  {
    suc = pop(out, &data);
    printf("NOTHING");
    if (suc == 1)
      printf("Popped %d from output", data);
  }
}

  

