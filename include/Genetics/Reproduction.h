#pragma once

#include <vector>
#include <queue>
#include "Entities/Population.h"
#include "Entities/Gene.h"
class Reproduction
{
private:
    float reproduction_rate;
public:
    Reproduction(float reprod_rate);
    void reproduct_population(Population population);
    vector<Individual> roulette_method(Population population);
    Individual gene_giveaway(vector<Individual> &individuals, vector<float> &roulette, int &total_fit);
    vector<Individual> reproduct(Individual individual_1, Individual individual_2, bool two_children);
    bool is_gene_in_chrom(Gene gene, queue<Gene> chromossome);
    Population add_children_to_pop(Population population, vector<Individual> children);
    Population getBestHalf(Population &population);

};