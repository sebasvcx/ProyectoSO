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

/**
 * @struct TrabajoProceso
 * @brief Representa el rango de trabajo asignado a un proceso hijo.
 *
 * @var filaInicio Fila inicial (inclusive) del bloque asignado.
 * @var filaFin Fila final (exclusiva) del bloque asignado.
 * @var idProceso Identificador lógico del proceso.
 */
typedef struct {
    int filaInicio; // Fila inicial del bloque asignado al proceso
    int filaFin;    // Fila final (no inclusiva)
    int idProceso;  // ID lógico del proceso dentro del conjunto creado
} TrabajoProceso;

/**
 * @brief Divide la matriz entre procesos y asigna un bloque por filas.
 *
 * @param filas Número total de filas en la matriz.
 * @param columnas Número total de columnas.
 * @param numProcesos Total de procesos a crear.
 * @param idProceso ID del proceso actual.
 * @return Puntero a estructura TrabajoProceso con el rango asignado.
 */
TrabajoProceso* dividirTrabajoMatriz(int filas, int columnas, int numProcesos, int idProceso);

/**
 * @brief Crea múltiples procesos hijos para trabajar sobre la matriz.
 *
 * @param numProcesos Número de procesos a crear.
 * @param matriz Puntero a la matriz.
 * @param trabajo Estructura de trabajo compartida.
 * @return Total de elementos distintos de cero.
 */
int crearProcesosHijos(int numProcesos, const Matriz* matriz, TrabajoProceso* trabajo);

/**
 * @brief Espera a que todos los procesos hijos terminen y recoge sus resultados.
 *
 * @param numProcesos Número de procesos hijos.
 * @param hijos Array con los PID de los procesos hijos.
 * @param pipes Matriz de pipes usados para comunicación.
 * @return Total acumulado de elementos diferentes de cero.
 */
int esperarProcesosHijos(int numProcesos, pid_t* hijos, int pipes[][2]);

/**
 * @brief Obtiene el tiempo actual en microsegundos.
 * @return Tiempo actual como valor long (microsegundos).
 */
long obtenerTiempoActual();

#endif // UTILIDADES_PROCESO_H 
