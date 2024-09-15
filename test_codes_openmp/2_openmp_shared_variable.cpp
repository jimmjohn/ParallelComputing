#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){
    int thread_id=100;

    #pragma omp parallel private(thread_id)
    {
        thread_id++;
        printf("Hello from process: %d\n", thread_id );
    }

    return 0;
}
