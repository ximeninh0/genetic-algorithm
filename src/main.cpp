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
    int option, tam_elite, tx_mut_indv, tx_mut_gene, size_p, epochs, tournament_size;
    vector<Gene> cities;
    Individual solution;
    Tools tools;
    tools.header();
    
    cin >> option;
    switch (option)
    {
        case 1:
        cities = tools.PopulateCitiesWithRandomPoints();
        break;
        case 2:
        cities = tools.PopulateCitiesinCircle();
        break;
    }
    
    cout << "Cidades: " << endl;

    for (Gene city : cities)
    city.print_gene();
    
    cout << "Insira o Tamanho da População " << endl;
    cin >> size_p ;

    do {
        cout << "Insira o Tamanho da Elite (deve ser menor que " << size_p << ")" << endl;
        cin >> tam_elite ;
    } while (tam_elite >= size_p); // Força tam_elite a ser menor que size_p

    cout << "Insira a Qtd Epócas " << endl;
    cin >> epochs ;

    cout << "Insira a taxa de mutação do indivíduo: " << endl;
    cin >> tx_mut_indv ;
    
    cout << "Insira a taxa de mutação do gene: " << endl;
    cin >> tx_mut_gene ;

    cout << "Insira o tamanho do torneio: " << endl;
    cin >> tournament_size ;


    if (cities.size() == 0) {
        cout << "Nenhuma cidade foi gerada. Encerrando o programa." << endl;
        return 1; // Sai do programa com código de erro
    }
    
    Population population(cities[0],cities,size_p,tam_elite);
    GeneticAlgorithm genetic(tam_elite,tx_mut_indv,tx_mut_gene);
    solution = genetic.RunGeneticAlgorithim(population,epochs, tournament_size);

    cout << "Debug2" << endl;

    std::vector<std::pair<float,float>> pairs = tools.individual_to_tuple_array(solution.get_chromossome(), solution.get_first_gene());
    cout << "tuplas: " << endl;
    for (const auto& p : pairs) {
        std::cout << "(" << p.first << ", " << p.second << ")\n";
    }    
    tools.save_generation(population.get_generation(), solution.get_fitness(),pairs,solution.get_chromossome(),solution.get_first_gene());
    cout << "Custo Solução: " << solution.get_fitness();

    cout << "\n" << endl;
    
    return 0;
}