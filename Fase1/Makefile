# Regra principal
all: fase1

# Compilar os objetos da fase 1
main.o: main.c
	gcc -Wall -g -c $< -o $@

./antenas/antenas.o: ./antenas/antenas.c
	gcc -Wall -g -c $< -o $@

./efeitos/efeitos.o: ./efeitos/efeitos.c
	gcc -Wall -g -c $< -o $@

# Criar biblioteca estática
libfase1.a: ./antenas/antenas.o ./efeitos/efeitos.o
	ar rcs libfase1.a $^

# Compilar o executável com os objetos da fase 1
fase1: main.o ./antenas/antenas.o ./efeitos/efeitos.o
	gcc -Wall -g -o $@ $^

# Executar
run: fase1
	./fase1

# Limpar ficheiros gerados
clean:
	rm -f *.o ./antenas/*.o ./efeitos/*.o fase1 libfase1.a


# Gerar documentação com Doxygen
doc:
	doxygen Doxyfile