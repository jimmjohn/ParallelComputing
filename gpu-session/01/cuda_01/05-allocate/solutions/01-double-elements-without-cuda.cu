#include <stdio.h>

// Define a custom data transfer function from host to device
void customCopyHostToDevice(int* dst, const int* src, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        dst[i] = src[i];
    }
}

// Define a custom data transfer function from device to host
void customCopyDeviceToHost(int* dst, const int* src, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        dst[i] = src[i];
    }
}

/*
 * Initialize array values on the host.
 */

void init(int *a, int N)
{
  int i;
  for (i = 0; i < N; ++i)
  {
    a[i] = i;
  }
}

/*
 * Double elements in parallel on the GPU.
 */

__global__
void doubleElements(int *a, int N)
{
  int i;
  i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i < N)
  {
    a[i] *= 2;
  }
}

/*
 * Check all elements have been doubled on the host.
 */

bool checkElementsAreDoubled(int *a, int N)
{
  int i;
  for (i = 0; i < N; ++i)
  {
    if (a[i] != i * 2) return false;
  }
  return true;
}

int main()
{
  int N = 100;
  int *a;
  int *d_a; // Device pointer

  size_t size = N * sizeof(int);

  /*
   * Allocate memory for `a` on the host.
   */

  a = (int *)malloc(size);

  init(a, N);

  size_t threads_per_block = 10;
  size_t number_of_blocks = 10;

  /*
   * Allocate memory for `d_a` on the device.
   * Note: No cudaMalloc used; memory is statically allocated.
   */

  d_a = (int *)malloc(size);

  /*
   * Custom data transfer from host to device.
   */

  customCopyHostToDevice(d_a, a, size);

  /*
   * This launch will work because the pointer `d_a` is available to the device.
   */

  doubleElements<<<number_of_blocks, threads_per_block>>>(d_a, N);
  cudaDeviceSynchronize();

  /*
   * Custom data transfer from device to host.
   */

  customCopyDeviceToHost(a, d_a, size);

  bool areDoubled = checkElementsAreDoubled(a, N);
  printf("All elements were doubled? %s\n", areDoubled ? "TRUE" : "FALSE");

  /*
   * Free allocated memory on both the host and the device.
   */

  free(a);
  free(d_a);
}
