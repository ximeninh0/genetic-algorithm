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
#include "Genetics/GeneticAlgorithm.h"

using namespace std;

GeneticAlgorithm::GeneticAlgorithm(){}

void GeneticAlgorithm::RunGeneticAlgorithim(Population population, int epochs)
{
    Reproduction reproducion_tools(100);
    Mutation mutation_tools(5,50);
    cout << "----------ANTES DA REPRODUCAO----------" << endl;
    population.print_population();

    reproducion_tools.reproduct_population(population);

    cout << "----------DEPOIS DA REPRODUCAO----------" << endl;
    population.print_population();

    cout << "----------ANTES DA MUTACAO----------" << endl;
    population.print_population();

    mutation_tools.mutate_population(population);

    cout << "----------DEPOIS DA MUTACAO----------" << endl;
    population.print_population();
    
    cout << "----------DEPOIS DO SORT----------" << endl;
    population.sort_individuals();
    population.print_population();
    
    while(population.get_individuals().size() > population.get_size())
        population.pop_indv();
        
    cout << "----------DEPOIS DA ANIQUILAÇÃO----------" << endl;
    population.print_population();
    // cout << "depois" << endl;
    // population.print_population();
    // return solution;
}

