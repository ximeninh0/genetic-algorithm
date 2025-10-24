#include "Entities/Population.h"
#include "Entities/Gene.h"
class Reproduction
{
private:
public:
    void reproduct_population(Population population);
    void roulette_method(Population population);
    Individual gene_giveaway(vector<Individual> individuals, vector<float> roulette, int total_fit);

};