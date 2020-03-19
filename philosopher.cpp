#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define N 5
sem_t chopsticks[N];
sem_t r;
int philosophers[N] = {0, 1, 2, 3, 4};
int islocked[N] = {0};
pthread_mutex_t chops[N];
void delay (int len) {
    int i = rand() % len;
    int x;
    while (i > 0) {
        x = rand() % len;
        while (x > 0) {
            x--;
        }
        i--;
    }
}
void xchg(int *x, int *y) {
    __asm__("xchgl %0, %1" : "=r" (*x) : "m" (*y));
}
void* philosopher(void* arg) {
    int i = *(int *)arg;
    int left = i;
    int right = (i + 1) % N;
    while (1) {
        printf("Philosopher%d is thinking.\n", i);
        delay(50000);
        if (i % 2 == 0) {
            sem_wait(&chopsticks[right]);
            sem_wait(&chopsticks[left]);
            delay(50000);
            sem_post(&chopsticks[left]);
            sem_post(&chopsticks[right]);
        } else {
            sem_wait(&chopsticks[left]);
            sem_wait(&chopsticks[right]);
            delay(50000);
            sem_post(&chopsticks[right]);
            sem_post(&chopsticks[left]);
        }
    }
}
int main (int argc, char **argv) {
    srand(time(NULL));
    pthread_t PHD[N];
    for (int i=0; i<N; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }
    sem_init(&r, 0, 4);
    for (int i=0; i<N; i++) {
        pthread_mutex_init(&chops[i], NULL);
    }
    for (int i=0; i<N; i++) {
        pthread_create(&PHD[i], NULL, &philosopher, &philosophers[i]);
    }
    for (int i=0; i<N; i++) {
        pthread_join(PHD[i], NULL);
    }
    for (int i=0; i<N; i++) {
        sem_destroy(&chopsticks[i]);
    }
    sem_destroy(&r);
    for (int i=0; i<N; i++) {
        pthread_mutex_destroy(&chops[i]);
    }
    return 0;
}

