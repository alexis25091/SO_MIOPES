#include <stdio.h>
#include <pthread.h>
#include <unistd.h> 															// Para la funcion sleep

// Funcion que simula el proceso de carga de un vehiculo electrico

void *cargar_vehiculo(void *arg) {
    int vehiculo_id = *((int *) arg); 											// Obtiene el ID del vehiculo a partir del argumento pasado al hilo
    printf("Vehiculo %d: Iniciando carga...\n", vehiculo_id); 					// Notificaa que el vehiculo ha comenzado a cargar
    sleep(2);  																	// Simula el tiempo de carga del vehiculo (2 segundos)
    printf("Vehiculo %d: Carga completada.\n", vehiculo_id);  					// Notificaa que el vehiculo ha terminado de cargar
    pthread_exit(NULL);  														// Terminar el hilo correctamente
}

int main() {
    pthread_t hilos[2];  														// Array para almacenar los identificadores de los hilos (uno por cada vehiculo)
    int ids[] = {1, 2};  														// Array que contiene los IDs de los vehiculos que se van a cargar (vehiculo 1 y vehiculo 2)

    // Crear hilos ligeros para cada vehiculo
    
	for (int i = 0; i < 2; i++) {  												// Ciclo de dos veces, una por cada vehiculo
																				// Crear un hilo que ejecuta la funcion cargar_vehiculo, pasando el ID del vehiculo como argumento
        pthread_create(&hilos[i], NULL, cargar_vehiculo, (void *) &ids[i]);  
        																		// Primer argumento: referencia al hilo que se va a crear
        																		// Segundo argumento: NULL para usar los atributos por defecto
																		        // Tercer argumento: funcion que ejecutara el hilo (cargar_vehiculo)
        																		// Cuarto argumento: ID del vehiculo, convertido a un puntero generico
    }

    // Esperar a que ambos vehiculos terminen de cargar
    
    for (int i = 0; i < 2; i++) {  												// Ciclo de dos veces, una por cada hilo
        pthread_join(hilos[i], NULL);  											// Espera a que el hilo termine de ejecutarse
        																		// Primer argumento: el identificador del hilo
        																		// Segundo argumento: NULL, ya que no necesitamos el valor de retorno del hilo
    }

    // Notifica que ambos vehiculos han terminado de cargar
    
    printf("Programa principal: Todos los vehiculos han terminado de cargar.\n");

    return 0;  																	// Finalizar el programa correctamente
}
