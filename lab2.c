/**************************************************************************/ 
/* PROGRAM NAME: lab2.c
/* CLASS: CECS-326
/* INSTRUCTOR: Mr. Haney Williams
/* STUDENT: Steven Le
/* DESCRIPTION: This program generates a chain of processes
/* using fork(). The number of processes n is a command line argument.
/* Each process sleeps for a random time less than 10 seconds then prints out
/* process ID, parent ID, and child ID
/**************************************************************************/ 
# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h> 
int main(int argc, char *argv[]) 
{
    int i, m, n, sleeptime, seed; 
    pid_t childpid; 
    if (argc !=3) 
    { 
      printf("Usage: %s processes\n", argv[0]); 
      exit(1); 
    } 
    n = atoi(argv[1]);  // Argument index 1 is number of processes n
    m = atoi(argv[2]);  // Argument index 2 is maximum sleeptime m
    if (n > 9) // If argument n is greater than 10, throw exception
    { 
      printf("Input error.\n");
      printf("Number of processes n must be less than 10.\n"); 
      exit(1); 
    }
    if (m > 19) // If argument m is greater than 20, throw exception
    { 
      printf("Input error.\n");
      printf("Maximum sleeptime m must be less than 20.\n"); 
      exit(1); 
    }
    childpid = 0; 
    for (i=0; i<n;i++) 
        if (childpid = fork()) break; 
    if (childpid == -1)
    { 
      perror ("The fork failed.\n"); 
      exit(1); 
    } 
    printf("%d: process ID:%6ld parent ID:%6ld child ID:%6ld\n",i, (long)getpid(), (long)getppid(), (long)childpid); 
    seed = (int)(getpid() + childpid);
    srand(seed); 
     /* since each process has a different childpid, using the childpid 
     as the seed number will restart the random function. 
     Therefore, each process will have a different sleeptime 
     */ 
    sleeptime = rand()%m; 
    printf (" sleep = %d\n", sleeptime); 
    sleep(sleeptime);  
    exit(0); 
}
