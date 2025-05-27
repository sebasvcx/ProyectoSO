/************************************************************
 * File: hilo_logica.h
 * Título: hilo_logica — Declaración de funciones para hilos
 *
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 26 de mayo de 2025
 * Autores: Thomas Arévalo Rodríguez, Sebastián Vargas Casquete,
 *          Diego Fernando Castrillón Cortes
 *
 * Materia: Sistemas Operativos
 * Tópico: Declaración de la función de conteo concurrente
 *
 * Descripción:
 *   Provee la firma de la función que crea n hilos POSIX
 *   para contar elementos distintos de cero en una matriz.
 *
 * Dependencias:
 *   matriz.h, pthread.h
 ************************************************************/

#ifndef HILO_LOGICA_H
#define HILO_LOGICA_H

#include "matriz.h"

/**
 * @brief Crea 'numHilos' hilos POSIX para contar cuántos ceros hay
 *        en la matriz.
 *
 * @param matriz   Puntero a la estructura Matriz (filas, columnas y datos).
 * @param numHilos Número de hilos a lanzar.
 * @return int     Total de ceros contados.
 */
int contar_no_ceros_con_hilos(Matriz *matriz, int numHilos);

#endif /* HILO_LOGICA_H */