//20ucs007
//Abhishek Suman

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <time.h>
#include <stdio.h>

__global__ void MV_mul(int *a, int *b, int *c, int n) {
    int numRow=threadIdx.x+blockDim.x*blockIdx.x;
    int sum=0;
   
    if(numRow<n)
    for(int j=0;j<n;j++)
    {
        sum=sum+a[numRow*n+j]*b[j];
    }
    
    c[numRow]=sum;
}


void PrintMatrix (int* matrix, int CountRow, int countColumn) {
    int i, j; // Variables in loop
    for (i=0; i<CountRow; i++) {
      for (j=0; j<countColumn; j++){
        printf(" %d ,", matrix[i*CountRow+j]);
      }
    printf("\n");
    }
}

void PrintVector (int* vector, int Size) {
    int i;
    for (i=0; i<Size; i++){
      printf(" %d ,", vector[i]);
    }
}


void random_ints(int* a, int N) {
    for (int i=0; i < N; i++){
        a[i] = rand() % 10;
    }
}

int main(void) {
    int n;
    do {
      printf("\nEnter the first items: ");
      scanf("%d", &n);
      printf("\nSelected items size = %d\n", n);
      if (n <= 0){
        printf("\nSize of Items > 0!\n");
      }
    }
    while (n <= 0);
    
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;
    int size = n * sizeof(int);


    cudaMalloc((void **)&d_a, size * n);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_c, size);

    a = (int *)malloc(size*n); random_ints(a, n*n);
    b = (int *)malloc(size); random_ints(b, n);
    c = (int *)malloc(size);

    printf (" First Matrix \n");
    PrintMatrix(a, n, n);
    printf("\n");
    printf(" First Vector \n");
    PrintVector(b, n);
    printf("\n");

    cudaMemcpy(d_a, a, size * n, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
    dim3 threadsPerBlock(n, n);
    dim3 blocksPerGrid(1, 1);

    MV_mul<<<blocksPerGrid,threadsPerBlock>>>(d_a, d_b, d_c,n);


    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    printf ("\n Resultant Vector: \n");
    PrintVector(c, n);

    free(a); free(b); free(c);
    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
    return 0;
}