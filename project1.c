/**************************************************************************/ 
/* PROGRAM NAME: project1.c
/* CLASS:        CECS-326
/* INSTRUCTOR:   Mr. Haney Williams
/* STUDENTS:     Cody Gildea
/*               Steven Le
/* DESCRIPTION: This program generates a chain of processes
/* using fork(). The number of processes n is a command line argument.
/* Each process sleeps for a random time less than 10 seconds then prints out
/* process ID, parent ID, and child ID
/**************************************************************************/ 
# include<stdio.h>
# include<stdlib.h>
# include<sys/types.h>
# include<unistd.h>
 
int main(int argc, char *argv[])
{
        int i, n;        // i : level of tree  n : height of tree
        pid_t childpid1; // child 1
        pid_t childpid2; // child 2
 
        if(argc != 2)    // Checks for 2 arguments for input
        {
                printf("\nUsage: %s processes\nNot enough arguments.\n", argv[0]);
                exit(1);
        }
        // number of processes
        n = atoi(argv[1]);
 
        // validate if n is greater than 5 or n is zero or negative, flag
        if(n > 5 || n <= 0)
        {
                printf("\nInvalid arguments used. Runtime failed.\n");
                exit(1);
        }
        // formatted display output
        printf("\nLevel\tProcs\tParent\tChild1\tChild2\n ");
        printf("No.\tID\tID\tID\tID\n");
        // initialize childpid's to 0
        childpid1 = 0;
        childpid2 = 0;
        // create binary tree of processes
        for(i=0;i<n;i++)
        {
                if(childpid1 = fork())
                {
                        if(childpid2=fork())
                        {
                                // sleep the child to allow parent to print
                                sleep(i);
                                // display process, parent, and child ID's
                                printf("%d\t%6ld\t%6ld\t%6ld\t%6ld\n",i,(long)getpid(),
                                      (long)getppid(), (long)childpid1, (long)childpid2);
                                // sleep the child to allow parent to print
                                sleep(i);
                                // break when no longer processes are being made
                                if(wait(NULL) > 0) break;
                        }
                        // sleep the child to allow parents to print
                }
 
                // throw error is fork failed
                if(childpid1 == -1 || childpid2 == -1)
                {
                        perror("\nThe fork failed\n");
                        exit(1);
                }
        }
        exit(0);
}
