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
    int option, tam_elite,tx_mut_indv,tx_mut_gene,size_p,epochs;
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
        // 360 dividido pela quantidade de pontos x^2 + y^2 = r^2 | 2piR
        case 2: break;
    }
    
    for (Gene city : cities)
    city.print_gene();
    
    // cout << "Insira o Tamanho da Elite " << endl;
    // cin >> tam_elite ;
    
    // cout << "Insira o Tamanho da População " << endl;
    // cin >> size_p ;

    // cout << "Insira a Qtd Epócas " << endl;
    // cin >> epochs ;

    // cout << "Insira a taxa de mutação do indivíduo: " << endl;
    // cin >> tx_mut_indv ;
    
    // cout << "Insira a taxa de mutação do gene: " << endl;
    // cin >> tx_mut_gene ;
    tam_elite = 15;
    size_p = 50;
    epochs = 30;
    tx_mut_indv = 70;
    tx_mut_gene = 60;

    
    Population population(cities[0],cities,size_p,tam_elite);
    GeneticAlgorithm genetic(tam_elite,tx_mut_indv,tx_mut_gene);
    solution = genetic.RunGeneticAlgorithim(population,epochs);
    std::vector<std::pair<float,float>> pairs = tools.individual_to_tuple_array(solution.get_chromossome(), solution.get_first_gene());
    cout << "tuplas: " << endl;
    for (const auto& p : pairs) {
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }    
    tools.save_generation(population.get_generation(), solution.get_fitness(),pairs,solution.get_chromossome(),solution.get_first_gene());
    cout << "Custo Solução: " << solution.get_fitness();
    return 0;
}