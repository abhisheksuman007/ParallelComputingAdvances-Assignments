//20ucs007
//Abhishek Suman

#include <cuda.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static const int Size = 2;

__global__ void add(const int *arr, int *out, const int size) {
    int indie = threadIdx.x;
    int sum = 0;
    for (int i = indie; i < size; i += Size)
        sum += arr[i];

    __shared__ int t[2];
    if(indie<2){
        t[indie]=sum;
    }
    if(indie==0)  {*out = t[0]; *(out+1) = t[1];}
}

void cudaAdd(int* b, int* a, int size) {
    int* ptr_a = NULL;
    int* ptr_b = NULL;

    cudaMalloc((void**)&ptr_b, size * sizeof(int));
    cudaMalloc((void**)&ptr_a, size * sizeof(int));

    cudaMemcpy(ptr_a, a, size * sizeof(int), cudaMemcpyHostToDevice);


      add<<<2, (size+1)/2>>>(ptr_a, ptr_b, size);

    cudaMemcpy(b, ptr_b, size * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(ptr_b);
    cudaFree(ptr_a);
}

int main(int argc, char** argv) {
    int count;
    printf("\n");
    printf("Input array size : ");
    scanf("%d", &count);
    if(count<1){
    	printf("Not a valid number. \n");
    	return 0;
    }
    int a[count];
    srand(time(NULL));
    for(int i=0;i<count;i++){
      a[i]=rand()%1000;
    }
    int b[count] = {0};

    cudaAdd(b, a, count);
    printf("\n Random generated array: \n");
      for(int i=0;i<count;i++){
      printf("%d ", a[i]);
    }
      printf("\n\nAddition of even indices: %d\n", b[0]);
      printf("Addition of odd indices : %d\n", b[1]);
      printf("\n");

    return 0;
}
