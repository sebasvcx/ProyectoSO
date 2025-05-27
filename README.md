# ProyectoSO

> **Detección de matrices dispersas**
> Implementaciones concurrentes en C usando procesos (`fork`) y hilos POSIX (`pthread`).

## 🔎 Descripción

En álgebra lineal, una **matriz dispersa** es aquella con un alto porcentaje de ceros.
Este proyecto determina si una matriz es dispersa de forma **concurrente**:

1. **`pdispersa`**: crea procesos hijos con `fork()`.
2. **`hdispersa`**: crea hilos POSIX con `pthread_create()`.

Ambas versiones:

* Leen la matriz desde un archivo de texto.
* Reparten equitativamente las filas para el conteo de elementos no cero.
* Calculan el porcentaje de ceros y comparan con el umbral indicado.

---

## 📁 Estructura del repositorio

```text
ProyectoSO/
├── Makefile
├── mainProceso.c          # versión con procesos
├── mainHilos.c           # versión con hilos
├── matriz.c
├── matriz.h
├── utilidades_proceso.c
├── utilidades_proceso.h
├── utilidades_hilo.c
├── utilidades_hilo.h
├── hilo_logica.c
├── hilo_logica.h
├── matriz100.txt         # ejemplos de matriz para pruebas
├── Matriz200.txt
├── matriz500.txt
├── matriz1000.txt
├── matrizA.txt
├── matrizB.txt
└── matrizcorta.txt       # matriz pequeña de ejemplo
```

---

## ⚙️ Requisitos

* **Compilador C** compatible con C11 (ej. `gcc` o `clang`)
* **Make**
* Plataforma POSIX (Linux, macOS, WSL)

---

## 🛠️ Compilación

```bash
make clean    # elimina binarios y objetos
make all      # compila 'pdispersa' y 'hdispersa'
```

Se generarán dos ejecutables:

* `pdispersa`
* `hdispersa`

---

## 🚀 Ejecución

### pdispersa (procesos)

```bash
./pdispersa -f <filas> -c <columnas> -a <archivo> -n <numProcesos> -p <porcentaje>
```

**Ejemplo:**

```bash
./pdispersa -f 10 -c 4 -a matrizA.txt -n 3 -p 60
```

### hdispersa (hilos)

```bash
./hdispersa -f <filas> -c <columnas> -a <archivo> -n <numHilos> -p <porcentaje>
```

**Ejemplo:**

```bash
./hdispersa -f 10 -c 4 -a matrizA.txt -n 3 -p 60
```

---

## 👥 Autores

* Thomas Arévalo Rodríguez
* Sebastián Vargas Casquete
* Diego Fernando Castrillón Cortes

Pontificia Universidad Javeriana — Sistemas Operativos (Mayo 2025)
