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

using namespace std;

// g++ -Iinclude src/main.cpp src/Entities/*.cpp src/Tools/*.cpp -o main



// class GeneticEstrategy
// {
// private:
//     Reproduction reproducion_tools;
//     Mutation mutation_tools;
//     PopulationAdjust pop_adj_tools;

// public:
//     Individual ApplyGeneticAlgorithim(Population population, int epochs)
//     {
//         Individual solution;

//         for (int i = 0; i < epochs; i++)
//         {
//             reproducion_tools.reproduction_logic(Population population);
//         }

//         return solution;
//     }

//     // vector<float> GenerateRouletteArray(Population population){
//     //     // for()
//     // }
// };

// class Reproduction
// {
// private:
// public:
//     void reproduction_logic()
//     {
//     }
// };

// class Mutation
// {
// private:
// public:
// };

// class PopulationAdjust
// {
// private:
// public:
// };



int main()
{
    int option;
    vector<Gene> cities;
    vector<Gene> solution;
    Tools tools;
    tools.header();

    // do
    // {
    cin >> option;
    switch (option)
    {
    case 1:
        cities = tools.PopulateCitiesWithRandomPoints(cities);
        break;
        // 360 divido pela quantidade de pontos
    case 2:
        for (Gene city : cities)
            city.print_gene();
        break;
    }
    Population population(cities[0], cities, 10);
    population.print_population();
    population = tools.getBestHalf(population);
    population.print_population();
    // population.get
    // } while (option != 3);
}