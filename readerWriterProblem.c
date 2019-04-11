#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex, writeblock;
int data = 0, rcount = 0;

void *reader(void *arg)
{
  int f;
  f = ((int)arg);
  sem_wait(&mutex);
  rcount = rcount + 1;
  if (rcount == 1)
    sem_wait(&writeblock);
  sem_post(&mutex);
  printf("Data read by the reader%d is %d\n", f, data);
  sleep(1);
  sem_wait(&mutex);
  rcount = rcount - 1;
  if (rcount == 0)
    sem_post(&writeblock);
  sem_post(&mutex);
}

void *writer(void *arg)
{
  int f;
  f = ((int) arg);
  sem_wait(&writeblock);
  data++;
  printf("Data writen by the writer%d is %d\n", f, data);
  sleep(1);
  sem_post(&writeblock);
}

int main()
{
  int i, b;
  pthread_t rtid[100], wtid[100];
  int r,w;
  printf("Enter the number of readers: ");
  scanf("%d",&r);
  printf("Enter the number of writers: ");
  scanf("%d",&w);
  sem_init(&mutex, 0, 1);
  sem_init(&writeblock, 0, 1);
  for (i = 0; i <= w-1; i++)
  {
    pthread_create(&wtid[i], NULL, writer, (void *)i);
    // pthread_create(&rtid[i], NULL, reader, (void *)i);
  }
  for (i = 0; i <= r-1; i++)
  {
    // pthread_create(&wtid[i], NULL, writer, (void *)i);
    pthread_create(&rtid[i], NULL, reader, (void *)i);
  }
  for (i = 0; i <= w-1; i++)
  {
    pthread_join(wtid[i], NULL);
    // pthread_join(rtid[i], NULL);
  }
  for (i = 0; i <= r-1; i++)
  {
    // pthread_join(wtid[i], NULL);
    pthread_join(rtid[i], NULL);
  }
  return 0;
}