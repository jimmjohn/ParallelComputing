#include <stdio.h>

__global__ void firstParallel()
{
  printf("This is running in parallel.\n");
}

int main()
{
  firstParallel<<<4, 4>>>();
  cudaDeviceSynchronize();
}
