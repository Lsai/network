#include <stdio.h>
#include <strings.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "gene.h"
#include <errno.h>
#define MAXLINE 4096
#define LISTENQ 1024
#define SERV_PORT 9877

void str_echo(int sockfd)
{
    ssize_t n;

    char buff[MAXLINE];
again:
    while((n=read(sockfd, buff, MAXLINE))>0){
        writen(sockfd, buff, n);
    }
    if(n<0&&errno==EINTR)
        goto again;
    else if(n<0)
        printf("str_echo: read_erroe");
}

int main(int argc, void *argv)
{
    int listenfd, connfd;
    struct sockaddr_in cliaddr, servaddr;
    socklen_t clilen;
    listenfd=socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);
    for(;;){
        clilen=sizeof(cliaddr);
        connfd=accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
        if(fork()==0){  // child
            close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        close(connfd);  //parent
    }
}
