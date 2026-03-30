#include "globales.h"
#include "brazo.h"

void* brazo_clasificador(void* arg){
    int id_brazo = *(int*)arg;
    while(1){
        sem_wait(&s_brazos_disponibles); // espera a que un dron entregue el producto.

        // INICIA EL CRONÓMETRO PARA ESTE PRODUCTO.
        struct timeval inicio, fin;
        gettimeofday(&inicio, NULL);

        // clasifica el producto de manera random.
        // Generar un número del 1 al 100
        int probabilidad = (rand() % 100) + 1; 
        int tipo_producto;
        int id_deposito;

        if (probabilidad <= prob_ultra) {
            tipo_producto = 2; // Ultra-delicado
        } else if (probabilidad <= prob_ultra + prob_refri) {
            tipo_producto = 1; // Refrigerado
        } else {
            tipo_producto = 0; // Estándar
        }

        sem_wait(&mutex_logistica);// pide todos los drones que necesita de una sola vez.

        if(tipo_producto == 1){ // refrigerado.
            id_deposito = 4 + (rand() % 3); //depositos 4, 5 y 6.
            sem_wait(&mutex_metricas);
            bloqueos_evitados++; // Simulamos que la logica previno un choque.
            sem_post(&mutex_metricas);

            printf("%s Brazo %d: Solicitó 2 Drones de Carga y esta ESPERANDO... %s\n", COLOR_MAGENTA, id_brazo, COLOR_RESET);

            sem_wait(&s_drones_carga); // Toma el 1ro.
            sem_wait(&s_drones_carga); // Toma el 2do.
            sem_post(&mutex_logistica);  // Libera exclusion.
            
            printf("%s Brazo %d: Consiguio los 2 Drones! Despachando Refrigerado... %s\n", COLOR_CYAN, id_brazo, COLOR_RESET);
            sem_post(&s_solicitud_drone);
            sem_post(&s_solicitud_drone);
            
            // ESPERA QUE LOS DOS DRONES TERMINEN.
            sem_wait(&s_drone_listo);
            sem_wait(&s_drone_listo);
            
            // LIBERA LOS RECURSOS.
            sem_post(&s_drones_carga);
            sem_post(&s_drones_carga);

        }else if( tipo_producto == 2){ // ultradelicado.
            id_deposito = 7; // deposito 7.
            printf("%s Brazo %d: Solicitó la Plataforma Magnetica y esta ESPERANDO... %s\n", COLOR_ROJO, id_brazo, COLOR_RESET);
            sem_wait(&s_plataforma);   // Reserva plataforma.
            sem_wait(&s_drones_carga); // Reserva logica del drone.
            sem_post(&mutex_logistica);  // Libera exclusion.
            
            printf("%s Brazo %d: Consiguio la Plataforma! DESPACHANDO... %s\n", COLOR_VERDE, id_brazo, COLOR_RESET);
            sem_post(&s_solicitud_drone);
            
            // ESPERA QUE EL DRONE TERMINE.
            sem_wait(&s_drone_listo);
            
            // LIBERA RECURSOS.
            sem_post(&s_drones_carga);
            sem_post(&s_plataforma);

            printf("%s Brazo %d: Solto la Plataforma Magnetica! %s\n", COLOR_AMARILLO, id_brazo, COLOR_RESET);
            
        }else{ // estandar.
            id_deposito = rand() % 4; // depositos 0, 1, 2 y 3.
            sem_post(&mutex_logistica); // libera exclusion.
            printf("Brazo %d Moviendo Estandar directo a deposito.\n", id_brazo);
            usleep(500000);
        }
        
        
        // depositar
        sem_wait(&mutex_depositos[id_deposito]); // Exclusion mutua del deposito
        cajas_en_deposito[id_deposito]++;
        printf("Brazo %d Caja depositada en %d. Total alli: %d\n", id_brazo, id_deposito, cajas_en_deposito[id_deposito]);

        if (cajas_en_deposito[id_deposito] == 3) {
            printf("Brazo %d Deposito %d LLENO. Llamando operario...\n", id_brazo, id_deposito);
            deposito_a_vaciar = id_deposito;
            sem_post(&s_operario);         // Despierta al operario
            sem_wait(&s_deposito_vaciado); // Espera que el operario termine
        }

        sem_post(&mutex_depositos[id_deposito]);

        // DETIENE EL CRONÓMETRO.
        gettimeofday(&fin, NULL);

        // CALCULA EL TIEMPO EN MILISEGUNDOS.
        double tiempo_producto = (fin.tv_sec - inicio.tv_sec) * 1000.0; 
        tiempo_producto += (fin.tv_usec - inicio.tv_usec) / 1000.0;

        // GUARDA LOS RESULTADOS (Dentro de la sección crítica de métricas).
        sem_wait(&mutex_metricas);
        tiempo_total_procesamiento += tiempo_producto; 
        
        if(tipo_producto == 0) total_estandar++;
        else if(tipo_producto == 1) total_refrigerado++;
        else total_ultra++, uso_plataforma++;
        sem_post(&mutex_metricas);
    }
    return NULL;
 }