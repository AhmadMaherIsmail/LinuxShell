#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

char array_result[10000];

void* server_handler(void*); 




typedef struct thread_data{
int conn;
}THREAD_DATA;

void runProcess(char ** cmd){
int pipefd[2];
pipe(pipefd);
    int error;
    error = 0;
pid_t pid= fork();

    if (pid == 0) {
close(pipefd[0]);
dup2(pipefd[1],1);
close(pipefd[1]);        
error = execvp(cmd[0], cmd);
        if (error == -1) {
            printf("Command not found (%s)\n", cmd[0]);
            exit(0);
        }

    }
    else {
        waitpid(0,NULL,0);
char buffer[10000];
close(pipefd[1]);
while(read(pipefd[0],buffer,sizeof(buffer))!=0);
//printf("%s",buffer);
strcpy(array_result,buffer);
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
            int pipefd[2];
            pipe(pipefd);
            pid_t pid4;
            pid4 = fork();
            if(pid4==0){
           close(pipefd[0]);
           dup2(pipefd[1],1);
            close(pipefd[1]);
          execvp(cmd3[0],cmd3);
          }
else{
char buffer[5010];
close(pipefd[1]);
while(read(pipefd[0],buffer,sizeof(buffer))!=0);
//printf("%s",buffer);
strcpy(array_result,buffer);
}
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
int pipefd[2];
pipe(pipefd);
pid_t pid3;
pid3 = fork();
if (pid3==0){
close(pipefd[0]);
dup2(pipefd[1],1);
close(pipefd[1]);
execvp(cmd2[0], cmd2);
}else{
char buffer[10000];
close(pipefd[1]);
while(read(pipefd[0],buffer,sizeof(buffer))!=0);
//printf("%s",buffer);
strcpy(array_result,buffer);
}

       
        }
    } else{
        
    }
  close(fd[0]);
  close(fd[1]);
  
}


void main(){
int sockfd=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in s;
struct sockaddr_in c;
s.sin_family=AF_INET;
s.sin_port=htons(5010);
s.sin_addr.s_addr=INADDR_ANY;
int a=bind(sockfd,(struct sockaddr*)&s,sizeof(s));
listen(sockfd,4);
 int t=sizeof(c);

while(1){
    int new_sock=accept(sockfd,(struct sockaddr*)&c,&t);
int pwd = new_sock;
THREAD_DATA data;
data.conn = pwd;
  pthread_t tid;
 // pthread_attr_t attr;
 // pthread_attr_init(&attr);
  //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  pthread_create(&tid, NULL, server_handler, (void*) &data);
pthread_join(tid,NULL);



//pthread_t thread;
       // pthread_attr_t attr; // attribute object for the thread


     //   pthread_attr_init(&attr);


   //     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); // make the thread detachable

        
 //       pthread_create(&thread, &attr, server_handler, (void*) &data);



}

}

void* server_handler(void* arg) {
    
    THREAD_DATA* data = (THREAD_DATA*) arg;

   int conn = data->conn;


    char* temp = NULL;
    char* args[15];
    char* cmd1[5];
    char* cmd2[5];
    char* cmd3[5];
    int i,o,j,sm, k,pipe_pos,pipe_pos1,m;
int count=0;
  //  bool op = false;
   // bool yu = false;
    int fd[2];

char input[255];
    
        for (i = 0; i < 15; i++) {
            args[i] = NULL;
        }
        for (i = 0; i < 5; i++) {
            cmd1[i] = NULL;
            cmd2[i] = NULL;
            cmd3[i] = NULL;
}
       // printf("Enter the command:  ");

int n=read(conn,input,sizeof(input));
printf("%s",input);


for(m=0;m<255;m++){
if(input[m]=='|')
count++;}
//printf("%d",count);





        if (!strncmp(input,"quit",4)) {
            printf("Bye Bye Doctor. See you in phase 4\n");
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
    
   
   // printf("%d",op);
            j = i - 1;
            pipe_pos = 8;
            for (i = 0; i < j; i++) {
                if (strcmp(args[i],"|") == 0) {
                    pipe_pos = i;
                    //op=true;
                   // printf("%d",pipe_pos);
                    sm=pipe_pos;
                    
                    break;
                }
            }
//printf("%d",pipe_pos);
           // printf("%d",op);
            if((count == 2)){
            for (k =sm+1;  k < 15; k++) {
                if (strcmp(args[k],"|") == 0) {
                 pipe_pos1 = k;
                 
                // printf("%d",pipe_pos1);
                break;

                }
            }}
          
            for (i = 0; i < pipe_pos; i++) {
                cmd1[i] = args[i];
            }
          // for(m=0;m<15;m++){
           // if(strcmp(args[m],"|")==0){
          // count++;
           // }
           // }
                      
            j = 0;
            k=0;
            
                if(count == 1){
                for (i = pipe_pos+1; i<15; i++) {
                    if (j < 5){
                        cmd2[j] = args[i];
                        j++;
                    }
                }}else if(count == 2){
              for (i = pipe_pos+1; i<pipe_pos1; i++) {
                    if (j < 5){
                        cmd2[j] = args[i];
                        j++;
                  }
            } }
            if((pipe_pos != 8) && (count == 2)){
            for (i = pipe_pos1+1; i < 15; i++) {
                   if (k < 5){
                       cmd3[k] = args[i];
                        k++;
                    }
              }
}
             
            
            if(pipe_pos !=8 && ( count == 2) ){
                pipeProcesses1(cmd1, cmd2,cmd3);
            }
            else if (pipe_pos != 8 && ( count == 1)) {
               pipeProcesses(cmd1, cmd2);
           }
            else if(pipe_pos == 8) {
              runProcess(cmd1);
          }
write(conn,array_result,strlen(array_result));
bzero(array_result,10000);
    }
    close(conn);
    pthread_exit(NULL);
}
