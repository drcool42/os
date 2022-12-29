#include <stdio.h>
#include <string.h>
#include <dirent.h>

void make_token(char *buff, char *args[]);
void lst(char *dname, char *op);

int main()
{

    int pid;
    char buff[20];
    char *args[20];

    while(1)
    {
        printf("\nmyshell$ ");
        fgets(buff,20,stdin);

        buff[strlen(buff)-1] = '\0';
        make_token(buff, args);

        if(strcmp(args[0],"list")==0)
        {
            lst(args[2], args[1]);
        }
        else {

            pid = fork();
            if(pid==0)
            {
                if(execvp(args[0],args) == -1)
                {
                    printf("WRONG COMMAND");
                }
            }
            else {
                wait();
            }
        }


    }

    return 0;
}

void make_token(char *buff, char *args[])
{
    char *p;
    int pos=0;

    p = strtok(buff, " ");

    while(p != NULL)
    {
        args[pos++] = p;
        p = strtok(NULL, " ");
    }
    args[pos] = NULL;
}

void lst(char *dname, char *op)
{
    struct dirent *dir;
    DIR *d;

    d =  opendir(dname);


    if(strcmp(op,"n")==0)
    {
        int count=0;
        while((dir = readdir(d)) != NULL)
        {
            count++;
        }
        printf("\nCount is %d",count);
    }
    else if(strcmp(op,"a")==0)
    {
        while((dir = readdir(d)) != NULL)
        {
            printf("%s\n",dir->d_name);
        }
    }
    //dir->d_ino;
    closedir(d);
}
