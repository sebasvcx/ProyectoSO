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

// Estructura que representa una matriz entera de MxN elementos.
typedef struct {
    int filas;  // Número de filas
    int columnas; // Número de columnas
    int** datos; // Puntero doble que almacena la matriz de enteros
} Matriz;

// Lee una matriz desde un archivo de texto.
// Retorna puntero a la estructura Matriz si es exitosa, NULL si falla.
Matriz* leerMatrizDesdeArchivo(const char* nombreArchivo, int filas, int columnas);

// Libera la memoria dinámica ocupada por una estructura Matriz.
void liberarMatriz(Matriz* matriz);

// Cuenta cuántos elementos son distintos de cero en un subrango de la matriz.
int contarElementosNoCero(const Matriz* matriz, int filaInicio, int filaFin);

// Calcula el porcentaje de ceros basado en el total de elementos y cantidad de no ceros.
double calcularPorcentajeCeros(const Matriz* matriz, int totalNoCero);

// Imprime información general sobre la matriz y si cumple con el porcentaje de ceros requerido.
void imprimirInfoMatriz(const Matriz* matriz, int totalNoCero, int porcentajeRequerido);

#endif // MATRIZ_H 