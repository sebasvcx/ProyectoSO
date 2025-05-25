GCC = gcc
FLAGS = -lm

FILES = main.c matriz.c utilidades_proceso.c
PROGRAMA = pdispersa

$(PROGRAMA):
	$(GCC) $(FILES) -o $@

clean:
	$(RM) $(PROGRAMA) 