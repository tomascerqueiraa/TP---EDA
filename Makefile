# Ficheiros-fonte
SRCS = ./main.c antenas/antenas.c efeitos/efeitos.c

# Regra principal: compilar o programa
make:
	gcc -Wall -g -o antenas.exe $(SRCS)

# Regra para compilar e executar
run: make
	./antenas.exe

# Gerar documentação com Doxygen
doc:
	doxygen Doxyfile

# Limpar ficheiros compilados
clean:
	rm -f antenas.exe
