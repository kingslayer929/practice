#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_BUF 9192

void usage(char *path){
    fprintf(stderr, "%s target_file destination\n", path);
}

int main(int argc, char **argv){
    if(argc != 3){
        usage(argv[0]);
        exit(1);
    }
    int fd_in, fd_out;
    char buf[MAX_BUF];
    int rs;
    fd_in = open(argv[1], O_RDONLY);
    if(!fd_in){
        fprintf(stderr, "open %s error\n", argv[1]);
        exit(1);
    }
    fd_out = open(argv[2], O_CREAT | O_WRONLY, MAX_BUF);
    if(fd_out){
        while(read(fd_in, buf, 1)){
            write(fd_out, buf, 1);
        }
    }else{
        fprintf(stderr, "failed to open/create %s\n", argv[1]);
        exit(1);
    }

    return 0;
}