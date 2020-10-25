#include "user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

void find(char *path, char *target)
{
    // printf("find: start with %s and %s\n", path, target);
    int fd;
    struct stat st;
    struct dirent de;
    // char buf[50];
    char *p;

    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    //
    switch (st.type)
    {
    case T_DIR:
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {   
            if (strlen(de.name) == 0) return;

            // printf("find: de.name = %s**\n", de.name);
            if (strcmp(de.name, ".") == 0 ||
                strcmp(de.name, "..") == 0)
                continue;
            p = malloc(50);
            strcpy(p, path);
            p[strlen(path)] = '/';
            strcpy(p + strlen(path) + 1, de.name);
            // printf("buf = %d, string = %s\n", buf, buf);

            find(p, target); // recursive
        }
        break;

    case T_FILE:
        for (p = path + strlen(path); p >= path && *p != '/'; p--)
            ;
        p++;
        if (strcmp(p, target) == 0)
        {
            printf("%s\n", path);
        }
        break;

    case T_DEVICE:
        break;
    }

    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("ERROR: invalid arguments.\n");
        exit(1);
    }

    find(argv[1], argv[2]);

    exit(0);
}