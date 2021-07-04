#include <cmath>
#include <cstdint>
#include <functional>
#include <random>
#include <vector>

/*
 * Esta clase representa un solucionador de un problema por medio de la metaheurística conocida como Simulated Annealing (SA).
 * El argumento de plantilla [T] representa el tipo de la solución del problema.
 * El algoritmo se programó de forma genérica para que funcione para toda clase de problemas, siempre y cuando el usuario provea información correcta sobre el problema con el que está tratando.
 * Debe indicar el estado inicial del problema, un evaluador de soluciones, y una función que para una posible solución encuentra su vecindario.
 * Además es necesario proveer parámetros específicos para el algoritmo, como la cantidad de iteraciones antes de modificar la temperatura, la temperatura inicial y la función de cambio de la temperatura.
 */
template<class T>
class SimulatedAnnealing {
private:
    static constexpr double FINAL_TEMPERATURE = 0;

    uint32_t  m_iterations_per_temp;
    uint32_t m_iterations;
    double m_temperature;

    std::function<double (T)> m_solution_evaluator;
    std::function<std::vector<T> (T)> m_get_neighborhood;

    std::mt19937 m_generator;

    /*
     * La condición de parada es que la temperatura actual sea menor o igual a 0 o que el algoritmo se atasque porque la solución actual tiene un vecindario vacío.
     */
    bool is_finished(std::vector<T> neighborhood) {
        return m_temperature <= FINAL_TEMPERATURE || neighborhood.empty();
    }

    T get_random_neighbor(std::vector<T> neighborhood) {
        auto start = neighborhood.begin();
        auto end = neighborhood.end();

        auto it = neighborhood.begin();

        std::uniform_int_distribution<> unif(0, std::distance(start, end) - 1);
        std::advance(it, unif(m_generator));

        return *it;
    }

    double default_temperature_reducer(double temperature) {
        return temperature / (m_iterations + 1.0);
    }

public:
    SimulatedAnnealing(
            double initial_temperature,
            uint32_t iterations_per_temp,
            const std::function<double (T)>& solution_evaluator,
            const std::function<std::vector<T> (T)>& get_neighborhood)
        :
            m_iterations(0),
            m_generator(std::random_device()()),
            m_temperature(initial_temperature),
            m_iterations_per_temp(iterations_per_temp),
            m_solution_evaluator(solution_evaluator),
            m_get_neighborhood(get_neighborhood)
    {
    }

    /*
     * Ejecuta el algoritmo de Simulated Annealing a partir de la solución inicial [initial_solution]. Retorna la solución encontrada.
     */
    T run(T initial_solution) {
        // inicializamos valores para el algoritmo
        auto solution = initial_solution;
        auto neighborhood = m_get_neighborhood(solution);

        // el algoritmo continúa hasta no llegar a la condición de parada
        while (!is_finished(neighborhood)) {
            // podemos repetir varias veces la misma temperatura antes de decrementar, dependiendo de cómo se configure el algoritmo.
            for (int i = 0; i < m_iterations_per_temp; ++i) {
                // se calcula el vecindario para la solución actual.
                neighborhood = m_get_neighborhood(solution);

                // se obtiene una nueva solución aleatoria del vecindario.
                auto new_solution = get_random_neighbor(neighborhood);
                // se compara con la solución actual.
                auto cost = m_solution_evaluator(solution) - m_solution_evaluator(new_solution);

                // si la solución encontrada es mejor que la actual, entonces se acepta.
                if (cost >= 0) {
                    solution = new_solution;
                }
                // de lo contrario, se hace un cálculo probabilístico que depende de la temperatura y el costo para determinar si se acepta la solución o no.
                else {
                    std::uniform_real_distribution<> unif(0, 1);
                    double probability = exp(-cost / m_temperature);
                    if (unif(m_generator) < probability) {
                        solution = new_solution;
                    }
                }
            }

            // se reduce la temperatura actual.
            m_temperature = default_temperature_reducer(m_temperature);
            ++m_iterations;
        }

        // solución encontrada.
        return solution;
    }
};
