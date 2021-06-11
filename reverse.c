#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_BUF 1024

void usage(char *path){
    fprintf(stderr, "usage:\n");
    fprintf(stderr, "%s filename\n", path);
}

int main(int argc, char **argv){
    if(argc != 2){
        usage(argv[0]);
        exit(1);
    }
    int fd, fd_tmp;
    char buf[MAX_BUF];
    fd = open(argv[1], O_RDWR);
    if(!fd){
        fprintf(stderr, "open %s error\n", argv[1]);
        exit(1);
    }
    fd_tmp = open("tmpForReverse.txt", O_CREAT | O_RDWR, MAX_BUF);
    if(fd_tmp){
        while(read(fd, buf, 1)){
            write(fd_tmp, buf, 1);
        }   
    }else{
        fprintf(stderr, "failed to summon tmp file\n");
        exit(1);
    }
    lseek(fd, -1, SEEK_END);
    lseek(fd_tmp, 0, SEEK_SET);
    while(read(fd_tmp, buf, 1)){
        write(fd, buf, 1);
        lseek(fd, -2, SEEK_CUR);
    }
    unlink("tmpForReverse.txt");

    return 0;
}