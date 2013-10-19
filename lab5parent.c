/**************************************************************************/ 
/* PROGRAM NAME: lab5parent.c
/* CLASS: CECS-326
/* INSTRUCTOR: Mr. Haney Williams
/* STUDENT: Steven Le
/* DESCRIPTION: Modify the parent program to receive command line arguments:
/*              N (number of child processes) and T (sleep time).
/*              N must be less than 20 and T must be less than 50. 
/*              The parent program passes the sleep time T to the child process.
/8              The child process sleeps for a random time modulo T.
/**************************************************************************/ 
# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h> 
# include <stdio.h>

int main(int argc, char *argv[])
{
   pid_t pid, w; int k, status; char value[3];
   int N, T;  // N = Number of processes. T = Sleeptime
   
   if(argc != 3) // If arguments are not 3 inputs
   {
      printf("Invalid inputs, requires 3 arguments.\n", argv[0]);
      exit(1);
   }
   for (k=0;k < 3; ++k)
   {
      if ((pid = fork()) == 0)
      {
         sprintf(value, "d",k);
         execl("lab5child", "lab5child", value, (char *) 0);
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
