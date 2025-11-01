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
    Population mutate_population(Population &population);
    void mutate_indv_by_rand_indx(Individual &individual);
    void mutate_indv_by_inverse(Individual &individual);
    int twins_score(Population &population);
};
