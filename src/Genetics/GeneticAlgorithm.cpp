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

GeneticAlgorithm::GeneticAlgorithm(int elite_size, int tx_mut_indv, int tx_mut_gene){
    this->elite_size = elite_size;
    this->mutation_indv_tx = tx_mut_indv;
    this->mutation_gene_tx = tx_mut_gene;
}

Individual GeneticAlgorithm::RunGeneticAlgorithim(Population &population, int epochs)
{
    // Inicialização dos objetos de mutação e reprodução, os valores passados no construtor são as taxas
    Reproduction reproducion_tools(this->elite_size);
    Mutation mutation_tools(this->mutation_indv_tx,this->mutation_gene_tx);

    for(int i = 0; i < epochs; i++){
        cout << "----------ANTES DA REPRODUCAO----------" << endl;
        population.sort_individuals();
        population.print_population();

        population = reproducion_tools.reproduct_population(population);     // Realiza a reprodução com base na taxa de reprodução e na qtd de filhos

        cout << "----------ANTES DA MUTACAO----------" << endl;
        population.print_population();

        mutation_tools.mutate_population(population);           // Realiza a mutação com base na taxa de mutacão por indivíduo e por gene estipulada

        cout << "----------DEPOIS DA MUTACAO----------" << endl;
        population.print_population();
        
        population.sort_individuals();                          // Ordena os indivíduos com base na qualidade

        // cout << "----------DEPOIS DO SORT----------" << endl;
        // population.print_population();
        
        // while(population.get_individuals().size() > population.get_size())  // Realiza o ajuste populacional deixando apenas os de melhor qualidade
        //     population.pop_indv();

        // cout << "----------DEPOIS DA ANIQUILAÇÃO----------" << endl;
        // population.print_population();
        population.set_generation(population.get_generation() + 1);
    }
    // cout << "depois" << endl;
    // population.print_population();
    return population.get_individuals()[0];
}

