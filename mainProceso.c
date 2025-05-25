/**********************************************
 * Título: Proyecto - Implementación con procesos
 * 
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 26 de mayo 2025
 * Autores: Thomas Arévalo Rodríguez, Sebastian Vargas Casquete, Diego Fernando Castrillón Cortes
 * 
 * Materia: Sistemas Operativos
 * Tópico: Identificación de matriz mediante concurrencia en procesos.
 * 
 * Descripción:
 * ------------
 * Este programa implementa una solución concurrente usando procesos en Linux (fork) para determinar si una matriz
 * es dispersa. Se divide la matriz entre varios procesos hijos, los cuales cuentan los elementos diferentes de cero
 * en su sección asignada. El proceso padre recopila los resultados y calcula el porcentaje de ceros para determinar
 * si la matriz cumple con el umbral de dispersión especificado por el usuario.
 * 
 * Uso:
 * - Compilación: make pdispersa
 * - Ejecución: ./pdispersa -f M -c N -a Narchivo -n Nprocesos -p porcentaje
 * 
 * Donde:
 * M: número de filas de la matriz que se encuentra almacenada en archivo
 * N: número de columnas de la matriz almacenada en archivo
 * Narchivo: nombre de archivo que contiene, en formato texto, la matriz que se va a examinar.
 * Nprocesos: número de procesos que se crearán para revisar el contenido de la matriz.
 * porcentaje: número entre 0 y 100 que indica el % de elementos con valor igual a 0 (cero) que debe tener la
 * matriz para ser considerada dispersa. Este valor será un número entero.
 *
 * Los selectores permiten identificar la función de cada parametro, se pueden poner en cualquier orden
 * siempre y cuando coincidan con el parametro que les siga.
 *
 * Dependencias:
 * - Uso de procesos (unistd.h)
 **********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "matriz.h"
#include "utilidades_proceso.h"

// Función que imprime cómo utilizar correctamente el programa
void imprimirUso(const char* nombrePrograma) {
    printf("Uso: %s -f M -c N -a Narchivo -n Nprocesos -p porcentaje\n", nombrePrograma);
    printf("Donde:\n");
    printf("  M: número de filas de la matriz\n");
    printf("  N: número de columnas de la matriz\n");
    printf("  Narchivo: nombre del archivo que contiene la matriz\n");
    printf("  Nprocesos: número de procesos a crear\n");
    printf("  porcentaje: porcentaje de ceros requerido (0-100)\n");
}

int main(int argc, char* argv[]) {
    int filas = 0, columnas = 0, numProcesos = 0, porcentaje = 0;
    char* nombreArchivo = NULL;
    int opcion;

    // Analizar argumentos de línea de comandos con getopt
    while ((opcion = getopt(argc, argv, "f:c:a:n:p:")) != -1) {
        switch (opcion) {
            case 'f':
                filas = atoi(optarg); // Asignar número de filas
                break;
            case 'c':
                columnas = atoi(optarg); // Asignar número de columnas
                break;
            case 'a':
                nombreArchivo = strdup(optarg); // Copiar nombre del archivo de matriz
                break;
            case 'n':
                numProcesos = atoi(optarg); // Asignar número de procesos a crear
                break;
            case 'p':
                porcentaje = atoi(optarg); // Porcentaje requerido de ceros
                break;
            default:
                imprimirUso(argv[0]);
                return 1;
        }
    }

    // Validar los argumentos de entrada
    if (filas <= 0 || columnas <= 0 || !nombreArchivo || numProcesos <= 0 || 
        porcentaje < 0 || porcentaje > 100) {
        printf("Error: Argumentos inválidos\n");
        imprimirUso(argv[0]);
        free(nombreArchivo);
        return 1;
    }

    // Leer la matriz desde el archivo especificado
    Matriz* matriz = leerMatrizDesdeArchivo(nombreArchivo, filas, columnas);
    free(nombreArchivo);
    
    if (!matriz) {
        printf("Error: No se pudo leer la matriz desde el archivo\n");
        return 1;
    }

    // Crear estructura de trabajo compartida entre procesos
    TrabajoProceso* trabajo = (TrabajoProceso*)malloc(sizeof(TrabajoProceso));
    if (!trabajo) {
        liberarMatriz(matriz);
        return 1;
    }

    long tiempoInicio = obtenerTiempoActual();

    // Crear procesos hijos y obtener el total de elementos distintos de cero
    int totalNoCero = crearProcesosHijos(numProcesos, matriz, trabajo);
    free(trabajo);

    if (totalNoCero < 0) {
        printf("Error: Falló el procesamiento de la matriz\n");
        liberarMatriz(matriz);
        return 1;
    }

    long tiempoFin = obtenerTiempoActual();

    // Imprimir información sobre la matriz y evaluar si es dispersa
    imprimirInfoMatriz(matriz, totalNoCero, porcentaje);
    
    // Calcular tiempo de procesamiento e imprimirlo
    double tiempoTotal = tiempoFin - tiempoInicio;
    printf("Tiempo total de procesamiento: %6.f microsegundos\n", tiempoTotal);

    // Liberar memoria usada por la matriz
    liberarMatriz(matriz);
    return 0;
} 
