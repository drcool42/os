#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void make_toks(char *s, char *tok[])
{
    int i = 0;
    char *p;
    p = strtok(s, " ");
    while (p != NULL)
    {
        tok[i++] = p;
        p = strtok(NULL, " ");
    }
    tok[i] = NULL;
}

void l_DIR(char *dir_name, char *op)
{
    int count = 0;
    DIR *d;
    struct dirent *dir;
    d = opendir(dir_name);
    if (d)
    {

  

        if (*op == 'f')
        {
            while ((dir = readdir(d)) != NULL)
            {
                printf("%s\n", dir->d_name);
            }
        }
        else if (*op == 'n' )
        {
            while ((dir = readdir(d)) != NULL)
            {
                count++;
            }
            printf("No of entries: %d\n", count - 2);
        }
        else if (*op == 'i')
        {
            struct stat buf;
            while ((dir = readdir(d)) != NULL)
            {
                //fstat(dir->d_name, &buf);
                printf("%d %s\n",dir->d_ino,dir->d_name);
            }
        }

        closedir(d);
    }
}

int main()
{
    char buff[80], *args[10];
    int pid;
    while (1)
    {
        printf("myshell$");
        fflush(stdin);
        fgets(buff, 80, stdin);
        buff[strlen(buff) - 1] = '\0';
        make_toks(buff, args);

        if (strcmp(args[0], "list") == 0)
            l_DIR(args[2], args[1]);

        else
        {
            pid = fork();
            if (pid > 0)
                wait();
            else
            {
                if (execvp(args[0], args) == -1)
                    printf("Bad command.\n");
            }
        }
    }
    return 0;
}
