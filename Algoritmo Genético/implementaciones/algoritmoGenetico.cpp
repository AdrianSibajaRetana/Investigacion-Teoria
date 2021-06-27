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

algoritmoGenetico::algoritmoGenetico(int generaciones, int tamaño, double porcentajeM, double porcentajeC, vector<int> numeros)
{
    srand (time(NULL));
    cantidadDeGeneraciones = generaciones;
    tamañoDeGeneracion = tamaño;
    porcentajeDeMutacion = porcentajeM;
    porcentajeDeCruce = porcentajeC;
    numerosLeidos = numeros;
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

void algoritmoGenetico::comenzarAlgoritmo()
{
    generarPoblacionInicial();
    evaluarPoblacionActual();    
}