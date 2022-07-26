#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>


void oneProcess(int numbers[], int L, int H)
{
    int counter = 0;
    for(int i = 0; i < L; i++)
    {
        if(numbers[i]== -1)
	{
            printf("Hi I am process %d and I found a hidden key in position A[%d]\n",getpid(),i);
            counter++;
        }
        if(counter == H)
            break;
        
    }
}

int blockSearch(int numbers[], int start, int end, int L , int H, int* keys)
{
       	int found = 0;

	size_t i;

	for (i = start; i < L && i < end; i++)
	{
		// Key check.
		if (numbers[i] == -1)
		{
			keys[found++] = i;
			printf("Hi I'm process %d and I found the hidden key in position A[%d].\n", getpid(), keys[found - 1]);
		}
		// All found check.
		if (found == H)
		{
			break;
		}
	}
	// Return number of keys found.
	return found;
}

void multProcess(int numbers[],int L, int H)
{
    
    int numFound,searchResult,j = 0;
    int split = L/H;
    
    int *indexes = (int*)malloc(H*sizeof(int));
    int *keyIndexes = (int*)malloc(H*sizeof(int));
    pid_t p,root,start,end;
    int pipefd[2];
    if((pipe(pipefd)) == -1)
    {
        printf("Pipe creation failure");
        exit(EXIT_FAILURE);
    }

    root = getpid();

    for(int i =0; i < H;i++)
    {
        start = split*i;
        end = (i+1) * split;
        if((p = fork()) < 0)
	{
            printf("Fork failed\n");
            exit(1);
	}
        //child
        else if(p == 0)
	{
            printf("Hi I'm process %d and my parent is %d.\n", getpid(), getppid());
            if(i == H)
	    { 
		 // Next send number of found indexes 
		write(pipefd[1], &numFound, sizeof(int));
		// Now, pipe each found index (should be none).
		for (j = 0; j < numFound; j++)
		{
			write(pipefd[1], &(keyIndexes[j]), sizeof(int));
		}
            }
        }
        //parent
        else if(p > 0)
	{
	
		searchResult = blockSearch(numbers,start,end,L,H,keyIndexes);

		for (j = 0; j < searchResult; j++)
		{
			indexes[j] = keyIndexes[j];
			numFound++;
		}


		waitpid(p, NULL, 0);
		int readFound, readIndex;

	
		read(pipefd[0], &readFound, sizeof(int));

		for (j = 0; j < readFound; j++)
		{
			read(pipefd[0], &readIndex, sizeof(int));
			indexes[numFound++] = readIndex;

		}
	
		if (!(getpid() == root))
		{
			write(pipefd[1], &numFound, sizeof(int));
			// Now, pipe each found index.
			for (j = 0; j < numFound; j++)
			{
				write(pipefd[1], &(indexes[j]), sizeof(int));		
			}
		}
                break;

        }
    }
    free(indexes);
    free(keyIndexes);
    exit(EXIT_SUCCESS);
}

int countLines(char *filename)
{
	FILE *fp = fopen(filename, "r");
	int ch = 0;
	int lines = 0;
	
	if (fp == NULL)
	{
		printf("Could not open file %s", filename);
		return 0;
	}
	
	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')
			lines++;
	}

	fclose(fp);
	return lines; 	
}
int main(int argc, char **argv)
{
    //argv[1] = filename
    //argv[2] = version
    //argv[3] = H
    if(argc != 4)
    {
	printf("not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    int L = countLines(argv[1]);
    int H = atoi(argv[3]);
    int version = atoi(argv[2]);
    //put numbers from txt file into an array
    int numbers[L];
    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0, num, max = -1, total=0;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) 
    {
        
        num = atoi(line);
        numbers[i]= num;
        total +=num;
        if (num > max)
		max = num;
        i++;
    }
    double avg = (total * 1.0)/L;
    printf("L = %d, H = %d, Max = %d, Average = %f\n", L, H, max, avg);
    fclose(fp);

    if(version == 1)
        oneProcess(numbers,L,H);
    if(version == 2)
        multProcess(numbers,L,H);
    return 0;

}
