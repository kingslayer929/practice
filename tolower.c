#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
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
    int fd_in, fd_out, readsize;
    char buf[MAX_BUF];
    fd_in = open(argv[1], O_RDONLY);
    fd_out = open(argv[1], O_WRONLY);
    if(!fd_in){
        fprintf(stderr, "open %s error\n", argv[1]);
        exit(1);
    }
    while((readsize = read(fd_in, buf, 1))){
        buf[0] = tolower(buf[0]);
        write(fd_out, buf, 1);
    }

    return 0;
}