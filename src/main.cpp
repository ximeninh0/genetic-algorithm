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


    cin >> option;
    switch (option)
    {
    case 1:
        cities = tools.PopulateCitiesWithRandomPoints(cities);
        break;
        // 360 dividido pela quantidade de pontos
    case 2: break;
    }
    for (Gene city : cities)
        city.print_gene();
    Population population(cities[0], cities, cities.size());
    population.print_population();
    genetic.RunGeneticAlgorithim(population,5);


}