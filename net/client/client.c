#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <strings.h>
#define MAXLINE 4096
#define SERV_PORT 9877
void str_cli(FILE *fp, int sockfd){
    char sendline[MAXLINE], recvline[MAXLINE];
    while(fgets(sendline, MAXLINE, fp)!=NULL){
        
    }


}

int main(int argc, char **argv)
{
    int sockfd,n;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    if(argc!=2){
        printf("argc is wrong");
    }
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);
    exit(0);
}
