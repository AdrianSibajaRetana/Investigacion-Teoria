#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H
#include "individuo.h"
#include <tuple>

class algoritmoGenetico
{
    private:
        int cantidadDeGeneraciones;        
        int tamañoDeGeneracion;
        double porcentajeDeMutacion;
        double porcentajeDeCruce;
        vector<int> numerosLeidos;
        vector<Individuo> generacionActual;
        void generarPoblacionInicial();
        void evaluarPoblacionActual();

    public: 
        algoritmoGenetico(int generaciones, int tamaño, double porcentajeM, double porcentajeC, vector<int> numeros);
        void comenzarAlgoritmo();
        Individuo obtenerMejorIndividuo();
};

#endif 