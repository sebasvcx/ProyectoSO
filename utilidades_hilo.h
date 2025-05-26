/************************************************************
 * @file utilidades_hilo.h
 * @brief Declaración de funciones auxiliares para hdispersa,
 *        incluyendo el parseo y validación de argumentos.
 ************************************************************/

#ifndef UTILIDADES_HILO_H
#define UTILIDADES_HILO_H

#include <stdbool.h>

/**
 * @brief Valida y extrae los parámetros de entrada del programa.
 * 
 * @param argc      Cantidad de argumentos.
 * @param argv      Vector de cadenas con los argumentos.
 * @param filas     (salida) Número de filas de la matriz.
 * @param columnas  (salida) Número de columnas de la matriz.
 * @param archivo   (salida) Ruta al archivo de la matriz. Debe reservarse
 *                  al menos 128 bytes.
 * @param numHilos  (salida) Número de hilos a crear.
 * @param porcentaje(salida) Porcentaje de ceros requerido.
 * @return true si todos los argumentos fueron correctos;
 *         false en caso contrario.
 */
bool validar_argumentos(int argc,
                        char *argv[],
                        int *filas,
                        int *columnas,
                        char *archivo,
                        int *numHilos,
                        int *porcentaje);

#endif // UTILIDADES_HILO_H