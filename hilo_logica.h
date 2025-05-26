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