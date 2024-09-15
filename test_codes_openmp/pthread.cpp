#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

volatile long int a = 0;
pthread_mutex_t mutex;

void* threadFunc(void *arg) {
    int i;
    long int localA = 0;
    for(i=1; i<500000; i++) {
        pthread_mutex_lock(&mutex);
        a = a + i;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* threadFunc2(void *arg) {
    int i;
    long int localA = 0;
    for(i=500000; i<1000000; i++) {
        pthread_mutex_lock(&mutex);
        a = a + i;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main(int argc, char **argv) {
    pthread_t one, two;
    int i;
    a = 0;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&one, NULL, threadFunc, NULL); // Remove the cast
    pthread_create(&two, NULL, threadFunc2, NULL); // Remove the cast

    pthread_join(one, NULL);
    pthread_join(two, NULL);

    pthread_mutex_destroy(&mutex);

    printf("%ld\n",a);
    return 0;
}
