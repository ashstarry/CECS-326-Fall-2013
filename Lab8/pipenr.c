/**************************************************************************/ 
/* PROGRAM NAME: pipea.c
/* CLASS:        CECS-326
/* INSTRUCTOR:   Mr. Haney Williams
/* STUDENT:      Steven Le
/* DESCRIPTION:  This lab utilizes the concept of named and unnamed pipes.
/* USAGE:        "pipea [message]". Child writes message to parent.
/**************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

void main(int argc, char *argv[])
{
   int f_des[2];        // Integer array with 2 values at index 0 and 1.
   static char message[BUFSIZ];
   char buffer[MAX_CANON]; // char Buffer array given in specifications, not utilized
   char *c;             // Given in specifications, not utilized
   int i, k, n;         // Given in specifications, not utilized
   pid_t childpid;      // Given in specifications, not utilized

   if (argc !=2)        // Argument check: must be 2 arguments.  Else, throw exception.
   {
      printf ("Error.  Must have two arguments.\n", *argv);
      exit(1);
   }

/* Generate pipe */

   if (pipe(f_des) == -1)
   {
      perror ("Pipe");
      exit(2);
   }
   switch (fork())
   {
      case -1:
         perror ("Fork");
         exit(3);
      case 0: /* In the parent */
         close(f_des[1]); // If try to close f_des[1], it will error bad file descriptor
         if (write(f_des[1], argv[1], strlen(argv[1])) != -1)
         {
            printf ("Message sent by child: *%s*\n", argv[1]);
            fflush(stdout);
         }
         else
         {
             perror ("Read");
             exit(4);
         }
         break;
     default: /* In the child */
         close(f_des[0]); // If try to close f_des[0], it will error bad file descriptor
         if (read(f_des[0], message, BUFSIZ) != -1)
         {
            printf ("Message received by parent: [%s]\n", message);
            fflush(stdout); // If stdout was open for writing, any unwritten data in its output buffer is written to the file.
         }
         else
         {
            perror ("Write");
            exit(5);
         }
   }
   exit(0);
}
