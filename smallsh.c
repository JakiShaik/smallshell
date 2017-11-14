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
  char * found;
  char ** inputarr;
  //memset(startcwd,'\0',400);                                                                                                                                                                              
  while(1) {
    printf(": ");
    noofcharsread = getline(&input,&inputlength,stdin);
    //printf("user input is %s\n",input);                                                                                                                                                                   
    input[strcspn(input, "\n")]='\0';
    printf("user input is %s\n",input);
    while((found = strsep(&input," ")) != NULL)
      printf("%s\n",found);
    printf("input after strsep is %s\n",input);
    if(strcmp(input,"status") == 0) {
      printf("it is in status\n");
    }
    else if (strcmp(input,"cd") == 0) {
      startcwd = getcwd(0,0);
      printf("it is in cd and cwd is %s\n",startcwd);
      if(argc == 1) {
        printf("arg is %s\n",argv[0]);
        chdir("/nfs/stak/users/shaikj");
        //pid_t cdpid = fork();                                                                                                                                                                             
        //printf("cdpid is %d\n",cdpid);                                                                                                                                                                    
        //if(cdpid == 0) {                                                                                                                                                                                  
        //printf("it is in child process\n");                                                                                                                                                               
          //execlp("cd","cd",NULL);                                                                                                                                                                         
          //chdir("~");                                                                                                                                                                                     
        //}                                                                                                                                                                                                 
        //int inttocheckcd;                                                                                                                                                                                 
        //cdpid = waitpid(cdpid,&inttocheckcd,0);                                                                                                                                                           
      }
      else {
        printf("argc is %d\n",argc);
        //argv[argc] = NULL;                                                                                                                                                                                
        printf("argv[1] is %s\n",argv[1]);
        chdir(argv[1]);
        //pid_t cdspid = fork();                                                                                                                                                                            
        //if(cdspid == 0) {                                                                                                                                                                                 
        //execvp(argv[0],argv);                                                                                                                                                                             
        //}                                                                                                                                                                                                 
        //int inttocheckcd;                                                                                                                                                                                 
        //cdspid = waitpid(cdspid,&inttocheckcd,0);                                                                                                                                                         
      }

    }
    else if(strcmp(input,"ls") == 0)  {
      pid_t lspid=fork();
      if(lspid == -1) {perror("lspid()");exit(1);}
      if(lspid == 0) {
      execlp("ls","ls",NULL);
      }
      int inttocheck;
      lspid = waitpid(lspid,&inttocheck,0);
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

