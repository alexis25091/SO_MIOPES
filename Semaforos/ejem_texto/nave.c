#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CINTA_CAPACIDAD 20  // Capacidad de la cinta transportadora

//Esta es la estructura para que represente la cinta transportadora
int cinta[CINTA_CAPACIDAD];
int frente = 0, fin = 0, cantidad = 0;
int pieza = 10; // Produce una pieza aleatoria 

sem_t espacio_disponible; // Semaforo que sirve para controlar el espacio disponible en la cinta
sem_t piezas_disponibles; // Semaforo que controla el numero de piezas disponibles de la cinta
sem_t mutex_cinta;        // Semaforo para controlar el acceso exclusivo hacia la cinta

// Funcion de la maquina de inyeccion
void* maquina_inyectar(void* arg) {
    while (pieza>=0) {
        

        // espera a que haya un espacio disponible
        sem_wait(&espacio_disponible);

        // acceso solo para la cinta
        sem_wait(&mutex_cinta);
        cinta[fin] = pieza;
        fin = (fin + 1) % CINTA_CAPACIDAD;
        cantidad++;
        printf("\nMaquina: \nInyecta pieza %d. \nPiezas en cinta: %d\n", pieza, cantidad);
        pieza--;
        sem_post(&mutex_cinta);

        // Se�ala si hay una pieza disponible
        sem_post(&piezas_disponibles);

        sleep(1);
        
    }
}

// Funcion del robot que recoge las piezas
void* robot_recoger(void* arg) {
    while (1) {
        
		// Espera a que haya piezas disponibles
        sem_wait(&piezas_disponibles);

        // otro acceso disponible para la cinta
        sem_wait(&mutex_cinta);
        int pieza = cinta[frente];
        frente = (frente + 1) % CINTA_CAPACIDAD;
        cantidad--;
        printf("\nRobot: Recoge pieza %d. \nPiezas en cinta: %d\n", pieza, cantidad);
        sem_post(&mutex_cinta);
	if(pieza==3)
		break;
        // Se�ala si hay espacios disponibles
        sem_post(&espacio_disponible);

        sleep(1);
    }
}

// Funcion del operario de control de calidad
void* operario_control_calidad(void* arg) {
    while (1) {
        // Necesita al menos 3 piezas para hacer el control de calidad
        sem_wait(&piezas_disponibles);
        sem_wait(&piezas_disponibles);
        sem_wait(&piezas_disponibles);

        // Acceso exclusivo a la cinta
        sem_wait(&mutex_cinta);
        if (cantidad >= 3) {
            printf("\nOperario: Realiza control de calidad de 3 piezas. \nPiezas restantes en cinta: %d\n", cantidad - 3);
            frente = (frente + 3) % CINTA_CAPACIDAD;
            cantidad -= 3;
        }
        sem_post(&mutex_cinta);

        // Se�alar que hay espacio disponible para 3 piezas
        sem_post(&espacio_disponible);
        sem_post(&espacio_disponible);
        sem_post(&espacio_disponible);

        sleep(2);  // Simular tiempo de control de calidad
    }
}

int main() {
    // Inicializar semaforos
    sem_init(&espacio_disponible, 0, CINTA_CAPACIDAD);
    sem_init(&piezas_disponibles, 0, 0);
    sem_init(&mutex_cinta, 0, 1);

    pthread_t hilo_maquina, hilo_robot, hilo_operario;

    // Crear hilos
    pthread_create(&hilo_maquina, NULL, maquina_inyectar, NULL);
    pthread_create(&hilo_robot, NULL, robot_recoger, NULL);
    pthread_create(&hilo_operario, NULL, operario_control_calidad, NULL);
    
    // Esperar a que los hilos terminen (aunque en este caso corren indefinidamente)
    pthread_join(hilo_maquina, NULL);
    pthread_join(hilo_robot, NULL);
    pthread_join(hilo_operario, NULL);
    printf("aun no destruye");

    // Destruir semaforos
    sem_destroy(&espacio_disponible);
    sem_destroy(&piezas_disponibles);
    sem_destroy(&mutex_cinta);
    
    printf("LLego hasta fin");

    return 0;
}

