#pragma once
#include "Entities/Individual.h"
#include "Entities/Population.h"

class Mutation
{
private:
    float mutation_indv_rate;
    float mutation_gene_rate;
public:
    Mutation(float mutat_i_rate, float mutat_g_rate);
    void mutate_population(Population &population);
    void mutate_individual(Individual &individual);

};
