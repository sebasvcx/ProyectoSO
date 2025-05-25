/**********************************************
 * Título: Proyecto - Implementación con procesos
 * 
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 26 de mayo 2025
 * Autores: Thomas Arévalo Rodríguez, Sebastian Vargas Casquete, Diego Fernando Castrillón Cortes
 * 
 * Materia: Sistemas Operativos
 * Tópico: Identificación de matriz mediante concurrencia en procesos.
 * Archivo: Declaración de funciones relacionadas al manejo de procesos.
 * 
 * Descripción:
 * ------------
 * Este archivo define las estructuras y funciones para realizar operaciones con procesos
 * en el contexto del análisis concurrente de matrices. Contiene la estructura para
 * representar la tarea de cada proceso y prototipos de funciones para dividir el trabajo,
 * crear procesos hijos y esperar resultados.
 **********************************************/

#ifndef UTILIDADES_PROCESO_H
#define UTILIDADES_PROCESO_H

#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include "matriz.h"

// Estructura que representa el rango de trabajo asignado a un proceso hijo
typedef struct {
    int filaInicio; // Fila inicial del bloque asignado al proceso
    int filaFin;    // Fila final (no inclusiva)
    int idProceso;  // ID lógico del proceso dentro del conjunto creado
} TrabajoProceso;

// Divide la matriz entre procesos según el ID de cada uno, asignando un bloque por filas.
// Devuelve una estructura con el rango de filas a procesar.
TrabajoProceso* dividirTrabajoMatriz(int filas, int columnas, int numProcesos, int idProceso);

// Crea múltiples procesos hijos para analizar porciones de la matriz de manera concurrente.
// Devuelve el total de elementos diferentes de cero encontrados por todos los procesos.
int crearProcesosHijos(int numProcesos, const Matriz* matriz, TrabajoProceso* trabajo);

// Espera a que todos los procesos hijos terminen y suma los resultados devueltos.
// Maneja correctamente los códigos de salida, incluyendo el caso especial de conteo > 254.
int esperarProcesosHijos(int numProcesos, pid_t* hijos, int pipes[][2]);

// Calcular el tiempo de procesamiento
long obtenerTiempoActual();

#endif // UTILIDADES_PROCESO_H 