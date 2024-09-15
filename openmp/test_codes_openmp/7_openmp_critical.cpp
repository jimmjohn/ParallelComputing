//critical -> Run code segment one by one by all threads

#include <iostream>
#include <stdio.h>
#include <omp.h>

int main() {
  // shared variable
    int sum_shared = 0;
    #pragma omp parallel
    {
        // private variable
        int sum_local = 0;
        //#pragma omp for nowait
        for (int i = 0; i < 10; ++i) {
            sum_local += i;
        }
        // critical section as we update
        // shared variable/ data
        //std::cout<<"Thread ID   = "<<omp_get_thread_num()<<std::endl;
        printf("Thread ID =  %d\n", omp_get_thread_num());
        #pragma omp critical
        {
            sum_shared += sum_local;
        }
    }
    std::cout << sum_shared << std::endl;
  return 0;
}
