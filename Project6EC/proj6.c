/**************************************************************************/ 
/* PROGRAM NAME: proj6.c                                                  */
/* CLASS:        CECS-326                                                 */
/* INSTRUCTOR:   Mr. Haney Williams                                       */
/* STUDENTS:     Cody Gildea                                              */
/*               Steven Le                                                */                                            
/* DESCRIPTION: This program utilizes creating pipes                      */
/**************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h> 


# define BUFSIZE 256 
void main(int argc, char *argv[]) 
{ 
    mode_t fifo_mode = S_IRUSR | S_IWUSR;       // Declare the mode for the pipe (FIFO)
    int fd, status, child, order, i, j;         
    char buf[BUFSIZE];                          // For the buffer to send through the pipe
    unsigned strsize;                           // For a string size
    char *inputMessage;                         // For the input message
    char *pipeName;                             // For pipe name
    
    if (argc < 4 || argc > 5) 
    /* Check that there is 4 or 5 arguments */
    { 
        printf ("\n Invalid input. Arguments must be 4 or 5\n"); 
        exit(1);
    }
    if(strcmp(argv[1], "n") == 0)
    /* If argument 2 is 'n' for named pipe */
    {
        if (argc != 5) 
        /* Check input arguments are exactly 5 */
        { 
            printf ("\n Arguments must be 5 when using a named pipe.\n"); 
            exit(1);
        }
        if (strlen(argv[4]) > 32)
        /* If the message is greater than 32 */
        {
            printf ("\nInvalid input. The message cannot have a length greater than 32.\n"); 
            exit(1);
        } 
        if (strcmp(argv[3], "c") == 0) /* child -> parent */                
        {
            order = 0;
        }
        else if (strcmp(argv[3], "p") == 0) /* parent -> child */
        {
            order = 1;
        }
        else
        /* Throw error if the 4th argument is not 'c' or 'p' */
        {
            printf("\nInvalid input for the order of the pipe.\n");
            exit(1);
        }
        
        pipeName = argv[2];             // Set the pipeName to the 3rd argument if 'n' is an option
        inputMessage = argv[4];         // Set the inputMessage to the 5th argument
    }
    else if(strcmp(argv[1], "u") == 0)
    {
        if (argc != 4) 
        /* Check input arguments are exactly 4 */
        { 
            printf ("\n Arguments must be 4 when using a non named pipe.\n"); 
            exit(1);
        } 
        if (strlen(argv[3]) > 32)
        /* If the message is greater than 32 */
        {
            printf ("\nInvalid input. The message cannot have a length greater than 32.\n"); 
            exit(1);
        } 
        if (strcmp(argv[2], "c") == 0) /* child -> parent */                
        {
            order = 0;
        }
        else if (strcmp(argv[2], "p") == 0) /* parent -> child */
        {
            order = 1;
        }
        else
        {
        /* Throw error if the 4th argument is not 'c' or 'p' */
            printf("\nInvalid input for the order of the pipe.\n");
            exit(1);
        }

        inputMessage = argv[3];         // Set the inputMessage to the 4th argument      
        pipeName = "FIFO";              // Set the pipeName to a defaul anme 'FIFO' if 'u' is an option
    }
    else
    /* Throw an error if the second argument is not 'n' or 'u' */
    {
        printf("\nInvalid input for the second argument. %s should be 'n' or 'u'.\n", argv[1]);
        exit(1);
    }

    /* generate a named pipe with r/w for user */  /* Make a FIFO special file */ 
    if ((mkfifo(pipeName,fifo_mode) == -1) && (errno != EEXIST)) /* EEXIST -> file already exists*/
        /* success: 0, failure: -1, sets errno. mkfifo 
        creates the FIFO file referenced by path; mode: File mode bits: 
        S_IRUSR read permission, owner. S_IWUSR write permission, owner */
    { /* Pipe error*/
        perror ("Pipe"); 
        exit(1); 
    } 
    

    if (order == 0) /* child -> parent */ 
    {
        if (( child = fork()) == -1) 
        { /* Fork error*/
            perror ("Fork"); 
            exit(1); 
        } 
        else if (child == 0)
        { 
            printf ("\nChild %ld is about to send the message [%s] to %s", (long)getpid(), inputMessage, pipeName); 
            if ((fd = open(pipeName, O_WRONLY)) == -1) /* Open for writing only*/
            { /* Open error*/
                perror("\nChild cannot open FIFO"); 
                exit(1);
            } 
            /* Run through the inputMessage and change its case to the opposite of what was inputed */
            for(i=0;i<=strlen(inputMessage);i++)
            {
                if(inputMessage[i]>=65&&inputMessage[i]<=90)
                    inputMessage[i]=inputMessage[i]+32;
                else if (inputMessage[i]>=97&&inputMessage[i]<=122)
                    inputMessage[i]=inputMessage[i]-32;
            }
            /* In the child */ 
            sprintf (buf, "*%s* from child %ld", inputMessage, (long)getpid()); 
            strsize = strlen(buf) + 1; 
            if (write(fd, buf, strsize) != strsize) 
                /* success: number of bytes written, 
                failure: -1, sets errno. Write nbyte bytes from the buffer 
                referenced by buf using the file descriptor pecified by filedes. */
            { /* Write error*/
                printf("\nChild write to FIFO failed"); 
                exit(1); 
            } 
            printf ("\nMessage sent.\n"); 
        } 
        else 
        { 

        /* parent does a read */ 
            if ((fd = open(pipeName, O_RDONLY | O_NONBLOCK)) == -1) /* Open for reading only*/
            { /* Open error*/
                perror("\nParent cannot open FIFO"); 
                exit(1); 
            } 
            while ((wait(&status) == -1) && (errno == EINTR)); /* EINTR -> interrupted system call*/
            printf ("\nParent is about to read the message from %s", pipeName); 
            
                if (read(fd, buf, BUFSIZE) <=0) 
                /* success: number of bytes read, failure: -1, sets errno. 
                All reads are initiated from current position. Read nbyte bytes 
                from the open file associated with the file descriptor filedes 
                into the buffer referenced by buf. */
                { /* Read error*/
                    perror("\nParent read from FIFO failed");
                    exit(1); 
                } 
            printf ("\nParent receives the message %s\n", buf); 
        }      
    } 
    else if (order == 1) /* parent -> child */
    {
         if (( child = fork()) == -1) 
        { /* Fork error*/
            perror ("Fork"); 
            exit(1); 
        } 
        else if (child == 0)
        { 
            /* child does a read */ 
            if ((fd = open(pipeName, O_RDONLY | O_NONBLOCK)) == -1) /* Open for reading only*/
            { /* Open error*/
                perror("\nChild cannot open FIFO"); 
                exit(1); 
            } 
            while ((wait(&status) == -1) && (errno == EINTR)); /* EINTR -> interrupted system call*/
            printf ("\nChild %ld is about to read the message from %s", (long)getpid(), pipeName); 
            
                if (read(fd, buf, BUFSIZE) <=0) 
                /* success: number of bytes read, failure: -1, sets errno. 
                All reads are initiated from current position. Read nbyte bytes 
                from the open file associated with the file descriptor filedes 
                into the buffer referenced by buf. */
                { /* Read error*/
                    perror("\nChild read from FIFO failed");
                    exit(1); 
                } 
            printf ("\nChild %ld receives the message %s\n", (long)getpid(), buf);
        } 
        else 
        { 
            printf ("\nParent is about to send the message [%s] to %s", inputMessage, pipeName); 
            if ((fd = open(pipeName, O_WRONLY)) == -1) /* Open for writing only*/
            { /* Open error*/
                perror("\nParent cannot open FIFO"); 
                exit(1);
            } 
            /* Run through the inputMessage and change its case to the opposite of what was inputed */
            for(i=0;i<=strlen(inputMessage);i++)
            {
                if(inputMessage[i]>=65&&inputMessage[i]<=90)
                    inputMessage[i]=inputMessage[i]+32;
                else if (inputMessage[i]>=97&&inputMessage[i]<=122)
                    inputMessage[i]=inputMessage[i]-32;
            }
            /* In the parent */ 
            sprintf (buf, "*%s* from parent", inputMessage); 
            strsize = strlen(buf) + 1; 
            if (write(fd, buf, strsize) != strsize) 
                /* success: number of bytes written, 
                failure: -1, sets errno. Write nbyte bytes from the buffer 
                referenced by buf using the file descriptor pecified by filedes. */
            { /* Write error*/
                printf("\nParent write to FIFO failed"); 
                exit(1); 
            } 
            printf ("\nMessage sent.\n"); 
        }
    }
    exit(0); 
}
