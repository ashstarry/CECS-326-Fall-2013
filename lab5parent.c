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
   pid_t pid, w; 
   int status;
   char value[3];
   int N, T;  // N = Number of processes. T = Sleeptime
   
   if(argc != 3) // If arguments are not 3 inputs
   {
      printf("Invalid inputs, requires 3 arguments.\n", argv[0]);
      exit(1);
   }
   N = atoi(argv[1]); // Argument index 1 is number of processes N
   T = atoi(argv[2]); // Argument index 2 is sleeptime T
   
   if (N > 20 || N <= 0) // If argument N is greater than 20, 0, or negative, throw exception
   { 
      printf("Input error.\n");
      printf("Number of processes N must be <= 20 and > 0.\n"); 
      exit(1); 
   }
   if (T > 50 || T <= 0) // If argument T is greater than 50, 0, or negative, throw exception
   { 
      printf("Input error.\n");
      printf("Maximum sleeptime T must be <= 50 and > 0.\n"); 
      exit(1); 
   }
   
   for (N = 0; N < 3; ++N)
   {
      if ((pid = fork()) == 0)
      {
         sprintf(value, "d",N);
         execl("lab5child", "lab5child", T, (char *) 0);
//       execl("lab5child", "lab5child", value, (char *) 0);
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
