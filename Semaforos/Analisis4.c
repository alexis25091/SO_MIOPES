#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SHMKEY 75
#define TRUE 1
int region_critica(int pid);
int region_no_critica(int pid); 
int esperando_turno(int pid);

int main() {
    int shmid, pid;
    char *addr, *turno;
    pid = getpid();
    shmid = shmget(SHMKEY, 10, 0777 | IPC_CREAT);
    addr = shmat(shmid, 0, 0);
    turno = (char *) addr;
    
    printf("\n [l] Variables Declaradas");
    sleep (5);
    (*turno) = '0';
    
    printf("\n [l] Iniciando proceso de turnos con turno inicial: %c", (*turno));

    while (TRUE) {
        while((*turno) != '0') {
            esperando_turno(pid);
        }
        region_critica(pid);
        sleep(1);
        (*turno) = '1';
        region_no_critica(pid);
    }
    
    shmdt(addr);
    
    shmctl(shmid, IPC_RMID, 0);
    return 0;
}
    

int esperando_turno(int pid) {
    printf("\n[l]Proceso %d y esperando turno :p", pid);
    sleep(2);
    return 0;
}


int region_critica(int pid) {
    printf("\n\n [O] Cambiando Variables");
    for (int i = 0; i < 5; i++) {
        printf("\n [O] Turno %d", i + 1);
        sleep(1);
    }
    return 0;
}


int region_no_critica(int pid){
    printf("\n [0] Proceso %d yturno tomado:)\n",pid);
    return 0;
}


