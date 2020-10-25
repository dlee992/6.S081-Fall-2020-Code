/*
**
*/
#include "user.h"

void child(int fd[2])
{
    close(fd[1]);
    int i, prime;
    int recCount = 0, sendCount = 0;
    int newfd[2];
    int pid;
    while (read(fd[0], &i, sizeof(i)) != 0)
    {
        if (recCount == 0)
        {
            prime = i;
            printf("prime %d\n", prime);
            recCount++;
        }
        else if (i % prime != 0)
        {
            if (sendCount == 0)
            {
                pipe(newfd);
                pid = fork();
                if (pid > 0)
                    child(newfd);
                else
                {
                    close(newfd[0]);
                    write(newfd[1], &i, sizeof(i));
                    sendCount++;
                }
            }
            else
            {
                write(newfd[1], &i, sizeof(i));
            }
        }
    }
    close(fd[0]);
    close(newfd[1]);
    wait(&pid);
}

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    int pid = fork();
    if (pid > 0)
    {
        child(fd);
    }
    else
    {
        close(fd[0]);
        for (int i = 2; i <= 35; i++)
            write(fd[1], &i, sizeof(i));
        close(fd[1]);
        wait(&pid);
    }

    exit(0);
}