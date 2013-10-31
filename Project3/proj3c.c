/**************************************************************************/ 
/* PROGRAM NAME: proj3c.c                                                 */
/* CLASS:        CECS-326                                                 */
/* INSTRUCTOR:   Mr. Haney Williams                                       */
/* STUDENTS:     Cody Gildea                                              */
/*               Steven Le                                                */
/* DESCRIPTION: This program utilizes a parent program and child program  */
/* to demonstrate using 'locks' and 'critical states' with processes.     */
/**************************************************************************/ 
# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h>
# include <sys/wait.h>
# include<sys/stat.h>
# include<errno.h>
# include<fcntl.h>
main(int argc, char *argv[])
{
        pid_t pid, pid_c, w;                                                // For child process
        int ret_value, num_tries, sleeptime, i, status, childNum;       // Ret_value and sleeptime
        char *fname;                                                          // File name
        char *lockfname = "lock1";                                        // Lock file name
        char sleepChar[3];                                                // Sleeptime for execlp
        char value[3];                                                        // Child number for execlp
                
        childNum = atoi(argv[1]);          // Child number from parent 2
        fname = argv[2];                  // File name, argument 3
        num_tries = atoi(argv[3]);        // Number of tries, argument 4
        sleeptime = atoi(argv[4]);        // Max sleeptime, argument 5

        pid = getpid();                // Get the process ID
        srand((unsigned) pid); 
                
                /* Attempt to acquire lock for text file*/
                for (i = 0; i<num_tries;++i)
                {
                        if((pid_c = fork()) == 0)
                        {
                                sprintf(sleepChar, "%d", sleeptime);
                                sprintf(value, "%d", childNum);
                                execlp("acquire", "acquire", value, lockfname, sleepChar, "1", (char*)0);
                        }
                        /* Wait for acquire to finish*/
                        while ((w=wait(&status)) && w != - 1)
                        {
                                if(w != -1) {
                                } 
                        }
                        /* Check status of wait for acquire*/
                        if (status == 0)
                                break;
                        else
                                sleep(rand()%sleeptime);
                }
                /* Print if lockfile was not acquired*/
                 if(i == num_tries)
                 {
                        printf("\nUnable to obtain lockfile\n");
                        //kill(pid_c, value);
                        exit(childNum);
                  }
                
                 /* Call text file*/
                 if ((pid_c = fork()) == 0)
                 {
                        execlp("/bin/cat", "/bin/cat", fname, (char*)0);
                 }
                /* Wait for the text file to finish*/
                 while ((w=wait(&status)) && w != - 1)
                {
                            if(w != -1) {
                        } 
                }
                /* Release lock*/
                 if ((pid_c = fork()) == 0)
                 {
                        sprintf(sleepChar, "%d", sleeptime);
                        execlp("release", "release", lockfname, sleepChar, "1", (char*)0);
                 }
                /* Wait for release to finish*/
                 while ((w=wait(&status)) && w != - 1)
                {
                            if(w != -1) {
                        } 
                }
                 if(status == 0)
                {
                        exit(getpid()&255);
                }
}
