CFLAGS = -O
CC = g++
SRC = main.cpp Individuo.cpp
OBJ = $(SRC:.cpp = .o)

# g++ .\main.cpp .\implementaciones\individuo.cpp -o main

Ejecutable: $(OBJ)
 $(CC) $(CFLAGS) -o Ejecutable $(OBJ)
clean:
 rm -f core *.o