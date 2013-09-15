/****************************************************************/
/*	PROGRAM NAME: lab1.c
/*	CLASS: CECS-326
/*	INSTRUCTOR: Mr. Haney Williams
/*	STUDENT: Steven Le
/*	DESCRIPTION: This C program named lab1 stores N random
/*	numbers in an array named randA[] and determines the largest,
/*	smallest, and average values of this array. The array displays
/*	elements that store these values. The random numbers range
/*	from -100 to +100. N is a command line argument. The
/*	debugger is utilized to go transverse program.
/****************************************************************/
# include <stdio.h>
# include <stdlib.h>

int* newRandomArray(int);	// Function prototype

int main(int argc, char *argv[])
{
	int i,j, n, sum, max, min;
	sum = 0;    // Initialize sum to be zero
	int *randA;
	double average = 0.0;	// Initialize average to double zero
	if (argc !=2) // If argument character is not two fields, print statement
	{
		printf("\n Usage: Need filename and one argument\n", argv[0]);
		exit(1);
	}
	n = atoi(argv[1]); // n receives index 2
	srand(time(NULL)); // Seed, initialize random number generator
	randA = newRandomArray(n);	// function newRandomArray with n assign to randA
	max = randA[0]; // First random number will be max at array index 0
	min = randA[0];  // First random number will be min at array index 0
	for (i = 0; i < n; i++) // Start at i = 0, iterate to # n random numbers
	{
        if(randA[i] > max)
        {
            max=randA[i]; // If number generate is > max, replace max with value
        }
        else if(randA[i] < min)
        {
            min=randA[i]; // If number generate is < max, replace min with value
        }
        else
        {
            max = max;	// If number generated is equal to max or min, keep value
            min = min;
        }
        sum = randA[i] + sum;  // Temp variable to hold sum of all random integers in array
	}	// End for-loop
	printf ("\n");
	average = (sum/(double)n); // Calculate average = sum of random integers / n
	for (j = 0; j < n; j++)
	{
	    printf("%d ", randA[j]);     // Display the array of random integers
    }
    printf("\nMaximum of random integers is: %d", max, "\n");		// Display max
    printf("\nMinimum of random integers is: %d", min, "\n");		// Display min
    printf("\nAverage of random integers is: %f", average, "\n");	// Display average
    printf("\n");
    free(randA);     // Deallocate memory block
	exit(0);
}

int* newRandomArray(int n)
{
     int* h = (int *) malloc(n*sizeof(int)); // malloc allocates memory for array
     int i;
     for (i = 0; i < n; ++i)
         h[i] = rand() % 201-100;            // Sets range for -100 to 100
         return h;							 // Returns a pointer
}
