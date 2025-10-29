#pragma once

#include <vector>
#include <queue>
#include "Entities/Population.h"
#include "Entities/Gene.h"
class Reproduction
{
private:
    float reproduction_rate;
    int new_indv_index;
    int generation_index;
    bool two_children;
    
public:
    Reproduction(float reprod_rate, bool two_children);
    void reproduct_population(Population &population);
    vector<Individual> roulette_method(Population population);
    Individual individual_giveaway(vector<Individual> &individuals, vector<float> &roulette, int &total_fit);
    vector<Individual> reproduct(Individual individual_1, Individual individual_2, bool two_children);
    bool is_gene_in_chrom(Gene gene, queue<Gene> chromossome);
    void add_children_to_pop(Population &population, vector<Individual> children);
    Population getBestHalf(Population &population);
    void compare_couple_with_children(Population &population, vector<Individual> children, vector<Individual> couple);
    void sort_and_anihilate(Population &population);
};