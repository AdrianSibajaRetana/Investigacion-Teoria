CFLAGS = -O
CC = g++
SRC = main.cpp Individuo.cpp
OBJ = $(SRC:.cpp = .o)

# g++ .\main.cpp .\implementaciones\individuo.cpp .\implementaciones\algoritmoGenetico.cpp  -o ejecutable

Ejecutable: $(OBJ)
 $(CC) $(CFLAGS) -o Ejecutable $(OBJ)
clean:
 rm -f core *.o