all:
	g++ src/main.cpp src/implementations/*.cpp -o tarea_investigacion -O2 -Isrc/headers

.PHONY:
clean:
	rm -f tarea_investigacion