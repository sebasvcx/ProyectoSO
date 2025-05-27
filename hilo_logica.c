/************************************************************
 * File: hilo_logica.c
 * Título: hilo_logica — Implementación de conteo con hilos
 *
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 26 de mayo de 2025
 * Autores: Thomas Arévalo Rodríguez, Sebastián Vargas Casquete,
 *          Diego Fernando Castrillón Cortes
 *
 * Materia: Sistemas Operativos
 * Tópico: Worker y función de creación/junción de hilos
 *
 * Descripción:
 *   Implementa el worker que recorre su bloque de filas
 *   contando elementos no cero y la función que reparte
 *   las filas, lanza hilos y acumula sus resultados.
 *
 * Dependencias:
 *   pthread.h, matriz.h, hilo_logica.h
 ************************************************************/

#include <pthread.h>
#include <stdlib.h>
#include "hilo_logica.h"
#include "matriz.h"

typedef struct {
    Matriz *m;
    int filaInicio;
    int filaFin;
    int noCerosLocal;
} ThreadParam;

static void *worker(void *arg){
    ThreadParam *p = (ThreadParam *) arg; 

    p->noCerosLocal = contarElementosNoCero(
        p->m,
        p->filaInicio,
        p->filaFin
    );
    return NULL;
}

int contar_no_ceros_con_hilos(Matriz *matriz, int numHilos){
    int filas = matriz->filas;

    //reservar memoria para los hilos y sus parámetros
    pthread_t *threads = malloc(sizeof(*threads) * numHilos);
    ThreadParam *params = malloc(sizeof(*params) * numHilos);

    int base = filas / numHilos; //elegimos hacerlos por hilos
    int resto = filas % numHilos; //y el resto de filas
    int offset = 0;

    for (int i = 0; i < numHilos; i++){
        int chunk = base + (i < resto ? 1 : 0); //asignamos el tamaño del chunk
        params[i] = (ThreadParam){
            .m = matriz,
            .filaInicio = offset,
            .filaFin = offset + chunk,
            .noCerosLocal = 0
        };
        offset += chunk; //actualizamos el offset para el siguiente hilo
        pthread_create(
            &threads[i],
            NULL,
            worker,
            &params[i]
        );
    }

    int totalNoCeros = 0;
    for (int i = 0; i < numHilos; i++){
        pthread_join(threads[i], NULL); //esperar a que terminen los hilos
        totalNoCeros += params[i].noCerosLocal; //sumamos los resultados locales
    }

    //liberar memoria
    free(threads);
    free(params);
    return totalNoCeros; //devolver el total de ceros
}
