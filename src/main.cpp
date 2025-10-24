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
#include "Genetics/GeneticAlgorithm.h"

using namespace std;

// g++ -Iinclude src/main.cpp src/Entities/*.cpp src/Tools/*.cpp src/Genetics/*.cpp -o main


int main()
{
    int option;
    vector<Gene> cities;
    vector<Gene> solution;
    GeneticAlgorithm genetic;
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
    genetic.RunGeneticAlgorithim(population,10);
    // population.get
    // } while (option != 3);
}