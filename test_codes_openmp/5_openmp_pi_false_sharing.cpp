#include <stdio.h>
#include <omp.h>
#include <chrono>
#include<iostream>
using namespace std;

#define NUM_THREADS 1

static long num_steps = 1e8;

#define PAD 8 //L1 cache line is 64 byte, double is 8 byte

double step;
int main() {
 // Start the timer
 auto start = std::chrono::high_resolution_clock::now();
 int i,nthreads;
 double x, pi, sum[NUM_THREADS][PAD];
 step = 1.0/(double)num_steps;
 omp_set_num_threads(NUM_THREADS);
 #pragma omp parallel
 {
   int i, id, nthrds;
   double x;
   id = omp_get_thread_num();
   nthrds = omp_get_num_threads();
   if(id==0) nthreads = nthrds;
   for(i=id,sum[id][0]=0.0;i<num_steps; i=i+nthrds) {
     x = (i+0.5)*step;
     sum[id][0] += 4.0/(1.0+x*x);
   }
 }
 for(i=0, pi=0.0; i<nthreads;i++)pi += step*sum[i][0];

 // End the timer
 auto end = std::chrono::high_resolution_clock::now();

 // Calculate the duration
 std::chrono::duration<double> duration = end - start;
 // Print the duration in seconds
 std::cout << "Execution time: " << duration.count() << " seconds." << std::endl;

 cout<<"\nPi="<<pi<<endl;
}
