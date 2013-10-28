#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void main(void)
{
    pid_t pid, w;
    int k, status;
    char value[3];
    for (k=0;k < 3; ++k) 
    {
       if ((pid = fork()) == 0) 
       { 
          sprintf(value, "%d",k);
          execl("child", "child", value, (char *) 0);
       }
       else
       printf ("Forked child %d\n", pid);
    }
    /* Wait for children */
    while ((w = wait(&status)) && w != - 1)
    {
       if (w != - 1)
       printf ("Wait on PID: %d returns status of: %04X\n", w, status);
    }
    exit(0);
}
