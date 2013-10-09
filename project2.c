/**************************************************************************/ 
/* PROGRAM NAME: project2.c						                          */
/* CLASS:        CECS-326						                          */
/* INSTRUCTOR:   Mr. Haney Williams					                      */
/* STUDENTS:     Cody Gildea						                      */
/*               Steven Le						                          */
/* DESCRIPTION: This program utilizes a parent program and child program. */
/**************************************************************************/ 
# include<stdio.h>
# include<stdlib.h>
# include<sys/types.h>
# include<unistd.h>

int addition(int i0, int i1);
int diff(int i0, int i1);
double divide(int i0, int i1);
int  multiply(int i0, int i1);

int main(int argc, char *argv[]) 
{
    int i, i0, i1, m, n, sleeptime, seed; 
    int sum, difference, product;
    double quotient;
    pid_t childpid; 
    if (argc !=4) // If arguments are not 4 inputs
    { 
      printf("Invalid inputs, requires 4 arguments.\n", argv[0]); 
      exit(1); 
    } 
    n = 4;     // Number of processes = 4
    m = atoi(argv[1]);   // Argument index 1 is maximum sleeptime m
    i0 = atoi(argv[2]); // Argument index 2 is first integer
    i1 = atoi(argv[3]); // Argument index 3 is second integer
    if (m > 50 || m <= 0) // If argument m is greater than 50, 0, or negative, throw exception
    { 
      printf("Input error.\n");
      printf("Maximum sleeptime m must be <= 50 and > 0.\n"); 
      exit(1); 
    }
    sum = addition(i0, i1);
    difference = diff(i0, i1);
    quotient = divide(i0, i1);
    product = multiply(i0, i1);
    printf("I am parent process, the maximum sleep time is %d and the two numbers are %d and %d.\n", m, i0, i1); 
    childpid = 0;     // Initialize childpid
    for (i=0; i<n;i++) 
    {
        if (childpid = fork())
        {
           printf("Forked child %d\n", (long)getpid());
           break;
        } 
        if (childpid == -1)
        { 
          perror ("The fork failed.\n"); 
          exit(1); 
        }
 	seed = (int)(getpid() + childpid);
    	srand(seed); 
     	/* since each process has a different childpid, using the childpid 
     	as the seed number will restart the random function. 
     	Therefore, each process will have a different sleeptime 
     	*/ 
    	sleeptime = rand()%m; 
   	sleep(sleeptime); 
       
        switch(i)
        {
         case 0:
              printf("I am child number %d with PID %d, the sum is %d\n", i, (long)getpid, sum); 
              break;
         case 1:
              printf("I am child number %d with PID %d, the difference is %d\n", i, (long)getpid, difference);
              break;
         case 2:
              printf("I am child number %d with PID %d, the quotient is %lf\n", i, (long)getpid, quotient);
              break;
         case 3:
              printf("I am child number %d with PID %d, the product is %d\n", i, (long)getpid, product);
              break;
	 default:
	      printf("An error has occured");
	      exit(1);     
         }    // End switch
    } // End for
    exit(0);
}
int addition(int i0, int i1)
{
    return i0 + i1;   
}
int diff(int i0, int i1)
{
    return i0 - i1;   
}
double divide(int i0, int i1)
{
    return (double)i0 /(double) i1;   
}
int multiply(int i0, int i1)
{
    return i0 * i1;   
}

