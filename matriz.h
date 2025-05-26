/**********************************************
 * Título: Proyecto - Implementación con procesos
 * 
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 26 de mayo 2025
 * Autores: Thomas Arévalo Rodríguez, Sebastian Vargas Casquete, Diego Fernando Castrillón Cortes
 * 
 * Materia: Sistemas Operativos
 * Tópico: Identificación de matriz mediante concurrencia en procesos.
 * Archivo: Declaración de funciones relacionadas a la matriz.
 * 
 * Descripción:
 * ------------
 * Este archivo define la estructura de datos para una matriz y declara las funciones que permiten:
 * - Leer una matriz desde un archivo.
 * - Liberar la memoria asociada.
 * - Contar los elementos distintos de cero en un subrango.
 * - Calcular el porcentaje de ceros en la matriz.
 * - Imprimir los resultados de análisis de dispersión.
 **********************************************/

#ifndef MATRIZ_H
#define MATRIZ_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @struct Matriz
 * @brief Representa una matriz de enteros con memoria dinámica.
 *
 * @var filas Número de filas.
 * @var columnas Número de columnas.
 * @var datos Matriz dinámica de enteros.
 */
typedef struct {
    int filas;  // Número de filas
    int columnas; // Número de columnas
    int** datos; // Puntero doble que almacena la matriz de enteros
} Matriz;

/**
 * @brief Lee una matriz desde un archivo de texto plano.
 *
 * @param nombreArchivo Ruta del archivo.
 * @param filas Número de filas esperadas.
 * @param columnas Número de columnas esperadas.
 * @return Puntero a Matriz si es exitoso, NULL si falla.
 */
Matriz* leerMatrizDesdeArchivo(const char* nombreArchivo, int filas, int columnas);

/**
 * @brief Libera la memoria asociada a una matriz.
 *
 * @param matriz Puntero a la matriz que se desea liberar.
 */
void liberarMatriz(Matriz* matriz);

/**
 * @brief Cuenta los elementos distintos de cero en una subregión de la matriz.
 *
 * @param matriz Puntero a la matriz.
 * @param filaInicio Índice de fila inicial (inclusive).
 * @param filaFin Índice de fila final (exclusiva).
 * @return Número de elementos diferentes de cero.
 */
int contarElementosNoCero(const Matriz* matriz, int filaInicio, int filaFin);

/**
 * @brief Calcula el porcentaje de ceros en la matriz.
 *
 * @param matriz Puntero a la matriz.
 * @param totalNoCero Número de elementos diferentes de cero.
 * @return Porcentaje de elementos cero en la matriz.
 */
double calcularPorcentajeCeros(const Matriz* matriz, int totalNoCero);

/**
 * @brief Imprime información sobre la dispersión de la matriz.
 *
 * @param matriz Puntero a la matriz.
 * @param totalNoCero Número de elementos distintos de cero.
 * @param porcentajeRequerido Porcentaje mínimo requerido para considerarla dispersa.
 */
void imprimirInfoMatriz(const Matriz* matriz, int totalNoCero, int porcentajeRequerido);

#endif // MATRIZ_H 
