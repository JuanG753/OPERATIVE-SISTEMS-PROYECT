#include "globales.h"
#include "agentes.h"
#include "brazo.h"
#include "drones.h"

int main(int argc, char *argv[]){
    srand(time(NULL));
    printf("=== INICIANDO SIMULACION AGRO-BOTS 2026 ===\n\n");

    // --- LECTOR DE BANDERAS ---
    if (argc > 1) { // Si el usuario escribió algo después de ./ejercicio
        if (strcmp(argv[1], "-ultradelicados") == 0) {
            printf("\n>>> MODO CASO BORDE: Forzando 90%% de productos Ultra-delicados <<<\n\n");
            prob_ultra = 90;
            prob_refri = 5;
        } 
        else if (strcmp(argv[1], "-refrigerados") == 0) {
            printf("\n>>> MODO CASO BORDE: Forzando 90%% de productos Refrigerados <<<\n\n");
            prob_ultra = 5;
            prob_refri = 90;
        }
    }

    // Inicializacion de semaforos
    sem_init(&s_capacidad, 0, MAX_CAPACIDAD_CENTRO);
    sem_init(&mutex_metricas, 0, 1);
    sem_init(&s_drone_esperando_agente, 0, 0);
    sem_init(&s_agente_listo, 0, 0);
    sem_init(&s_brazos_disponibles, 0, 0);           
    sem_init(&s_drones_carga, 0, NUM_DRONES_CARGA);
    sem_init(&s_plataforma, 0, 1);
    sem_init(&mutex_logistica, 0, 1);
    sem_init(&s_solicitud_drone, 0, 0);
    sem_init(&s_drone_listo, 0, 0);
    sem_init(&s_operario, 0, 0);
    sem_init(&s_deposito_vaciado, 0, 0);
    
    for(int i = 0; i < NUM_DEPOSITOS; i++) {
        sem_init(&mutex_depositos[i], 0, 1);
    }

    // Creacion de hilos servidores
    pthread_t t_agente, t_operario;
    pthread_t t_brazos[NUM_BRAZOS];
    pthread_t t_drones_carga[NUM_DRONES_CARGA];
    
    pthread_create(&t_agente, NULL, agente_de_desinfeccion, NULL);
    pthread_create(&t_operario, NULL, operario_de_almacen, NULL);
    
    int id_brazos[NUM_BRAZOS];
    for(int i = 0; i < NUM_BRAZOS; i++) {
        id_brazos[i] = i + 1;
        pthread_create(&t_brazos[i], NULL, brazo_clasificador, &id_brazos[i]);
    }

    int id_drones_carga[NUM_DRONES_CARGA];
    for(int i = 0; i < NUM_DRONES_CARGA; i++) {
        id_drones_carga[i] = i + 1;
        pthread_create(&t_drones_carga[i], NULL, drone_carga, &id_drones_carga[i]);
    }

    // Simulacion de llegada de drones
    pthread_t t_drones_recolectores[NUM_DRONES_RECOLECTORES];
    
    for(int i = 0; i < NUM_DRONES_RECOLECTORES; i++) {
        int* id_drone = malloc(sizeof(int));
        *id_drone = i + 1;
        pthread_create(&t_drones_recolectores[i], NULL, drone_recolector, id_drone);
        usleep(500000);
    }

    // Esperar finalizacion
    for(int i = 0; i < NUM_DRONES_RECOLECTORES; i++) {
        pthread_join(t_drones_recolectores[i], NULL);
    }

    sleep(3); 

    // Imprimir resultados
    printf("\n=======================================================\n");
    printf("         RESULTADOS DE LA COSECHA (METRICAS)\n");
    printf("=======================================================\n");
    printf("Productos Estandar procesados:        %d\n", total_estandar);
    printf("Productos Refrigerados procesados:    %d\n", total_refrigerado);
    printf("Productos Ultra-delicados procesados: %d\n", total_ultra);
    printf("Uso de plataforma magnetica:          %d veces\n", uso_plataforma);
    printf("Bloqueos prevenidos:                  %d veces\n", bloqueos_evitados);
    printf("=======================================================\n");
    
    // IMPRESIÓN DEL TIEMPO PROMEDIO 
    printf("Tiempo prom. de recolección/depósito: %.2f ms por producto\n", 
            tiempo_total_procesamiento / NUM_DRONES_RECOLECTORES);
            
    printf("=======================================================\n");

    return 0;
}
