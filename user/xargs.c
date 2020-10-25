#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    char *subArgv[MAXARG];
    for (int i = 1; i < argc; i++)
    {
        subArgv[i - 1] = argv[i];
        // printf("argc=%d, argv=%s\n", i - 1, subArgv[i - 1]);
    }
    argc--;

    char one;
    char buf[100];
    int count = 0;
    while (read(0, &one, sizeof(one)) > 0)
    {
        buf[count++] = one;
        if (one == '\n')
        {
            //fork
            int pid = fork();
            if (pid > 0)
            {
                //append argv in buf
                int start = 0;
                while (buf[start++] == ' ')
                    ;
                int end = start;
                while (end < count)
                {
                    while (buf[end] != ' ' && buf[end] != '\n')
                        end++;
                    buf[end] = 0;
                    subArgv[argc] = malloc(end - start);
                    strcpy(subArgv[argc], &buf[start]);
                    // printf("argc=%d, argv=%s\n", argc, subArgv[argc]);
                    argc++;
                    while (buf[end++] == ' ')
                        ;
                    start = end;
                }
                //exec
                subArgv[argc] = 0;
                exec(subArgv[0], subArgv);
            }
            else
            {
                count = 0;
                wait(&pid);
            }
        }
    }

    exit(0);
}