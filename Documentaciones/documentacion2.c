/*Codigo 2*/

#include <stdio.h>//Libreria de entrada y salida estandar
#include <stdlib.h>//Libreria para la gestion de memoria y conversion de datos
#include <pthread.h>//Libreria para manejar hilos 
#include <unistd.h> // Para usar la funcion sleep

// Estructura para pasar multiples argumentos a la funcion del hilo
typedef struct {
    int thread_id;//Identificador unico para el hilo
    char* order;//Apuntador a una cadena que representa un pedido
    int preparation_time;//Tiempo de preparacion del hilo
} ThreadArgs;

// Funcion que se ejecutara en el primer hilo (Cocinero 1)
void* prepareOrder1(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;//Realiza una conversion
    printf("Cocinero %d: Preparando %s...\n", thread_args->thread_id, thread_args->order);//Mensaje de inicio
    sleep(thread_args->preparation_time); // Simula el tiempo de preparación
    printf("Cocinero %d: %s listo!\n", thread_args->thread_id, thread_args->order);//Mensaje de fin
    pthread_exit(NULL); // Terminar el hilo
}

// Función que se ejecutará en el segundo hilo (Cocinero 2)
void* prepareOrder2(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;//Realiza una conversion
    printf("Cocinero %d: Preparando %s...\n", thread_args->thread_id, thread_args->order);//Mensaje inicio
    sleep(thread_args->preparation_time); // Simula el tiempo de preparación
    printf("Cocinero %d: %s listo!\n", thread_args->thread_id, thread_args->order);//Mensaje fin
    pthread_exit(NULL); // Terminar el hilo
}

int main() {
    // Definir la estructura de argumentos para cada cocinero
    ThreadArgs args1 = {1, "Hamburguesa con papas", 3};  // Pedido 1: Hamburguesa con papas (3 segundos)
    ThreadArgs args2 = {2, "Pizza grande", 5};           // Pedido 2: Pizza grande (5 segundos)

    // Declarar las variables de hilo
    pthread_t thread1, thread2;

    // Crear los hilos y pasar las funciones junto con los argumentos
    if (pthread_create(&thread1, NULL, prepareOrder1, (void*)&args1) != 0) {//Crea el primer hilo y llama a la funcion prepareOrder1
        perror("Error al crear el hilo para el primer cocinero"); // Imprimir error si falla la creación del hilo
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread2, NULL, prepareOrder2, (void*)&args2) != 0) {//Crea el segundo hilo y llama a la funcion prepareOrder2
        perror("Error al crear el hilo para el segundo cocinero"); // Imprimir error si falla la creación del hilo
        exit(EXIT_FAILURE);
    }

    // Esperar a que los hilos terminen su ejecución
    if (pthread_join(thread1, NULL) != 0) {//Espera a que termine su ejecucion
        perror("Error al unir el hilo del primer cocinero"); // Imprimir error si falla la espera del hilo
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread2, NULL) != 0) {//Espera a que termine su ejecucion
        perror("Error al unir el hilo del segundo cocinero"); // Imprimir error si falla la espera del hilo
        exit(EXIT_FAILURE);
    }

    // Imprimir mensaje del hilo principal
    printf("Hilo principal: Ambos pedidos están listos.\n");

    return 0;
}
