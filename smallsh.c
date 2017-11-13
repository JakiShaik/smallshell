#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>

int main(int argc,char * argv[]) {
  char * input = NULL;
  size_t inputlength = 0;
  int noofcharsread;
  char * startcwd;
  //memset(startcwd,'\0',400);                                                                                                                                                                              
  while(1) {
    printf(": ");
    noofcharsread = getline(&input,&inputlength,stdin);
    input[strcspn(input, "\n")]='\0';
    if(strcmp(input,"status") >= 0) {
      printf("it is in status\n");
    }
    else if (strcmp(input,"cd") == 0) {
      startcwd = getcwd(0,0);
      printf("it is in cd and cwd is %s\n",startcwd);
      if(argc == 1) {
        printf("arg is %s\n",argv[0]);
        execlp("cd","cd",NULL);
      }
      else {
        printf("argc is %d\n",argc);
        argv[argc] = NULL;
        execvp(argv[0],argv);
      }

    }
    else if(strcmp(input,"ls") == 0)  {
      pid_t lspid=fork();
      if(lspid == -1) {perror("lspid()");exit(1);}
      if(lspid == 0) {
      execlp("ls","ls",NULL);
      }
      int inttocheck;
      lspid = waitpid(lspid,&inttocheck,WNOHANG);
    }
    else if (strcmp(input,"exit")==0) {
        free(input);
        input = NULL;
        exit(0);
      }
    else {
      printf("command not found\n");
    }
  }

}
