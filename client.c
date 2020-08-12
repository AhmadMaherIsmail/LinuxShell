#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>

void* send_message(void *t) {
    int conn = *((int*)t);
char bbc[255];
fgets(bbc,255,stdin);
write(conn,bbc,sizeof(bbc));

char buff[10000];
int n=read(conn,buff,sizeof(buff));
printf("%s",buff);
    
    close(conn);
    pthread_exit(0);

}

void main(){
while(1){
void *status=0;
int sockfd=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in s;
s.sin_family=AF_INET;
s.sin_port=htons(5010);
inet_pton(AF_INET,"127.0.0.1",&s.sin_addr);
connect(sockfd,(struct sockaddr*)&s,sizeof(s));
   pthread_t thread;
    pthread_create(&thread, NULL, send_message,(void*) &sockfd);

    pthread_join(thread, &status);
    if (status == 0)
        printf("Thread exited successfully\n");
    else
        printf("Thread exited unsuccessfully\n");
    


}
}
