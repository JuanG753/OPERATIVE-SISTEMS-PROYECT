#include "globales.h"
#include "drones.h"

void* drone_carga(void* arg) {
    int id_drone = *(int*)arg;
    
    while(1) {
        // 1. Duerme esperando que un Brazo Clasificador lo solicite
        sem_wait(&s_solicitud_drone); 
        
        printf("Drone Carga %d Activado. Transportando producto delicado...\n", id_drone);
        sleep(1); // Simula el tiempo de vuelo hacia el deposito
        
        // 2. Avisa al brazo que el transporte finalizo
        sem_post(&s_drone_listo); 
    }
    return NULL;
}

void* drone_recolector(void* arg) {
    int id = *(int*)arg;
    
    // 1. Entrar al centro (Maximo 25 a la vez)
    sem_wait(&s_capacidad); 
    printf("Drone %d Entrando al centro.\n", id);
    
    // 2. Pasar por el Agente de Desinfeccion
    sem_post(&s_drone_esperando_agente);
    sem_wait(&s_agente_listo); // Espera ser validado
    
    // 3. Entregar carga al Brazo Clasificador
    // Despierta a un brazo libre para que haga su trabajo
    sem_post(&s_brazos_disponibles); 
    
    // 4. Salir del centro
    printf("Drone %d Carga entregada. Saliendo del centro.\n", id);
    sem_post(&s_capacidad); // Libera el cupo para otro drone
    
    free(arg); // Limpiar memoria del argumento
    return NULL;
}