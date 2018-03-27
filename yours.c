#include <stdlib.h>
#include <sys/time.h>
#include<time.h>
#include <printf.h>
#include "handout.h"

//these are the implemented methods in 'handout.o' :

//double *generate(int n)
//bool check(double *Yours, double *A, double *B, int n)
//void printMatrix(double *M, int n)
//double *Mult(double *A, double *B, int n)

//the timer should be implemented in the YoursBlocked & YoursRecursive function and printed out in a format like "TIME: 0.000000 seconds"


double *YoursBlocked(double *b, double *c, int n, int blockSize) {
    double *a;
     a = (double *) malloc(n * n * sizeof(double));
// fill your code here, a is your output matrix
	
	
	int i, j, k, iInner, jInner, kInner ;
   	for (i = 0; i < n; i+=blockSize)
      		for (k = 0 ; k < n; k+=blockSize)
         		for (j=0; j<n ; j+= blockSize)
            			for (iInner = i; iInner<i+blockSize; iInner++)
               				for (kInner = k ; kInner<k+blockSize ; kInner++)
                  				for (jInner = j ; jInner<j+blockSize; jInner++)
                        a[iInner*n+jInner] += b[iInner*n+kInner] * c[kInner*n+jInner];

    return a;
}

double *YoursRecursive(double *b, double *c, int n) {
    double *a;
    a = (double *) malloc(n * n * sizeof(double));
	int i,j,k;
	if(n>=2){
		for(i=0;i<n;i++) 
			for (j=0;j<n;j++)
				for(k=0;k<n;k++)
					a[i*n+j] += b[i*n+k] * c[k*n+j];
		YoursRecursive(a,b,n/2);
		
	}
	else if(n==1){
	*(a);	
	}
	else
	return a;
}	

int main(int argc, char *argv[]) {
	clock_t startB,endB,startR,endR;
    srand((unsigned int) time(NULL));
    int n = 32;//atoi(argv[1]);
    int blockSize = n;	//atoi(argv[1]);
    double *A, *B;
	
    A = generate(n);
    B = generate(n);
    printf("A\n");
    printMatrix(A, n);

    printf("B\n");
    printMatrix(B, n);
   
    startB = clock();
    double *Y;
    Y = (double *) malloc(n * n * sizeof(double));
    Y = generate(n);
    Y = YoursBlocked(A, B, n,blockSize);
    Y = Mult(A, B, n);
    printf("Y\n");
    printMatrix(Y, n);
    endB = clock();
    if (check(Y, A, B, n))
        printf("B TRUE%d\n", 1);
    else
        printf("B FALSE%d\n", 0);
    
    startR = clock();
    double *R;
    R = (double *) malloc(n * n * sizeof(double));
    R = generate(n);
    R = YoursRecursive(A,B,n);
    R = Mult(A, B, n);
    printf("R\n");
    printMatrix(R, n);
    endR = clock();
    if (check(R, A, B, n))
        printf("R TRUE%d\n", 1);
    else
        printf("R FALSE%d\n", 0);
	printf("Btime : %.3lfms\nRtime : %.3lfms\n",(double)endB-startB,(double)endR-startR);
    free(A);
    free(B);
    free(Y);
    free(R);
}
