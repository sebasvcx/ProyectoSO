/************************************************************
 * File: utilidades_hilo.c
 * Título: utilidades_hilo — Implementación de utilidades
 *
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 26 de mayo de 2025
 * Autores: Thomas Arévalo Rodríguez, Sebastián Vargas Casquete,
 *          Diego Fernando Castrillón Cortes
 *
 * Materia: Sistemas Operativos
 * Tópico: Función validar_argumentos()
 *
 * Descripción:
 *   Implementa la rutina validar_argumentos() que usa getopt()
 *   para extraer y comprobar filas, columnas, archivo,
 *   número de hilos y porcentaje.
 *
 * Dependencias:
 *   unistd.h, stdio.h, stdlib.h, string.h, utilidades_hilo.h
 ************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/time.h>
 #include <time.h>
 #include <string.h>
 #include "utilidades_hilo.h"

  bool validar_argumentos(int argc,
                        char *argv[],
                        int *filas,
                        int *columnas,
                        char *archivo,
                        int *numHilos,
                        int *porcentaje){
    int opt;
    bool f_ok = false, c_ok = false, a_ok = false, n_ok = false, p_ok = false;

    //Analizar las flags: f, c, a, n, p
    while ((opt = getopt(argc, argv, "f:c:a:n:p:")) != -1) {
        switch (opt) {
            case 'f':
                *filas = atoi(optarg);
                f_ok = (*filas > 0);
                break;
            case 'c':
                *columnas = atoi(optarg);
                c_ok = (*columnas > 0);
                break;
            case 'a':
                strncpy(archivo, optarg, 127);
                archivo[127] = '\0'; // Asegurar terminación nula
                a_ok = true;
                break;
            case 'n':
                *numHilos = atoi(optarg);
                n_ok = (*numHilos > 0);
                break;
            case 'p':
                *porcentaje = atoi(optarg);
                p_ok = (*porcentaje >= 0 && *porcentaje <= 100);
                break;
            default:
                fprintf(stderr, "Uso: %s -f <filas> -c <columnas> -a <archivo> -n <numHilos> -p <porcentaje>\n", argv[0]);
                return false;
        }
    }

    // Verificar que todas las opciones requeridas sean válidas
    if (!f_ok || !c_ok || !a_ok || !n_ok || !p_ok || optind != argc) {
        return false;
    }
    return true;
 }

 long obtenerTiempoActual() {
    struct timeval tiempo;
    gettimeofday(&tiempo, NULL);
    return (tiempo.tv_sec * 1000000L) + tiempo.tv_usec;
}
