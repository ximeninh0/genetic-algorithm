#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <ctime>
#include <experimental/random>
#include <random>
#include <experimental/random>
#include "Entities/Population.h"
#include "Genetics/Reproduction.h"
#include "Entities/Individual.h"

using namespace std;


void Reproduction::reproduct_population(Population population)
{
    this->roulette_method(population);
}

void Reproduction::roulette_method(Population population)
{
    vector<Individual> individuals = population.get_individuals();
    vector<float> roulette;
    int total_fitness = 0;
    for (Individual indv : population.get_individuals()) total_fitness += indv.get_fitness();
    for (Individual indv : population.get_individuals()) {
        float indv_fit = indv.get_fitness();
        float indv_slice = (float)indv_fit / (float)total_fitness;
        roulette.push_back(indv_slice);
    }

    for(Individual indv : individuals) 
        indv.print_individual();

    Individual individual_1 = gene_giveaway(individuals,roulette,total_fitness);
    Individual individual_2 = gene_giveaway(individuals,roulette,total_fitness);

    for(Individual indv : individuals) 
        indv.print_individual();

}

Individual Reproduction::gene_giveaway(vector<Individual> individuals, vector<float> roulette, int total_fit)
{
    int acc = 0;
    int slice_giveway = std::experimental::randint(1,total_fit);
    for (int i = 0; i < (roulette.size() - 1); i++) {
        float gene_range = roulette[i] * total_fit;
        acc += gene_range;

        if(slice_giveway <= acc) {
            Individual selected = individuals[i];
            individuals.erase(individuals.begin() + i);
            roulette.erase(roulette.begin() + i);

            return selected;
        }
    }

}
