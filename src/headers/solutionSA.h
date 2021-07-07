#pragma once

#include <array>
#include <cmath>
#include <numeric>
#include <ostream>
#include <random>
#include <vector>
#include <utility>

using ll = long long int;
using disjoint_sets_t = std::array<std::vector<ll>, 3>;

class SolutionSA {
public:
    static const int ALTERNATE_SOLUTIONS = 10;
    static const int NUMBERS_TO_TAKE = 10;
    disjoint_sets_t m_disjoint_sets;

    SolutionSA(disjoint_sets_t disjoint_sets)
        : m_disjoint_sets(std::move(disjoint_sets))
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const SolutionSA& solution) {
        for (int i = 0; i < solution.m_disjoint_sets.size(); ++i) {

            ll sum = std::accumulate(solution.m_disjoint_sets[i].begin(), solution.m_disjoint_sets[i].end(), 0);
            os << "Suma conjunto " << i + 1 << ": " << sum << std::endl;
        }

        return os;
    }
};

/*
 * Calcula el costo de una solución, utilizando diferencias de cuadrados.
 */
double solution_evaluator(SolutionSA solution) {
    ll sum1 = std::accumulate(solution.m_disjoint_sets[0].begin(), solution.m_disjoint_sets[0].end(), 0);
    ll sum2 = std::accumulate(solution.m_disjoint_sets[1].begin(), solution.m_disjoint_sets[1].end(), 0);
    ll sum3 = std::accumulate(solution.m_disjoint_sets[2].begin(), solution.m_disjoint_sets[2].end(), 0);

    return pow(sum1 - sum2, 2) + pow(sum1 - sum3, 2) + pow(sum2 - sum3, 2);
}

std::vector<SolutionSA> get_neighborhood(SolutionSA solution) {
    std::vector<SolutionSA> neighbors;

    for (int i = 0; i < SolutionSA::ALTERNATE_SOLUTIONS; ++i) {
        disjoint_sets_t new_sets = solution.m_disjoint_sets;

        std::random_device rd;
        std::mt19937 generator(rd());

        std::uniform_int_distribution<> unif_set(0, 2);

        for (int i = 0; i < SolutionSA::NUMBERS_TO_TAKE; ++i) {
            int set_to_take = unif_set(generator);
            int set_to_move = unif_set(generator);

            int length = new_sets[set_to_take].size();

            if (length == 0)
                continue;

            if (set_to_take == set_to_move)
                continue;

            std::uniform_int_distribution<> unif_number(0, length - 1);
            int number_to_take = unif_number(generator);

            ll number_taken = new_sets[set_to_take][number_to_take];
            new_sets[set_to_take].erase(new_sets[set_to_take].begin() + number_to_take);
            new_sets[set_to_move].push_back(number_taken);
        }

        neighbors.push_back(SolutionSA(new_sets));
    }

    return neighbors;
}
