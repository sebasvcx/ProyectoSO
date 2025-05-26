# Makefile para Proyecto_SO

CC       := gcc
CFLAGS   := -Wall -Wextra -std=c11
LDFLAGS  := -lm
THREADS  := -pthread

# Fuentes de cada ejecutable
SRCS_PROC := mainProceso.c matriz.c utilidades_proceso.c
SRCS_HILO := mainHilos.c   matriz.c utilidades_hilo.c hilo_logica.c

PROG_PROC := pdispersa
PROG_HILO := hdispersa

.PHONY: all clean

all: $(PROG_PROC) $(PROG_HILO)

# --------------------------------------------------
$(PROG_PROC): $(SRCS_PROC)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# --------------------------------------------------
$(PROG_HILO): $(SRCS_HILO)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(THREADS)

# --------------------------------------------------
clean:
	rm -f $(PROG_PROC) $(PROG_HILO) *.o
