#pragma once


#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <ctime>
#include <experimental/random>
#include <random>
#include <algorithm>
#include "Entities/Gene.h" 
#include "Entities/Individual.h"
#include "Entities/Point.h"
#include "Entities/Population.h"
#include "Tools/Tools.h"
#include "Genetics/Reproduction.h"
#include "Genetics/Mutation.h"

using namespace std;


class GeneticAlgorithm
{
private:
    int reproducion_tx;
    int mutation_indv_tx;
    int mutation_gene_tx;

public:
    GeneticAlgorithm(int tx_reprod, int tx_mut_indv, int tx_mut_gene);
    Individual RunGeneticAlgorithim(Population &population, int epochs);

};