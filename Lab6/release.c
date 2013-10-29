/**************************************************************************/ 
/* PROGRAM NAME: release.c
/* CLASS: CECS-326
/* INSTRUCTOR: Mr. Haney Williams
/* STUDENT: Steven Le
/* DESCRIPTION: This program releases a lock file by utilizing system calls
/*              and allows processes to communicate with one another.
/**************************************************************************/ 
# include <stdio.h> 
# include <stdlib.h>
# include <fcntl.h> 
# include <errno.h>
# include <sys/types.h> 
# include <sys/stat.h> 

void main(int argc, char *argv[])
{
   char *fname;
   int fd, sleeptime, n_try, count = 0;
   pid_t pid;
   pid = getpid();
   srand((unsigned) pid);

   if(argc != 4)                   // If arguments are not 4 inputs
   {
      printf("Invalid inputs, requires 4 arguments.\n", argv[0]);
      exit(1);
   }
   fname     = argv[1];            // Argument index 1 is filename
   sleeptime = atoi(argv[2]);      // Argument index 2 is sleeptime
   n_try     = atoi(argv[3]);      // Argument index 3 is number of tries
   if (n_try <= 0) // If number of tries is 0 or negative, throw exception
   { 
      printf("Input error.\n");
      printf("Number of tries cannot be 0 or negative.\n"); 
      exit(1); 
   }
   if (sleeptime <= 0) // If sleeptime is 0 or negative, throw exception
   { 
      printf("Input error.\n");
      printf("Sleeptime cannot be 0 or negative.\n"); 
      exit(1); 
   }
   while (unlink(fname)!=0)
   if (++count < n_try)
      sleep(sleeptime);
   else
   {
      printf ("\n Cannot release file\n"); exit(-1);
   }
   printf ("\n File is released\n");
}
