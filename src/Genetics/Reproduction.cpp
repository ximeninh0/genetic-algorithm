#include "Entities/Population.h"
#include "Genetics/Reproduction.h"
#include "Entities/Individual.h"

void Reproduction::reproduct_population(Population population)
{
    this->roulette_method(population);
}

void Reproduction::roulette_method(Population population)
{
    vector<float> roulette;
    float total_fitness = 0;
    for (Individual indv : population.get_individuals()) total_fitness += indv.get_fitness();
    for (Individual indv : population.get_individuals()) {
        float indv_fit = indv.get_fitness();
        float indv_slice = indv_fit / total_fitness;
        roulette.push_back(indv_slice);

    }
}
