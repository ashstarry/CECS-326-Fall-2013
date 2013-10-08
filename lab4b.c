/**************************************************************************/ 
/* PROGRAM NAME: lab4a.c
/* CLASS: CECS-326
/* INSTRUCTOR: Mr. Haney Williams
/* STUDENT: Steven Le
/* DESCRIPTION: This program utilizes the concept of a parent generating
/* a child process and then overlays it by a call to exec.
/**************************************************************************/ 
# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h> 
# include <stdio.h>
# include <unistd.h>
void main()
{
    static char *mesg[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    int display(char *), i;
    for (i=0; i<10; ++i)
        display(mesg[i]);
    sleep(2);
}
int display(char *m)
{
    char err_msg[25];
    switch (fork())
    {
           case 0: // Replace with non-existing directory to check for results
                execlp("/righteous", "echo", m, (char *) NULL);
                sprintf (err_msg, "%s Exec failure", m);
                perror(err_msg); return(1);
           case -1:
                perror ("Fork failure"); return(2);
           default:
                return(0);
    }
}
