#include <stdio.h>
#include <omp.h>
#include<iostream>
#include <chrono>

using namespace std;

static long num_steps = 1e8;
double step;
int main() {

 // Start the timer
 auto start = std::chrono::high_resolution_clock::now();

 double x, pi, sum=0.0;
 step = 1.0/(double)num_steps;
 for(int i=0; i<num_steps; i++) {
  x = (i+0.5)*step;
  sum += 4.0/(1.0+x*x);
 }
 pi = step*sum;

 // End the timer
 auto end = std::chrono::high_resolution_clock::now();

 // Calculate the duration
 std::chrono::duration<double> duration = end - start;
 // Print the duration in seconds
 std::cout << "Execution time: " << duration.count() << " seconds." << std::endl;

 cout<<"Pi="<<pi<<endl;
}
