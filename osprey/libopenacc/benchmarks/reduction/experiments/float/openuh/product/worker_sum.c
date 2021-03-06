#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <openacc.h>
#include <sys/time.h>

#define REAL float

int main()
{
	int i, j, k;
	int NI, NJ, NK;
    int error;
    REAL *finput, *ftemp;
    REAL frounding_error = 1.E-9;
    int *logics;
    struct timeval tim;
    double start, end;
	
    NK = 2;
	NJ = 1<<20;
	NI = 32;

    error = 0;
    finput = (REAL*)malloc(NK*NJ*NI*sizeof(REAL));
	ftemp = (REAL*)malloc(NK*NJ*NI*sizeof(REAL));
    
    acc_init(acc_device_default);

    srand((unsigned)time(0));
	for(k=0; k<NK; k++)
	{
		for(j=0; j<NJ; j++)
		{
			for(i=0; i<NI; i++)
            {
				finput[k*NJ*NI + j*NI + i] = (REAL)rand()/(REAL)RAND_MAX + 0.1;
            }
		}
	}
    
    /* Testing REAL * */
    gettimeofday(&tim, NULL);
    start = tim.tv_sec*1000 + (tim.tv_usec/1000.0);
  #pragma acc parallel copyin(finput[0:NK*NJ*NI]) \
  					   copyout(ftemp[0:NK*NJ*NI])
  {
    #pragma acc loop gang
    for(k=0; k<NK; k++)
	{
        REAL fproduct = 1;
		#pragma acc loop worker reduction(*:fproduct)
		for(j=0; j<NJ; j++)
		{
			#pragma acc loop vector
			for(i=0; i<NI; i++)
				ftemp[k*NJ*NI + j*NI + i] = finput[k*NJ*NI + j*NI + i];
            
		    fproduct *= ftemp[k*NJ*NI + j*NI];
		}
        ftemp[k*NJ*NI] = fproduct;
	}
  }
    gettimeofday(&tim, NULL);
    end = tim.tv_sec*1000 + (tim.tv_usec/1000.0);
	
    for(k=0; k<NK; k++)
    {
		REAL fproduct = 1;
		for(j=0; j<NJ; j++)
		{
			fproduct *= finput[k*NJ*NI + j*NI];
		}
		if(fabsf(ftemp[k*NJ*NI] - fproduct) > frounding_error)
        {
			error++;
		    printf("worker * FAILED\n");
        }
    }
    printf("worker * execution time is :%.2lf: ms\n", end-start);

    if(error == 0)
        printf("worker * SUCCESS!\n");

    free(finput);
    free(ftemp);

    return 1;
}
