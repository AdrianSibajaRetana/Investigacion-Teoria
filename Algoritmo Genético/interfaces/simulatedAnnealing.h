#include <cmath>
#include <cstdint>
#include <functional>
#include <random>
#include <vector>

template<class T>
class SimulatedAnnealing {
private:
    double const c_final_temperature = 0;

    double m_temperature;
    uint32_t  m_iterations_per_temp;

    std::function<double (T)> m_solution_evaluator;
    std::function<double (double)> m_reduce_temperature;
    std::function<std::vector<T> (T)> m_get_neighborhood;

    std::mt19937 m_generator;

    bool is_finished(T current_solution, std::vector<T> neighborhood) {
        return m_temperature <= c_final_temperature || neighborhood.empty();
    }

    T get_random_neighbor(std::vector<T> neighborhood) {
        auto start = neighborhood.begin();
        auto end = neighborhood.end();

        auto it = neighborhood.begin();

        std::uniform_int_distribution<> unif(0, std::distance(start, end) - 1);
        std::advance(it, unif(m_generator));

        return *it;
    }

public:
    SimulatedAnnealing(
            uint32_t iterations_per_temp,
            double initial_temperature,
            std::function<double (T)> solution_evaluator,
            std::function<double (double)> reduce_temperature,
            std::function<std::vector<T> (T)> get_neighborhood)
        :
            m_temperature(initial_temperature),
            m_iterations_per_temp(iterations_per_temp),
            m_solution_evaluator(solution_evaluator),
            m_reduce_temperature(reduce_temperature),
            m_get_neighborhood(get_neighborhood)
    {
    }

    T run(T initial_solution) {
        auto solution = initial_solution;
        auto neighborhood = m_get_neighborhood(solution);
        while (!is_finished(neighborhood)) {
            for (int i = 0; i < m_iterations_per_temp; ++i) {
                neighborhood = m_get_neighborhood(solution);

                auto new_solution = get_random_neighbor(neighborhood);
                auto cost = m_solution_evaluator(solution) - m_solution_evaluator(new_solution);

                if (cost >= 0) {
                    solution = new_solution;
                }
                else {
                    std::uniform_int_distribution<> unif(0, 1);
                    double probability = exp(-cost, m_temperature);
                    if (unif(m_generator) < probability) {
                        solution = new_solution;
                    }

                }
            }

            m_temperature = m_reduce_temperature(m_temperature);
        }

        return solution;
    }
};

