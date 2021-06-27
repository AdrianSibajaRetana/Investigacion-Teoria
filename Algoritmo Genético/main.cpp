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
    int cantidadDeGeneraciones = 1;
    int tamañoDeGeneracion = 3;
    double porcentajeDeMutacion = 0.05;
    double porcentajeDeCruce = 0.50;
    vector<int> numeros = generarNumeros();
    algoritmoGenetico algoritmo(cantidadDeGeneraciones, tamañoDeGeneracion, porcentajeDeMutacion, porcentajeDeCruce, numeros);
    algoritmo.comenzarAlgoritmo();
    return 0;
}