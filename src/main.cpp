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
    int option, tx_reprod,tx_mut_indv,tx_mut_gene;
    vector<Gene> cities;
    Individual solution;
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
    
    Population population(cities[0], cities, 100);
    cout << "Insira a taxa de reprodução: " << endl;
    cin >> tx_reprod ;
    
    cout << "Insira a taxa de mutação do indivíduo: " << endl;
    cin >> tx_mut_indv ;
    
    cout << "Insira a taxa de mutação do gene: " << endl;
    cin >> tx_mut_gene ;
    
    GeneticAlgorithm genetic(tx_reprod,tx_mut_indv,tx_mut_gene);
    solution = genetic.RunGeneticAlgorithim(population,100);
    std::vector<std::pair<float,float>> pairs = tools.individual_to_tuple_array(solution.get_chromossome(), solution.get_first_gene());
    cout << "tuplas: " << endl;
    for (const auto& p : pairs) {
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }    
    tools.save_generation(population.get_generation(), solution.get_fitness(),pairs,solution.get_chromossome(),solution.get_first_gene());
    cout << "Custo Solução: " << solution.get_fitness();
    return 0;
}