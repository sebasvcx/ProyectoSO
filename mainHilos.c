/************************************************************
 * Título: hdispersa — Implementación con hilos
 *
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 26 de mayo de 2025
 * Autores: Thomas Arévalo Rodríguez, Sebastián Vargas Casquete,
 *          Diego Fernando Castrillón Cortes
 *
 * Materia: Sistemas Operativos
 * Tópico: Conteo concurrente de elementos de matriz usando POSIX threads
 *
 * Descripción:
 *   Este programa contiene la función main para la versión con
 *   hilos (hdispersa). Se encarga de parsear los argumentos,
 *   cargar la matriz, lanzar/juntar los hilos y decidir si la
 *   matriz es dispersa según el porcentaje de ceros.
 *
 * Uso:
 *   make hdispersa
 *   ./hdispersa -f <filas> -c <columnas>
 *               -a <archivo> -n <numHilos> -p <porcentaje>
 *
 * Dependencias:
 *   pthread.h, matriz.h, utilidades_hilo.h, hilo_logica.h
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "matriz.h"
#include "utilidades_hilo.h"
#include "hilo_logica.h"

/**
 * @brief Punto de entrada: parsea parámetros, carga la matriz,
 *        lanza los hilos y decide si la matriz es dispersa.
 *
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Arreglo de cadenas con los argumentos.
 * @return int EXIT_SUCCESS en éxito, EXIT_FAILURE en error.
 */

int main(int argc, char *argv[]){
    //declaracion de variables
    int filas, columnas, numHilos, porcentaje;
    char archivo[128];

    //validar y extraer argumentos
    if (!validar_argumentos(
        argc,
        argv,
        &filas,
        &columnas,
        archivo,
        &numHilos,
        &porcentaje
    )){
        return EXIT_FAILURE;
    }

    //carga de matriz en oa memoria
    //int **matriz = leerMatrizDesdeArchivo(archivo, filas, columnas);
    Matriz *matriz = leerMatrizDesdeArchivo(archivo, filas, columnas);

    if (matriz == NULL){
        fprintf(stderr, "Error al leer la matriz desde el archivo %s\n", archivo);
        return EXIT_FAILURE;
    }

    long tiempoInicio = obtenerTiempoActual();

     // Conteo de No-ceros mediante hilos POSIX
    int totalNoCeros = contar_no_ceros_con_hilos(matriz, numHilos);
    
    long tiempoFin = obtenerTiempoActual();

    //mostrar los resultados
    // Imprimir información sobre la matriz y evaluar si es dispersa
    imprimirInfoMatriz(matriz, totalNoCeros, porcentaje);

    // Calcular tiempo de procesamiento e imprimirlo
    double tiempoTotal = tiempoFin - tiempoInicio;
    printf("Tiempo total de procesamiento: %6.f microsegundos\n", tiempoTotal);

    //liberar estructura matriz
    liberarMatriz(matriz);
    return EXIT_SUCCESS;
}
