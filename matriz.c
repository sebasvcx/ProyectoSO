/**********************************************
 * Título: Proyecto - Implementación con procesos
 * 
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 26 de mayo 2025
 * Autores: Thomas Arévalo Rodríguez, Sebastian Vargas Casquete, Diego Fernando Castrillón Cortes
 * 
 * Materia: Sistemas Operativos
 * Tópico: Identificación de matriz mediante concurrencia en procesos.
 * Archivo: Implementación de funciones relacionadas a la matriz.
 * 
 * Descripción:
 * ------------
 * Este archivo implementa las funciones declaradas en matriz.h. Maneja la lectura, análisis
 * y liberación de estructuras que representan matrices en memoria.
 **********************************************/

#include "matriz.h"
#include <string.h>
#include <math.h>

// Lee los datos de una matriz desde un archivo de texto plano.
// El archivo debe contener valores enteros organizados en filas y columnas.
// Devuelve un puntero a una estructura matriz válida, o NULL si hay error.
Matriz* leerMatrizDesdeArchivo(const char* nombreArchivo, int filas, int columnas) {
    FILE* archivo = fopen(nombreArchivo, "r"); // Abre el archivo
    if (!archivo) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    // Reserva memoria para la estructura Matriz
    Matriz* matriz = (Matriz*)malloc(sizeof(Matriz));
    if (!matriz) {
        fclose(archivo);
        return NULL;
    }

    matriz->filas = filas;
    matriz->columnas = columnas;

    // Reserva memoria para las filas
    matriz->datos = (int**)malloc(filas * sizeof(int*));
    
    if (!matriz->datos) {
        free(matriz);
        fclose(archivo);
        return NULL;
    }

    // Reserva memoria para cada fila individualmente
    for (int i = 0; i < filas; i++) {
        matriz->datos[i] = (int*)malloc(columnas * sizeof(int));
        if (!matriz->datos[i]) {
            // En caso de error, liberar memoria previamente asignada
            for (int j = 0; j < i; j++) {
                free(matriz->datos[j]);
            }
            free(matriz->datos);
            free(matriz);
            fclose(archivo);
            return NULL;
        }
    }

    // Lee los elementos uno por uno desde el archivo
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (fscanf(archivo, "%d", &matriz->datos[i][j]) != 1) {
                // Limpia en caso de error de lectura
                liberarMatriz(matriz);
                fclose(archivo);
                return NULL;
            }
        }
    }

    fclose(archivo); // Cierra el archivo
    return matriz;
}

// Libera toda la memoria dinámica asociada a una estructura Matriz.
void liberarMatriz(Matriz* matriz) {
    if (!matriz) return;
    
    // Libera memoria de cada fila existente
    if (matriz->datos) {
        for (int i = 0; i < matriz->filas; i++) {
            free(matriz->datos[i]);
        }
        free(matriz->datos);
    }
    free(matriz);
}

// Recorre una subregión de la matriz y cuenta cuántos elementos no son cero.
// El rango está definido por [filaInicio, filaFin] y [colInicio, colFin]
int contarElementosNoCero(const Matriz* matriz, int filaInicio, int filaFin) {
    int contador = 0;
    for (int i = filaInicio; i < filaFin; i++) {
        for (int j = 0; j < matriz->columnas; j++) {
            if (matriz->datos[i][j] != 0) {
                contador++;
            }
        }
    }
    return contador;
}

// Calcula el porcentaje de ceros en función de los elementos distintos de cero detectados.
// Fórmula: %ceros = ((total - noCero) / total) * 100
double calcularPorcentajeCeros(const Matriz* matriz, int totalNoCero) {
    int totalElementos = matriz->filas * matriz->columnas;
    int totalCeros = totalElementos - totalNoCero;
    return (double)totalCeros / totalElementos * 100.0;
}

// Imprime un resumen sobre la dispersión de la matriz.
// Muestra la cantidad de ceros, ell porcentaje y si cumple el umbral dado.
void imprimirInfoMatriz(const Matriz* matriz, int totalNoCero, int porcentajeRequerido) {
    double porcentajeCeros = calcularPorcentajeCeros(matriz, totalNoCero);
    int totalElementos = matriz->filas * matriz->columnas;
    int totalCeros = totalElementos - totalNoCero;
    
    printf("La matriz en el archivo tiene un total de %d ceros (%.1f%%), ", 
           totalCeros, porcentajeCeros);
    
    if (porcentajeCeros >= porcentajeRequerido) {
        printf("por lo tanto, se considera dispersa.\n");
    } else {
        printf("por lo tanto, no se considera dispersa.\n");
    }
} 