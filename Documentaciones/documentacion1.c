                                                                            /* Codigo 1. Importacion de Librerias */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>                                                         /* Para la funcion sleep */

                                                                            /* Funcion que simula la impresion de facturas en la primera impresora */
void *impresora1(void *arg)
{
    for (int i = 1; i <= 5; ++i)                                            /* Se crea un for para simular las 5 facturas que hara*/
    {
        printf("Impresora 1: Imprimiendo factura %d\n", i);                 /* Simulacion de la impresion de facturas */
        sleep(1);                                                           /* Simula el tiempo de impresion (1 segundo por factura) */
    }
    return NULL;                                                            /* Significa que termino el hilo sin generar nigun valor*/
}

                                                                            /* Funcion que simula la impresion de facturas en la segunda impresora */
void *impresora2(void *arg)
{
    for (int i = 1; i <= 5; ++i)                                            /* Se crea un for para simular las 5 facturas que hara*/
    {
        printf("Impresora 2: Imprimiendo factura %d\n", i);                 /* Simulacion de la impresion de facturas */
        sleep(1);                                                           /* Simula el tiempo de impresion (1 segundo por factura) */
    }
    return NULL;                                                            /* Significa que termino el hilo sin generar nigun valor*/
}

int main()
{
                                                                            /* Declaracion de identificadores de hilos */
    pthread_t hilo1, hilo2;

                                                                            /* Creacion de hilos para las impresoras */
    pthread_create(&hilo1, NULL, impresora1, NULL);                         /* El hilo 1 ejecuta la funcion impresora1 */
    pthread_create(&hilo2, NULL, impresora2, NULL);                         /* El hilo 2 ejecuta la funcion impresora2 */

                                                                            /* Espera a que los hilos terminen su ejecucion */
    pthread_join(hilo1, NULL);                                              /* Espera a que el hilo de la impresora1 termine */
    pthread_join(hilo2, NULL);                                              /* Espera a que el hilo de la impresora2 termine */

    printf("Programa principal: Todas las facturas han sido impresas\n");   /* Teminan los hilos y finaliza el programa */ 

    return 0;
}
