/**********************************************
 * Título: Proyecto - Implementación con procesos
 * 
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 26 de mayo 2025
 * Autores: Thomas Arévalo Rodríguez, Sebastian Vargas Casquete, Diego Fernando Castrillón Cortes
 * 
 * Materia: Sistemas Operativos
 * Tópico: Identificación de matriz mediante concurrencia en procesos.
 * Archivo: Implementación de funciones relacionadas al manejo de procesos.
 * 
 * Descripción:
 * ------------
 * Este archivo implementa funciones para la creación y sincronización de procesos hijos
 * en un entorno concurrente. Cada proceso se encarga de contar elementos distintos de cero
 * en una sección específica de la matriz. La división se realiza por filas.
 **********************************************/

#include "utilidades_proceso.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// Función que asigna un rango de filas a un proceso específico.
// La matriz se divide de forma equitativa, y las filas restantes se reparten entre los primeros procesos.
TrabajoProceso* dividirTrabajoMatriz(int filas, int columnas, int numProcesos, int idProceso) {
    TrabajoProceso* trabajo = (TrabajoProceso*)malloc(sizeof(TrabajoProceso));
    if (!trabajo) return NULL;

    int filasPorProceso = filas / numProcesos;  // División base
    int filasExtra = filas % numProcesos;   // Filas sobrantes para repartir entre primeros procesos

    trabajo->idProceso = idProceso;

    // Si el ID es menor que la cantidad de filas extra, este proceso recibe una fila adicional
    if (idProceso < filasExtra) {
        trabajo->filaInicio = idProceso * (filasPorProceso + 1);
        trabajo->filaFin = trabajo->filaInicio + filasPorProceso + 1;
    } else {
        trabajo->filaInicio = idProceso * filasPorProceso + filasExtra;
        trabajo->filaFin = trabajo->filaInicio + filasPorProceso;
    }

    return trabajo;
}

// Función que crea "numProcesos" procesos hijos.
// Cada hijo cuenta los elementos no cero en su parte asignada de la matriz.
// y comunica el resultado al proceso padre utilizando un pipe anónimo.
// Devuelve el total de elementos distintos de cero encontrados por todos los hijos.
int crearProcesosHijos(int numProcesos, const Matriz* matriz, TrabajoProceso* trabajo) {
    pid_t* hijos = (pid_t*)malloc(numProcesos * sizeof(pid_t));
    if (!hijos) return -1;

    // Vector de pipes: cada hijo tiene un pipe [lectura, escritura]
    int pipes[numProcesos][2];

    for (int i = 0; i < numProcesos; i++) {
        // Crea un pipe para este hijo
        if (pipe(pipes[i]) == -1) {
            perror("Error al crear pipe");
            free(hijos);
            return -1;
        }

        // Calcular el rango de filas que trabajara este hijo
        TrabajoProceso* trabajoHijo = dividirTrabajoMatriz(matriz->filas, matriz->columnas, numProcesos, i);
        if (!trabajoHijo) {
            free(hijos);
            return -1;
        }

        hijos[i] = fork(); // Crea un proceso hijo
        
        if (hijos[i] < 0) {
            // Error al crear el proceso
            free(trabajoHijo);
            free(hijos);
            return -1;
        } else if (hijos[i] == 0) {
            // Código que ejecuta el proceso hijo

            // Cierra el extremo de lectura (el hijo solo escribe)
            close(pipes[i][0]);

            // Contar elementos distintos de cero en la sección asignada
            int conteoNoCero = contarElementosNoCero(matriz, trabajoHijo->filaInicio, trabajoHijo->filaFin);

            // Escribir el resultado en el pipe
            write(pipes[i][1], &conteoNoCero, sizeof(int));

            // Cerrar el pipe y liberar recursos
            close(pipes[i][1]);
            free(trabajoHijo);
            free(hijos);
            liberarMatriz((Matriz*)matriz); // Cast para liberar correctamente la memoria
            exit(0);
        }

        // Cierra extremo de escritura (el padre no lo usará)
        close(pipes[i][1]);

        // Libera estructura temporal de trabajo
        free(trabajoHijo);
    }

    // Espera y recolecta los resultados desde los pipes
    int totalNoCero = esperarProcesosHijos(numProcesos, hijos, pipes);
    free(hijos);
    return totalNoCero;
}

// Espera a que todos los hijos finalicen y suma sus resultados.
// Lee el conteo de elementos distintos de cero desde los pipes asociados.
// Devuelve la suma total de elementos no cero detectados por todos los hijos.
int esperarProcesosHijos(int numProcesos, pid_t* hijos, int pipes[][2]) {
    int totalNoCero = 0;
    int estado;

    for (int i = 0; i < numProcesos; i++) {
        // Espera a que el hijo termine
        if (waitpid(hijos[i], &estado, 0) == -1) {
            perror("Error al esperar por el hijo");
            continue;
        }

        //Lee el valor del pipe
        int resultado = 0;
        ssize_t bytesLeidos = read(pipes[i][0], &resultado, sizeof(int));

        if (bytesLeidos != sizeof(int)) {
            perror("No se pudo leer correctamente el resultado del hijo %d\n");
        } else {
            totalNoCero += resultado;
        }

        // Cierra el extremo de lectura del pipe
        close(pipes[i][0]);
    }

    return totalNoCero;
}

long obtenerTiempoActual() {
    struct timeval tiempo;
    gettimeofday(&tiempo, NULL);
    return (tiempo.tv_sec * 1000000L) + tiempo.tv_usec;
}