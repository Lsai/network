#include <stdio.h>
#include <errno.h>
ssize_t readn(int fd, void *vptr, size_t n){
    char *ptr;
    size_t nleft;
    ssize_t nread;
    int errno;
    ptr=vptr;
    nleft=n;
    while(nleft>0){
        if(nread=read(fd, ptr, nleft)<0){
            if(errno==EINTR){
                nread=0;
            }else{
                return -1;
            }
        }else if(nread==0){
            break;
        }
        nleft-=nread;
        ptr+=nread;
    }
    return n-nleft;
}

ssize_t writen(int fd, const void *vptr, size_t n){
    ssize_t nwrite;
    size_t nleft; int errno;
    const char *ptr;
    ptr=vptr;
    nleft=n;
    while(nleft>0){
        if((nwrite=write(fd, ptr, nleft)<=0)){
            if(nwrite<0&&errno==EINTR){
                nwrite=0;
            }else
                return -1;
        }
        nleft-=nwrite;
        ptr+=nwrite;
    }
    return n;
}

static int read_cnt;
static char *read_ptr;
static char read_buf[MAXLINE];

static ssize_t my_read(int fd, char *ptr){
    if(read_cnt<=0){  //the line is first to read
    again:
        if((read_cnt=read(fd, ptr, sizeof(ptr))))
    }
}
