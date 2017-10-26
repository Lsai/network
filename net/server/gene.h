#include <stdio.h>
#include <errno.h>
#define MAXLINE 4096
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
    int errno;
    if(read_cnt<=0){  //the line is first to read
    again:
        if((read_cnt=read(fd, read_buf, sizeof(read_buf)))<0){
            if(errno==EINTR){
                goto again;
            }
            return -1;
        }else if(read_cnt==0)
            return 0;
        read_ptr=read_buf;
    }
    read_cnt--;
    *ptr=*read_ptr++;
    return 1;
}

ssize_t readline(int fd, void *vptr, size_t maxlen){
    ssize_t n, rc;
    char c, *ptr;
    ptr=vptr;
    for(n=1;n<maxlen;n++){
        if((rc=my_read(fd,&c))==1){
            *ptr++=c;
            if(c=='\n')
                break;
        }else if(rc==0){
            *ptr=0;
            return n-1;
        }else 
            return -1;
    }
    *ptr=0;
    return n;
}
