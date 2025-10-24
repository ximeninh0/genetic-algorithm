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
    Reproduction reproducion_tools;
    Mutation mutation_tools;

public:
    GeneticAlgorithm(){}
    Individual RunGeneticAlgorithim(Population population, int epochs);

};