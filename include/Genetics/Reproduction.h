#pragma once

#include <vector>
#include <queue>
#include "Entities/Population.h"
#include "Entities/Gene.h"
class Reproduction
{
private:
    int new_indv_index;
    int generation_index;
    int elite_size;
    int tournament_size;

public:
    Reproduction(int elite_size, int tournament_size);
    Population reproduct_population(Population &population);
    void roulette_method(Population &population, vector<Individual> &out_couple);
    Individual individual_giveaway(vector<Individual> &individuals, vector<float> &roulette, int &total_fit);
    void reproduct(Individual &individual_1, Individual &individual_2, bool two_children, vector<Individual> &out_childrens);
    bool is_gene_in_chrom(Gene &gene, queue<Gene> chromossome);
    void add_children_to_pop(Population &population, vector<Individual> &children);
    Population getBestHalf(Population &population);
    Individual& tournament_selection(Population &population, int tournament_size);
    void reproduct_crossover_2_points(Individual &individual_1, Individual &individual_2, bool two_children, vector<Individual> &out_childrens);
    Individual gen_child_by_crossover(Individual &individual_1, Individual &individual_2);

};