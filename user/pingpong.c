/*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*/
#include "user.h"

int main(int argc, char *argv[])
{
    //0 for read, 1 for write
    int to[2], from[2];
    pipe(to);
    pipe(from);
    char *buf = malloc(1);

    if (fork() == 0) {
        close(to[1]);
        close(from[0]);
        read(to[0], buf, 1);
        printf("%d: received ping\n", getpid());
        write(from[1], buf, 1);
        free(buf);
        exit(0);
    }
    
    close(to[0]);
    close(from[1]);
    write(to[1], buf, 1);
    read(from[0], buf, 1);
    free(buf);
    printf("%d: received pong\n", getpid());
    exit(0);
}