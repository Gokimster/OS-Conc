#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>

static int *created;

static int no = 4;
static int n = 20;
static int *q;
static int *size;
static int *p1Finished;
static int *p2Finished;

sem_t * sem;

int push(int x, int s[])
{
  sem_wait(sem);
  s[*size] = x;
  *size = *size + 1;
  sem_post(sem);
}

int pop(int s[])
{
  sem_wait(sem);
  int t = s[0];
  int i;
  for(i=0; i < *size-1; i++)
  {
    s[i] = s[i+1];
  }
  *size = *size - 1;
  sem_post(sem);
  return t;
}

void doP1(int s[], int n)
{
  int i;
  for(i = 1; i <= n; i++)
  {
    push(i, s);
  }
  *p1Finished = 1;
}

void doP2(int s[], int n)
{
  int i;
  for(i = -1; i >= -n; i--)
  {
    push(i, s);
  }
  *p2Finished = 1;
}


void main(int argc, char *argv[])
{
  pid_t pids[no];
  int i;
  int j;

  created = mmap(NULL, sizeof *created, PROT_READ | PROT_WRITE, 
                  MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  *created = 0;

  size = mmap(NULL, sizeof *size, PROT_READ | PROT_WRITE, 
                  MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  *size = 0;

  p1Finished = mmap(NULL, sizeof *p1Finished, PROT_READ | PROT_WRITE, 
                  MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  *p1Finished = 0;

  p2Finished = mmap(NULL, sizeof *p2Finished, PROT_READ | PROT_WRITE, 
                  MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  *p2Finished = 0;

  q = mmap(NULL, 300 * (sizeof n), PROT_READ | PROT_WRITE, 
                  MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  sem = mmap(0, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  sem_init(sem,1,1);

for(i=0;i<no;i++){
  if ((pids[i] = fork()) < 0) {
      perror("fork");
      abort();
    } else if (pids[i] == 0) {
      while(*created == 0){}
      if(i == 0)
      {
        doP1(q, n);
        printf("%d\n", *size);
      }
      else
        if(i == 1)
        {
          doP2(q, n);
          printf("%d\n", *size);
        }
        else
          if(i == 2){
            while(!(((*p1Finished + *p2Finished) == 2)&&(*size <= 0)))
            {
              if(*size > 0)
              {
                int x = pop(q);
                printf("Proccess 0 Popped %d\n", x);
              }
            }
          }else 
            {
              while(!(((*p1Finished + *p2Finished) == 2)&&(*size <= 0)))
              {
                if (*size > 0)
                {
                  int x = pop(q);
                  printf("Proccess 1 Popped %d\n", x);
                }
              }
            }
      exit(0);
  }
}
*created = 1;
  /* Wait for children to exit. */
  int status;
  pid_t pid;
  while (no > 0) {
    pid = wait(&status);
    printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
    --no;  // TODO(pts): Remove pid from the pids array.
  }
}