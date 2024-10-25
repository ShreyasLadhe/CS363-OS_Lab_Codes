#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define BUFF_SIZE 5

int buffer[BUFF_SIZE];
int in = 0;
int out = 0;
int count = 0;

typedef struct {
    int value;
} semaphore;

void sem_init(semaphore *sem, int value) {
    sem->value = value;
}

void sem_wait(semaphore *sem) {
    while (sem->value <= 0);
    sem->value--;
}

void sem_sig(semaphore *sem) {
    sem->value++;
}

semaphore mutex;
semaphore empty;
semaphore full;

void *producer() {
    int item;
    while (true) {
        item = rand() % 100;
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Producer produced item: %d\n", item);
        in = (in + 1) % BUFF_SIZE;
        count++;

        sem_sig(&mutex);
        sem_sig(&full);

        sleep(1);
    }
}

void *consumer() {
    int item;
    while (true) {
        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[out];
        printf("Consumer consumed item: %d\n", item);
        out = (out + 1) % BUFF_SIZE;
        count--;

        sem_sig(&mutex);
        sem_sig(&empty);

        sleep(2);
    }
}

void thread_create(void (*function)()) {
    if (fork() == 0) {
        function();
        exit(0);
    }
}

int main() {
    sem_init(&mutex, 1);
    sem_init(&empty, BUFF_SIZE);
    sem_init(&full, 0);

    thread_create(producer);
    thread_create(consumer);
    while (true) {
        sleep(1);
    }

    return 0;
}
