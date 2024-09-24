/*Codigo 3*/


#include <stdio.h>//Libreria estandar de entrada y salida
#include <pthread.h>//Libreria para manejar hilos
#include <unistd.h> // Para usar la funcion sleep

// Funcion que simula el escaneo de articulos por cada cajero
void *escaneo_cajero(void *arg) {
    int cajero_id = *((int *)arg);  // Obtener el ID del cajero
    printf("Cajero %d: Escaneando articulos...\n", cajero_id);//Muestra el id donde se esta usando el cajero(hilos)
    sleep(1);  // Simula el tiempo de escaneo de los articulos
    printf("Cajero %d: Ha terminado de escanear los articulos.\n", cajero_id);//Mensaje al terminar la secuencia
    pthread_exit(NULL);  // Terminar el hilo
}

int main() {
    pthread_t cajeros[4];  // Array para almacenar los identificadores de los hilos (cajeros)
    int ids[] = {1, 2, 3, 4};  // IDs de los cajeros

    // Crear hilos para cada cajero
    for (int i = 0; i < 4; i++) {
        pthread_create(&cajeros[i], NULL, escaneo_cajero, (void *) &ids[i]);  // Crear hilo que representa a cada cajero
    }

    // Esperar a que cada cajero termine de escanear
    for (int i = 0; i < 4; i++) {
        pthread_join(cajeros[i], NULL);  // Esperar a que el cajero termine su tarea
    }

    printf("Programa principal: Todos los cajeros han terminado de escanear.\n");//Mensaje de finalizacion del programa

    return 0;
}
