/************************************************************
 * File: utilidades_hilo.h
 * Título: utilidades_hilo — Declaración de utilidades para hilos
 *
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 26 de mayo de 2025
 * Autores: Thomas Arévalo Rodríguez, Sebastián Vargas Casquete,
 *          Diego Fernando Castrillón Cortes
 *
 * Materia: Sistemas Operativos
 * Tópico: Parseo y validación de argumentos
 *
 * Descripción:
 *   Provee la firma de la función validar_argumentos(),
 *   que gestiona el parseo de opciones y la validación de
 *   entradas de línea de comandos para hdispersa.
 *
 * Dependencias:
 *   stdbool.h
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

/**
 * @brief Obtiene el tiempo actual en microsegundos.
 * @return Tiempo actual como valor long (microsegundos).
 */
long obtenerTiempoActual();

#endif // UTILIDADES_HILO_H