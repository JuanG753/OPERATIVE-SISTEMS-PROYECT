# OPERATIVE-SISTEMS-PROYECT
Proyecto final de sistemas operativos: creacion de un programa concurrente


# Agro-Bots 2026 - Simulación Concurrente

**Autor/s:** Juan Pablo Gomez Sevilla y Victoria Eugenia Alvarado Pacheco
**Materia:** Sistemas Operativos

## Descripción
Este proyecto simula el sistema automatizado "Agro-Bots 2026" utilizando programación concurrente en C. Se implementan hilos POSIX (`pthreads`) y semáforos para orquestar el flujo de productos agrícolas, garantizando la sincronización, la exclusión mutua y la prevención de abrazos mortales (*deadlocks*) en un entorno con recursos compartidos y limitados.

El código cuenta con salidas de consola utilizando secuencias de escape ANSI (colores) para facilitar la auditoría visual de los bloqueos, liberaciones y asignación de recursos críticos.

## Requisitos del Sistema
* Entorno Linux (Nativo, Máquina Virtual o WSL)
* Compilador GCC
* Utilidad Make

## Compilación
Para compilar el código fuente con las banderas de advertencia estrictas (`-Wall -Wextra`) y la librería de hilos (`-pthread`), abre la terminal en el directorio del proyecto y ejecuta:

```bash
make

