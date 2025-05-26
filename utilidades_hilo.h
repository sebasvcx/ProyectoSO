/************************************************************
 * @file utilidades_hilo.h
 * @brief Declaración de funciones auxiliares para hdispersa,
 *        incluyendo el parseo y validación de argumentos.
 ************************************************************/

#ifndef UTILIDADES_HILO_H
#define UTILIDADES_HILO_H

#include <stdbool.h>

bool validar_argumentos(int argc,
                        char *argv[],
                        int *filas,
                        int *columnas,
                        char *archivo,
                        int *numHilos,
                        int *porcentaje);

#endif // UTILIDADES_HILO_H