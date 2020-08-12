#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
void runProcess(char ** cmd){
    int error;
    error = 0;
pid_t pid= fork();

    if (pid == 0) {
        error = execvp(cmd[0], cmd);
        if (error == -1) {
            printf("Command not found (%s)\n", cmd[0]);
            exit(0);
        }

    }
    else {
        waitpid(0,NULL,0);
    }
}
void pipeProcesses1(char ** cmd1, char ** cmd2, char ** cmd3){
 int fd[2];
 int fd1[2];
    pipe(fd);
    pipe(fd1);
    pid_t pid;
    pid=fork();

    if (pid ==0) {
        pid_t pid2= fork();
      if(pid2==0){
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        printf("\n");
       execvp(cmd1[0], cmd1);
      }
    else if(pid2 >0){
        pid_t pid3=fork();
        if(pid3 == 0){
            wait(NULL);
            close(0);
            dup(fd1[0]);
            close(fd1[0]);
            close(fd1[1]);
            execvp(cmd3[0],cmd3);
        }else if(pid3 >0){
        wait(NULL);
         close(0);
        dup(fd[0]);
        close(1);
        dup(fd1[1]);
        close(fd[1]);
        close(fd[0]);
        close(fd1[1]);
        close(fd1[0]);
       
       execvp(cmd2[0], cmd2);}
       }
    } else{
        
    }
  close(fd[0]);
  close(fd[1]);
  close(fd1[0]);
  close(fd1[1]);
}

void pipeProcesses(char ** cmd1, char ** cmd2){

    int fd[2];
    pipe(fd);
    
    pid_t pid;
    pid=fork();

    if (pid ==0) {
        pid_t pid2= fork();
      if(pid2==0){
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        printf("\n");
       execvp(cmd1[0], cmd1);
        //runProcess(cmd1);
   // exit(0);
          
      }
    else if(pid2 >0){
        wait(NULL);
         close(0);
        dup(fd[0]);
        close(fd[1]);
        close(fd[0]);
       
       execvp(cmd2[0], cmd2); }
    } else{
        
    }
  close(fd[0]);
  close(fd[1]);
  
}

void main(){

    char input[256];
    char* temp = NULL;
    char* args[15];
    char* cmd1[5];
    char* cmd2[5];
    char* cmd3[5];
    int i,t,o,j,s, k,pipe_pos,pipe_pos1;
    bool op = false;
    bool yu = false;
    int fd[2];
    
    while(1){
        for (i = 0; i < 15; i++) {
            args[i] = NULL;
        }
        for (i = 0; i < 5; i++) {
            cmd1[i] = NULL;
            cmd2[i] = NULL;
            cmd3[i] = NULL;
}
       // printf("Enter the command:  ");
        fgets(input,255,stdin);
        if (!strncmp(input,"quit",4)) {
            printf("Bye Bye Doctor. See you in phase 2\n");
            exit(0);
        }
        else {
            i = 0;
            temp = strtok(input, " \n");
            
            while ((temp != NULL) && (i < 15)) {
                args[i] = temp;
                temp = strtok(NULL, " \n");
               
                i++;
    }
    for( t=0;t<15;t++){
        if(args[t] == NULL){
            o=t;
            break;
        }
    }
   
   // printf("%d",op);
            j = i - 1;
            pipe_pos = 8;
            for (i = 0; i < j; i++) {
                if (strcmp(args[i],"|") == 0) {
                    pipe_pos = i;
                    op=true;
                   // printf("%d",pipe_pos);
                    s=pipe_pos;
                    
                    break;
                }
            }
           // printf("%d",op);
            if((pipe_pos != 8) && (s+1== 2)){
            for (k =s+1;  k < 15; k++) {
                if (strcmp(args[k],"|") == 0) {
                 pipe_pos1 = k;
                 yu=true;
                 printf("%d",pipe_pos1);
                break;
                }
            }}
          
            for (i = 0; i < pipe_pos; i++) {
                cmd1[i] = args[i];
            }
           
            j = 0;
            k=0;
            if (pipe_pos != 8) {
                for (i = pipe_pos+1; i <3; i++) {
                    if (j < 5){
                        cmd2[j] = args[i];
                        j++;
                    }
                }
              // for(int e=0;e<5;e++){
                 //  printf("%s ",cmd2[e]);
               //}
       
            } 
            if((pipe_pos != 8) && (yu == true)){
            for (i = pipe_pos1+1; i < 15; i++) {
                   if (k < 5){
                       cmd3[k] = args[i];
                        k++;
                    }
              }
int e;
              for(e=0;e<5;e++){
                   printf("%s ",cmd3[e]);}
            }
            
            if(pipe_pos !=8 &&  yu ==true){
                pipeProcesses1(cmd1, cmd2,cmd3);
            }
            else if (pipe_pos != 8) {
               pipeProcesses(cmd1, cmd2);
           }
            else if(pipe_pos == 8) {
              runProcess(cmd1);
          }
        }
    }
}

