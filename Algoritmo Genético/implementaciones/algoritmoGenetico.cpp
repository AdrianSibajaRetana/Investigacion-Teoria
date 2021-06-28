#include "../interfaces/algoritmoGenetico.h"
#include <string>
#include<algorithm>
#include <time.h>

//Quitar
#include <iostream>

Individuo generarIndividuo(vector<int> numeros)
{
    vector<int> s1;
    vector<int> s2;
    vector<int> s3;
    for (int x : numeros)
    {
        int NumeroAleatorio = rand() % 3 + 1;
        switch(NumeroAleatorio) {
            case 1:
                s1.push_back(x);
                break;
            case 2:
                s2.push_back(x);
                break;
            case 3:
                s3.push_back(x);
                break;            
        }
    }
    Individuo individuoGenerado(s1,s2,s3);
    return individuoGenerado;  
}

algoritmoGenetico::algoritmoGenetico(int generaciones, int tamaño, double porcentajeM, double porcentajeC, vector<int> numeros, double elitismo, double peores)
{
    srand (time(NULL));
    cantidadDeGeneraciones = generaciones;
    tamañoDeGeneracion = tamaño;
    porcentajeDeMutacion = porcentajeM;
    porcentajeDeCruce = porcentajeC;
    numerosLeidos = numeros;
    mejoresIndividuos = elitismo;
    peoresIndividuos = peores;
}

void algoritmoGenetico::generarPoblacionInicial()
{
    int cantidadDeIndividuosCreados = 0;
    while(cantidadDeIndividuosCreados < tamañoDeGeneracion)
    {
        Individuo nuevoIndividuo = generarIndividuo(numerosLeidos);
        generacionActual.push_back(nuevoIndividuo);
        cantidadDeIndividuosCreados++;
    }
}

void algoritmoGenetico::evaluarPoblacionActual()
{
    for (Individuo& x : generacionActual)
        x.evaluar();

    sort(generacionActual.begin(), generacionActual.end(), [](const Individuo& lhs, const Individuo& rhs) {
      return lhs.puntaje < rhs.puntaje;
    });
}

void algoritmoGenetico::seleccionarIndividuos()
{
    int cantidadPeoresIndividuos = tamañoDeGeneracion * peoresIndividuos;
    for(int i = 0; i < cantidadPeoresIndividuos;)
    {
        Individuo individuoSeleccionado = generacionActual[i++];
        generacionSiguiente.push_back(individuoSeleccionado);
    }
    int cantidadMejoresIndividuos = tamañoDeGeneracion * mejoresIndividuos;
    for(int i = 0; i < cantidadMejoresIndividuos; i++)
    {
        int indice = generacionActual.size() - 1;
        indice = indice - i; 
        Individuo individuoSeleccionado = generacionActual[indice];
        generacionSiguiente.push_back(individuoSeleccionado);
    }
    cruzarIndividuos();
}

void algoritmoGenetico::cruzarIndividuos()
{
    while(generacionSiguiente.size() < tamañoDeGeneracion)
    {
        
    }
}

void algoritmoGenetico::mutarIndividuos()
{
    for (Individuo& x : generacionSiguiente)
        x.mutar(porcentajeDeMutacion);
}


void algoritmoGenetico::comenzarAlgoritmo()
{
    int numeroDeGeneracion = 1;
    generarPoblacionInicial();
    while(numeroDeGeneracion <= cantidadDeGeneraciones)
    {
        evaluarPoblacionActual();
        seleccionarIndividuos();                 
        mutarIndividuos();
        generacionActual = generacionSiguiente;
        generacionSiguiente.clear();
        numeroDeGeneracion++;
    }
}