/****************************************************************/
/*	PROGRAM NAME: lab3.c
/*	CLASS: CECS-326
/*	INSTRUCTOR: Mr. Haney Williams
/*	STUDENT: Steven Le
/*	DESCRIPTION: A process creates a child process and may want
/*  to change the program code the child is executing. There
/*  are 6 system calls under the generalized heading exec. When 
/*  the process issues any exec call, if the call is successful,
/*  the existing process is overlaid with a new set of program
/*  code.
/****************************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

void main(int argc, char *argv[])
{
     if (argc > 1)
     {
        execvp(argv[1], &argv[1]);
        perror ("exec failure");
        exit(1);
     }
     printf("\n Usage: %s text_file\n", *argv);
     exit(1) ;
}
