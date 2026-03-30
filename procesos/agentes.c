#include "globales.h"
#include "agentes.h"

void* agente_de_desinfeccion(void* arg){
    while(1){
        sem_wait(&s_drone_esperando_agente); // espera a que llegue un dron.
        // seccion critica.
        printf("Agente desinfectando y validando bateria e ID... \n");
        sleep(1); // simula tiempo.
        sem_post(&s_agente_listo); // avisa al dron que puede pasar.
    }
    return NULL;
}

void* operario_de_almacen(void* arg){
    while(1){
        sem_wait(&s_operario); // duerme hasta que un brazo lo llame.

        // retira el producto y pone cajas nuevas.
        int id = deposito_a_vaciar;
        printf("Operario Vaciando deposito %d (Estaba lleno con 3 cajas).\n", id);
        sleep(2); // Tiempo de vaciado.
        cajas_en_deposito[id] = 0;
        sem_post(&s_deposito_vaciado); // avisa que ya vacio el deposito.
    }
    return NULL;
}