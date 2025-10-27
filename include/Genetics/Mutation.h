#pragma once
#include "Entities/Individual.h"

class Mutation
{
private:
    float mutation_rate;
public:
    Mutation(float mutat_rate);
    void mutate_individual(Individual &individual);

};
