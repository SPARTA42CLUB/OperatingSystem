#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static void *threadFunc(void *arg)
{
  char *s = (char *)arg;
  printf("%s\n", s);
  return (void*)strlen(s);
}

int main(int argc, char *argv[])
{
  pthread_t tid;
  pthread_attr_t attr;

  void *res;
  int s;

  pthread_attr_init(&attr);
  s = pthread_create(&tid, &attr, threadFunc, "Hello world!");
  if (s != 0)
  {
      perror("pthread_create");
      exit(1);
  }
  printf("Message from main() \n");
  s = pthread_join(tid, &res);
  if (s != 0)
  {
    perror("pthread_join");
    exit(1);
  }

  printf("Thread return %ld\n", (long)res);
  exit(EXIT_SUCCESS);
  
}
