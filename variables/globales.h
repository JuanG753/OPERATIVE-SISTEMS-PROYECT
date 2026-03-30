#ifndef GLOBALES_H
#define GLOBALES_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

#define NUM_DRONES_RECOLECTORES 100
#define MAX_CAPACIDAD_CENTRO 25
#define NUM_BRAZOS 3
#define NUM_DRONES_CARGA 4
#define NUM_DEPOSITOS 8 

// Colores para mas personalidad.
#define COLOR_ROJO "\033[1;31m"
#define COLOR_VERDE "\033[1;32m"
#define COLOR_CYAN "\033[1;36m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_RESET "\033[0m"
#define COLOR_AMARILLO "\033[1;33m"

// Metricas del sistema (Recursos compartidos):
extern int total_estandar;
extern int total_refrigerado;
extern int total_ultra;
extern int uso_plataforma;
extern int bloqueos_evitados;
extern float tiempo_total_procesamiento;

// Estado de los depositos:
extern int cajas_en_deposito[NUM_DEPOSITOS]; 
extern int deposito_a_vaciar; 

// Probabilidades
extern int prob_ultra; 
extern int prob_refri; 

// Semaforos:
extern sem_t s_capacidad;
extern sem_t mutex_metricas; 
extern sem_t s_drone_esperando_agente; 
extern sem_t s_agente_listo; 
extern sem_t s_brazos_disponibles; 
extern sem_t s_drones_carga;
extern sem_t s_plataforma;
extern sem_t mutex_logistica; 
extern sem_t s_solicitud_drone; 
extern sem_t s_drone_listo;     
extern sem_t mutex_depositos[NUM_DEPOSITOS]; 
extern sem_t s_operario; 
extern sem_t s_deposito_vaciado; 

#endif