/**************************************************************************/ 
/* PROGRAM NAME: lab5parent.c
/* CLASS: CECS-326
/* INSTRUCTOR: Mr. Haney Williams
/* STUDENT: Steven Le
/* DESCRIPTION: This program utilizes the concept of a parent generating
/* a child process and then overlays it by a call to exec.
/**************************************************************************/ 
# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h> 
# include <stdio.h>

main(void)
{
   pid_t pid, w; int k, status; char value[3];
   for (k=0;k < 3; ++k)
   {
      if ((pid = fork()) == 0)
      {
         sprintf(value, "d",k);
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
