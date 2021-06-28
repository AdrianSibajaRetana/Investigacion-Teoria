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
    vector<int> cadenaGenetica; 
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
        cadenaGenetica.push_back(NumeroAleatorio);
    }
    Individuo individuoGenerado(s1,s2,s3,cadenaGenetica);
    return individuoGenerado;  
}

// Se cruzan los genes de los padres para generar una nueva cadena genética
//   la cual está formada por la mitad de los genes del padre y la mitad de los 
//   genes de la madre. 
Individuo cruzarPadres(Individuo padre, Individuo madre, vector<int>& numeros)
{
    int indiceGenesHijo = 0;
    int mitad = numeros.size() / 2;
    vector<int> cadenaGenetica;
    int genLeido = 0;
    while(indiceGenesHijo < numeros.size())
    {        
        if(indiceGenesHijo <= mitad)
        {
            genLeido = padre.cadenaGenetica[indiceGenesHijo];
        }
        else
        {
            genLeido = madre.cadenaGenetica[indiceGenesHijo];
        }
        cadenaGenetica.push_back(genLeido);
        indiceGenesHijo++;
    }
    Individuo hijo(cadenaGenetica, numeros);
    return hijo;
}



algoritmoGenetico::algoritmoGenetico(int generaciones, int tamaño, double porcentajeM,  vector<int> numeros, double elitismo, double peores)
{
    srand (time(NULL));
    cantidadDeGeneraciones = generaciones;
    tamañoDeGeneracion = tamaño;
    porcentajeDeMutacion = porcentajeM;
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
    // Se ejecuta la función f(s1, s2, s3) = (s1 - s2)^2 + (s1 - s3)^2 + (s2 - s3)^2.
    //   para cada individuo y su respectivo resultado resulta como el puntaje. 
    for (Individuo& x : generacionActual)
        x.evaluar();

    // Se ordenan los individuos en orden a su puntaje.
    // El orden es de mayor a menor. 
    // Entre menos es la aptitud, mejor
    sort(generacionActual.begin(), generacionActual.end(), [](const Individuo& lhs, const Individuo& rhs) {
      return lhs.puntaje > rhs.puntaje;
    });
}

// Genera la siguiente generación del algoritmo genético. 
// Esta nueva generación es creada en el vector<Individuo> generacionSiguiente
void algoritmoGenetico::seleccionarIndividuos()
{
    // Se seleccionan los peores individuos a pasar a la siguiente generacion.
    int cantidadPeoresIndividuos = tamañoDeGeneracion * peoresIndividuos;
    for(int i = 0; i < cantidadPeoresIndividuos;)
    {
        Individuo individuoSeleccionado = generacionActual[i++];
        generacionSiguiente.push_back(individuoSeleccionado);
    }
    
    // Se seleccionan los mejores individuos a pasar a la siguiente generación.
    int cantidadMejoresIndividuos = tamañoDeGeneracion * mejoresIndividuos;
    for(int i = 0; i < cantidadMejoresIndividuos; i++)
    {
        int indice = generacionActual.size() - 1;
        indice = indice - i; 
        Individuo individuoSeleccionado = generacionActual[indice];
        generacionSiguiente.push_back(individuoSeleccionado);
    }

    // El resto de los individuso se consiguen mediante el cruce. 
    cruzarIndividuos();
}

// Genera los individuos restantes de la siguiente generación mediante el cruce. 
void algoritmoGenetico::cruzarIndividuos()
{
    // Se escogen los individuos que pertenezcan a el porcentaje superior 
    //  de la población actual.  
    double porcentajeElite = 0.3;
    int individuosElegibles = tamañoDeGeneracion * porcentajeElite;
    int indiceFinal = generacionActual.size() - 1;
    
    while(generacionSiguiente.size() < tamañoDeGeneracion)
    {

        // Se escogen a los padres aleatoriamente de la generación actual.
        int indiceIndividuo1 = rand() % individuosElegibles;
        int indiceIndividuo2 = rand() % individuosElegibles;
        indiceIndividuo1 = indiceFinal - indiceIndividuo1;
        indiceIndividuo2 = indiceFinal - indiceIndividuo2;
        Individuo padre = generacionActual[indiceIndividuo1];
        Individuo madre = generacionActual[indiceIndividuo2];
        
        // Se genera un hijo a partir de los individuos seleccionados 
        Individuo hijo = cruzarPadres(padre, madre, numerosLeidos);
        generacionSiguiente.push_back(hijo);
    }
}

//Se mutan los individuos seleccionados.
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

        cout<<"Generacion numero "<< numeroDeGeneracion<<endl;
        for (Individuo x : generacionActual)
            cout<<x.puntaje<<endl;
        cout<<"---------------------"<<endl;

        seleccionarIndividuos();                 
        mutarIndividuos();
        generacionActual = generacionSiguiente;
        generacionSiguiente.clear();
        numeroDeGeneracion++;
    }
    // Se evalua la última generación
    evaluarPoblacionActual();

    cout<<"Resultados de la ultima generacion numero "<< numeroDeGeneracion << endl; 
    for (Individuo x : generacionActual)
        cout<<x.puntaje<<endl;
}