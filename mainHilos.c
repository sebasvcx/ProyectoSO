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
    int **matriz = leerMatrizDesdeArchivo(archivo, filas, columnas);

    if (matriz == NULL){
        fprintf(stderr, "Error al leer la matriz desde el archivo %s\n", archivo);
        return EXIT_FAILURE;
    }

     // Conteo de ceros mediante hilos POSIX
    int totalNoCeros = contar_no_ceros_con_hilos(matriz, numHilos);

    //calcular el porcentaje de ceros
    double pctCeros = calcularPorcentajeCeros(matriz, totalNoCeros);

    //mostrar los resultados
    printf("La matriz '%s' tiene %.2f%% de ceros, ", archivo, pctCeros);
    if (pctCeros >= (double)porcentaje) {
        printf("por lo tanto, se considera dispersa.\n");
    } else {
        printf("por lo tanto, No se considera dispersa.\n");
    }

    liberarMatriz(matriz);
    return EXIT_SUCCESS;
}
