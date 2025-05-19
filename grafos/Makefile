# Regra principal
all: programa

programa: main.o grafos.o ../fase1/libfase1.a
	gcc -Wall -g -o programa main.o grafos.o -L../fase1 -lfase1 -lm

main.o: main.c grafos.h
	gcc -Wall -g -c main.c

grafos.o: grafos.c grafos.h
	gcc -Wall -g -c grafos.c

# Executar
run: all
	./programa

# Limpar tudo
clean:
	rm -f *.o programa
