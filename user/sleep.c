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
    if (argc == 1)
    {
        char str[] = "ERROR: must provide ticks.\n";
        write(2, str, sizeof(str));
        exit(1);
    }

    int ticks = atoi(argv[1]);
    sleep(ticks);
    exit(0);
}