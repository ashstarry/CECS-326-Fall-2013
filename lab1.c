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

int* newRandomArray(int);

int main(int argc, char *argv[])
{
	int i,j, n, sum, max, min;
	max = -100; // First random number will be max if greater than -100 range
	min = 100;  // First random number will be min if less than 100 range
	sum = 0;    // Initialize sum to be zero
	int *randA;
	double average = 0.0;
	if (argc !=2) // If argument character is not two fields, print statement
	{
		printf("\n Usage: Need filename and one argument\n", argv[0]);
		exit(1);
	}
	n = atoi(argv[1]); // Index 2 (number N)
	srand(time(NULL)); // Seed, initialize random number generator
	randA = newRandomArray(n);
	for (i=0; i<n;i++) // Start at i = 0, iterate to # n random numbers
	{
        if(randA[n]>max)
        {
            max=randA[n]; // If number generate is > max, replace max
        }
        else if(randA[n]<min)
        {
            min=randA[n]; // If number generate is < max, replace min
        }
        else
        {
            max = max;
            min = min;
        }
        sum = randA[i] + sum;  // Place hold a sum of all random integers
	}
	printf ("\n");
	average = (sum/(double)n); // Calculate average by sum of random integers
	for (j=0; j < n; j++)
	{
	    printf("%d ", randA[j]);     // Display the array of random integers
    }
    printf("\nAverage of random integers is: %f", average, "\n");
    printf("\nMaximum of random integers is: %d", max, "\n");
    printf("\nMinimum of random integers is: %d", min, "\n");
    printf ("\n");
    free(randA);     // Free memory
	exit(0);
}

int* newRandomArray(int n)
{
     int* h = (int *) malloc(n*sizeof(int)); // malloc allocates memory for array
     int i;
     for (i=0; i<n; ++i)
         h[i] = rand()%201-100;
         return h;
}
