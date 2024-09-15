#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>

void helloCPU()
{
  printf("Hello from the CPU.\n");
}

/*
 * The addition of `__global__` signifies that this function
 * should be launced on the GPU.
 */

__global__ void helloGPU()
{
  printf("Hello from the GPU.\n");
}

int main()
{
  helloCPU();


  /*
   * Add an execution configuration with the <<<...>>> syntax
   * will launch this function as a kernel on the GPU.
   */

  helloGPU<<<2, 1>>>();

  /*
   * `cudaDeviceSynchronize` will block the CPU stream until
   * all GPU kernels have completed.
   */

  cudaDeviceSynchronize();
}
