#pragma once

#include "individuo.h"
#include <tuple>

class AlgoritmoGenetico
{
    private:
        // propiedades principales (seteadas por main.cpp)
        int cantidadDeGeneraciones;
        int tamañoDeGeneracion;
        double porcentajeDeMutacion;
        double mejoresIndividuos;
        double peoresIndividuos;
        // números leídos del .txt
        vector<int> numerosLeidos;
        // Almacena la generación Actual
        vector<Individuo> generacionActual;
        // Almacena la siguiente Generación
        vector<Individuo> generacionSiguiente;
        // Métodos para llevar a cabo las distintas partes del algoritmo
        void generarPoblacionInicial();
        void evaluarPoblacionActual();
        void seleccionarIndividuos();
        void cruzarIndividuos();
        void mutarIndividuos();

    public:
        AlgoritmoGenetico(int generaciones, int tamaño, double porcentajeM, vector<int> numeros, double elitismo, double peores);
        void comenzarAlgoritmo();
};
