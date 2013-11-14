/**************************************************************************/ 
/* PROGRAM NAME: proj4.c
/* CLASS:        CECS-326
/* INSTRUCTOR: Mr. Haney Williams
/* STUDENT: Steven Le
/* DESCRIPTION: 
/**************************************************************************/ 

# include <stdio.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>
# include <unistd.h>
# include <stdlib.h>
# define NS 3

union semun
{
   int val;
   struct semid_ds *buf;
   ushort *array;
};

int main(void)
{
   int sem_id, sem_value, i;
   int counter;
   key_t ipc_key;
   struct semid_ds sem_buf;
// static ushort sem_array[NS] = {3, 1, 4};
   static ushort sem_array[NS];
   union semun arg;
   ipc_key = ftok(".", 'S');

    if(argv[1] == 'r')
       ropt = atoi(argv[1])
    else if(argv[1] == 'n')
       ropt = atoi(argv[1])
    else
    {
      printf("Input error.\n");
      printf("Option is not valid.\n"); 
      exit(1);         
    }
    NS = atoi(argv[2]);    // Argument index 2 is number of semaphores
    for (counter = 0; counter < NS; ++counter)
    A = atoi(argv[2]);    // Argument index 2 is first integer
    B = atoi(argv[3]);    // Argument index 3 is second integer
    if (T > 50 || T <= 0) // If argument T is greater than 50, 0, or negative, throw exception
    { 
      printf("Input error.\n");
      printf("Maximum sleeptime m must be <= 50 and > 0.\n"); 
      exit(1); 
    }


/* Create semaphore */
   if ((sem_id = semget(ipc_key, NS, IPC_CREAT | 0666)) == -1)
   {
      perror ("semget: IPC | 0666");
      exit(1);
   }
   printf ("Semaphore identifier %d\n", sem_id);
/* Set arg (the union) to the address of the storage location for */
/* returned semid_ds value */
   arg.buf = &sem_buf;
   if (semctl(sem_id, 0, IPC_STAT, arg) == -1)
   {
      perror ("semctl: IPC_STAT");
      exit(2);
   }
   printf ("Create %s", ctime(&sem_buf.sem_ctime));
/* Set arg (the union) to the address of the initializing vector */
   arg.array = sem_array;
   
   if (semctl(sem_id, 0, SETALL, arg) == -1)
   {
      perror("semctl: SETALL");
      exit(3);
   }
   for (i=0; i<NS; ++i) 
   {
      if ((sem_value = semctl(sem_id, i, GETVAL, 0)) == -1)
      {
         perror("semctl : GETVAL");
         exit(4);
      }
      printf ("Semaphore %d has value of %d\n",i, sem_value);
   }
/* remove semaphore */
/*   if (semctl(sem_id, 0, IPC_RMID, 0) == -1) 
   {
      perror ("semctl: IPC_RMID");
      exit(5);
   }*/
}