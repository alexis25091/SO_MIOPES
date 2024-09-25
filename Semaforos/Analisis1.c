#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex;

void* thread_func(void* arg) {
    sem_wait(&mutex);
    printf("Sección crítica del hilo\n");
    sem_post(&mutex);
    return NULL;
}

int main() {
    pthread_t thread;
    
    sem_init(&mutex, 0, 1);

    pthread_create(&thread, NULL, thread_func, NULL);
    
    sem_wait(&mutex);
    printf("Sección crítica del hilo principal\n");
    sem_post (&mutex);

    pthread_join (thread, NULL);
    sem_destroy(&mutex);
    return 0;
}
