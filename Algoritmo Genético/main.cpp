#include <iostream>
#include <fstream>
#include <string>
#include "./interfaces/algoritmoGenetico.h"

vector<int> generarNumeros()
{
    string line;
    ifstream myfile("Numeros.txt");
    vector<int> numeros;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            int numeroLeido = stoi(line);
            numeros.push_back(numeroLeido);
        }
        myfile.close();
    }
    return numeros;
}


int main() {

    // Propiedades del algoritmo genético
    int cantidadDeGeneraciones = 100;
    int tamañoDeGeneracion = 10;

    // Porcentaje de probabilidad que tiene un gen de cambiar valor
    double porcentajeDeMutacion = 0.01;

    //Formato de cambio de población
    //Se escogen el porcentaje de: 
    //                              mejores individuos
    //                              y peores individuos.
    // el resto de individuos nacerán a partir de cruces. 
    double mejoresIndividuos = 0.5;
    double peoresIndividuos = 0.1;

    vector<int> numeros = generarNumeros();
    algoritmoGenetico algoritmo(cantidadDeGeneraciones, tamañoDeGeneracion, porcentajeDeMutacion, numeros, mejoresIndividuos, peoresIndividuos);
    algoritmo.comenzarAlgoritmo();
    return 0;
}