#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BUF_SIZE = 20;

void ProcessWork() {
  char buffer[BUF_SIZE];
  for (int i = 1; i <= 5; i++)
  {
    sleep(1);
    sprintf(buffer, "PID = %d, count = %d\n", getpid(), i);
    write(1, buffer, strlen(buffer));
  }
}

int main(int argc, const char * argv[]) {
  pid_t pid;
  int N_PROC = 2;

  for (int i = 0; i < N_PROC; i++)
  {
    pid = fork();
    if(pid == 0) {
      ProcessWork();
      exit(0);
    }
  }
}