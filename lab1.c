/****************************************************************/
/*	PROGRAM NAME: lab1.c */
/*	DESCRIPTION: Write a C program named lab1 to store N random
/*	numbers in an array named randA[ ] and determine the largest,
/*	smallest, and average values of this array. Display the array
/*	elements that store these values. The random numbers range
/*	from -100 to +100. N is a command line argument. Use the
/*	debugger to go through the program. Use all the debugger
/*	commands.
/****************************************************************/
# include <stdio.h>
# include <stdlib.h>
int main(int argc, char *argv[])
{
int i,j,n;
if (argc !=2) {
printf("\n Usage: Need filename and one argument\n", argv[0]);
exit(1);
}
n = atoi(argv[1]);
srand(n);
for (i=0; i<10;++i){
j = rand()%100;
printf ("\n %d",j);
}
printf ("\n");
exit(0);
}
