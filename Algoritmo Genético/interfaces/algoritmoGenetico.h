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
        double creadosPorCruces;
        double mejoresIndividuos;
        double peoresIndividuos;
        vector<int> numerosLeidos;
        vector<Individuo> generacionActual;
        vector<Individuo> generacionSiguiente;
        void generarPoblacionInicial();
        void evaluarPoblacionActual();
        void seleccionarIndividuos();
        void cruzarIndividuos();
        void mutarIndividuos();
        
    public: 
        algoritmoGenetico(int generaciones, int tamaño, double porcentajeM, vector<int> numeros, double elitismo, double peores);
        void comenzarAlgoritmo();
        Individuo obtenerMejorIndividuo();
};

#endif 