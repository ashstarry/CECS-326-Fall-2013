/**************************************************************************/ 
/* PROGRAM NAME: project3child.c
/* CLASS: CECS-326
/* INSTRUCTOR: Mr. Haney Williams
/* STUDENT: Steven Le
/* DESCRIPTION: This program utilizes the concept of a parent generating
/*              a child process and then overlays it by a call to exec.
/*              The parent program passes the sleep time T to the child process.
/*              The child process sleeps for a random time modulo T.
/**************************************************************************/ 
# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h> 
# include <sys/wait.h>

int main(int argc, char *argv[])
{
   pid_t pid; int ret_value;
   int T;                  // Variable T = sleeptime passed from parent
   T = atoi(argv[2]);      // Argument index 1 is maximum sleeptime T
   pid = getpid();
   ret_value = (int) (pid %256);
   srand((unsigned) pid);
   sleep(rand() % T);
   if (atoi(*(argv + 1)) %2)
   {
      printf("Child %d is terminating with signal 009\n", pid);
      kill(pid, 9);
   }
   else
   {
       printf("Child %d is terminating with exit(%04X)\n", pid, ret_value);
       exit(ret_value);
   }
}
