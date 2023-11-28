#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
  if(argc == 1)
    {
      printf("Usage: %s <exec command> , [arg0, arg1, arg2, ...]\n", argv[0]);
      return 1;
    }

  pid_t pid = fork();

  if(pid < 0)
    {
      perror("fork error");
      return 1;
    }

  if(pid == 0)
    {
      execvp(argv[1], argv+1);
      perror("execvp error");
      exit(EXIT_FAILURE);
    }
  else
    {
      int status;
      waitpid(pid, &status, 0);

      if(WIFEXITED(status))
      {
        printf("자식 프로세스가 상태 %d로 종료됨.\n", WEXITSTATUS(status));
      }
      else if(WIFSIGNALED(status))
      {
        printf("자식 프로세스가 시그널 %d에 의해 종료됨.\n", WTERMSIG(status));
      }
      else{
        printf("자식 프로세스가 비정상적으로 종료됨.\n");
      }
    }
  return 0;
}

