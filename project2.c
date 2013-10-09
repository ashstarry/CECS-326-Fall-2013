/**************************************************************************/ 
/* PROGRAM NAME: project2.c
/* CLASS:        CECS-326
/* INSTRUCTOR:   Mr. Haney Williams
/* STUDENTS:     Cody Gildea
/*               Steven Le
/* DESCRIPTION: This program utilizes a parent program and child program.
/**************************************************************************/ 
# include<stdio.h>
# include<stdlib.h>
# include<sys/types.h>
# include<unistd.h>

int main(int argc, char *argv[]) 
{
    int i, i0, i1, m, n, sleeptime, seed; 
    pid_t childpid; 
    if (argc !=4) // If arguments are not 4 inputs
    { 
      printf("Invalid inputs, require 4 arguments.\n", argv[0]); 
      exit(1); 
    } 
    n = 4;     // Number of processes = 4
    m = atoi(argv[1]);   // Argument index 1 is maximum sleeptime m
    i0 = atoi(argv[2]); // Argument index 2 is first integer
    i1 = atoi(argv[3]); // Argument index 3 is second integer
    if (m > 50 || m <= 0) // If argument m is greater than 50, 0, or negative, throw exception
    { 
      printf("Input error.\n");
      printf("Maximum sleeptime m must be < 50 and > 0.\n"); 
      exit(1); 
    }
    printf("I am parent process, the maximum sleep time is %d and the two numbers are %d and %d.\n", m, i0, i1); 
    childpid = 0;     // Initialize childpid
    for (i=0; i<n;i++) 
        if (childpid = fork())
        {
           printf("Forked child %d\n", (long)childpid);
           break;
        } 
    if (childpid == -1)
    { 
      perror ("The fork failed.\n"); 
      exit(1); 
    } 
    printf("%d: process ID:%6ld parent ID:%6ld child ID:%6ld",i, (long)getpid(), (long)getppid(), (long)childpid); 
    seed = (int)(getpid() + childpid);
    srand(seed); 
     /* since each process has a different childpid, using the childpid 
     as the seed number will restart the random function. 
     Therefore, each process will have a different sleeptime 
     */ 
    sleeptime = rand()%m; 
    sleep(sleeptime);  
    printf (" sleep = %d\n", sleeptime);
    exit(0);
}
