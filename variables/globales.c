#include "globales.h"

int total_estandar = 0;
int total_refrigerado = 0;
int total_ultra = 0;
int uso_plataforma = 0;
int bloqueos_evitados = 0;
float tiempo_total_procesamiento = 0.0;

int cajas_en_deposito[NUM_DEPOSITOS] = {0}; 
int deposito_a_vaciar = -1; 

int prob_ultra = 20; // 10% de probabilidad normal
int prob_refri = 35; // 30% de probabilidad normal

sem_t s_capacidad;
sem_t mutex_metricas; 
sem_t s_drone_esperando_agente; 
sem_t s_agente_listo; 
sem_t s_brazos_disponibles; 
sem_t s_drones_carga;
sem_t s_plataforma;
sem_t mutex_logistica; 
sem_t s_solicitud_drone; 
sem_t s_drone_listo;     
sem_t mutex_depositos[NUM_DEPOSITOS]; 
sem_t s_operario; 
sem_t s_deposito_vaciado;