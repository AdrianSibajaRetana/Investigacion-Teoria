#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <functional>

#include "algoritmoGenetico.h"
#include "simulatedAnnealing.h"
#include "solutionSA.h"

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

void ejecutarAlgoritmoGenetico() {
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
    AlgoritmoGenetico algoritmo(cantidadDeGeneraciones, tamañoDeGeneracion, porcentajeDeMutacion, numeros, mejoresIndividuos, peoresIndividuos);
    algoritmo.comenzarAlgoritmo();
}

void ejecutarSimulatedAnnealing() {
    int iterations_per_temp = 1000;
    double initial_temperature = 10000;

    SimulatedAnnealing<SolutionSA> simulatedAnnealing(initial_temperature, iterations_per_temp, solution_evaluator, get_neighborhood);
    vector<int> numbers = generarNumeros();
    vector<ll> first_set;
    std::transform(numbers.begin(), numbers.end(), back_inserter(first_set), [](int n) { return (ll) n; });

    SolutionSA initial_solution(disjoint_sets_t{{ first_set, std::vector<ll>(), std::vector<ll>() }});
    auto solution = simulatedAnnealing.run(initial_solution);

    std::cout << solution << '\n';
}


enum Algoritmos {
    algoritmoGenetico,
    simulatedAnnealing
};


int main(int argc, char** argv) {

    if (argc <= 1) {
        return std::cerr << "Uso: ./tarea_investigacion {ALGORITMO}, donde {ALGORITMO} puede ser algoritmoGenetico o simulatedAnnealing\n", 1;
    }


    Algoritmos algoritmo;

    if (std::string(argv[1]) == "algoritmoGenetico") {
        algoritmo = Algoritmos::algoritmoGenetico;
    }
    else if (std::string(argv[1]) == "simulatedAnnealing") {
        algoritmo = Algoritmos::simulatedAnnealing;
    }
    else {
        return std::cerr << "Algoritmo " << argv[1] << " no reconocido.\n", 2;
    }

    if (algoritmo == Algoritmos::algoritmoGenetico) {
        ejecutarAlgoritmoGenetico();
    }
    else if (algoritmo == Algoritmos::simulatedAnnealing) {
        ejecutarSimulatedAnnealing();
    }

    return 0;
}
