#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

make_tokens(char *buff, char *args[]) {
  char *p;
  int pos = 0;
  p = strtok(buff, " ");

  while (p != NULL) {
    args[pos++] = p;
    p = strtok(NULL, " ");
  }
  args[pos] = NULL;
}

void typeline(char *ch, char *fname) {
  int fh;
  char c;

  fh = open(fname, O_RDONLY);
  int op = atoi(ch);

  if(fh == -1)
  {
    printf("FILE NOT FOUND");
    return;
  }


  if (op > 0) {
    int cnt = 0;
    while (read(fh, &c, 1) > 0) {
      if (c == '\n') {
        cnt++;
      }
      if (cnt < op) {
        printf("%c", c);
      }
    }
  }
  else if(strcmp(ch,"-a")==0)
  {
    while(read(fh, &c, 1)>0)
    {
        printf("%c",c);
    }
  }
  else {
    printf("Wrong argument passsed");
  }


  close(fh);
}

int main() {

  char buff[20];
  char *args[20];
  int pid;

  while (1) {

    printf("\nmyshell$ ");
    fgets(buff, 20, stdin);

    buff[strlen(buff) - 1] = '\0';
    make_tokens(buff, args);

    if (strcmp(args[0], "typeline") == 0) {
      typeline(args[1], args[2]);
    } else {
      pid = fork();
      if (pid == 0) {
        if (execvp(args[0], args) == -1) {
          printf("\nWrong command");
        }
      } else {
        wait();
      }
    }
  }

  return 0;
}
