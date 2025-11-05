#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <ctime>
#include <experimental/random>
#include <random>
#include <algorithm>
#include <fstream>

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

Individual GeneticAlgorithm::RunGeneticAlgorithim(Population &population, int epochs, int tournament_size)
{
    // Inicialização dos objetos de mutação e reprodução, os valores passados no construtor são as taxas
    Reproduction reproducion_tools(this->elite_size, tournament_size);
    Mutation mutation_tools(this->mutation_indv_tx,this->mutation_gene_tx);
    Tools tools;

    std::ofstream history("history.csv");
    if (!history.is_open()) {
        std::cerr << "Erro ao abrir arquivo de histórico.\n";
    }

    history << "generation,best,average,worst,route\n";

    for(int i = 0; i < epochs-1; i++){
        // cout << "----------GERACAO--------------------------------" << i << endl;
        // cout << "----------ANTES DA REPRODUCAO----------" << endl;
        population.sort_individuals();
        // population.print_population();

        population = reproducion_tools.reproduct_population(population);     // Realiza a reprodução com base na taxa de reprodução e na qtd de filhos

        // cout << "----------ANTES DA MUTACAO----------" << endl;
        // population.print_population();

        population = mutation_tools.mutate_population(population);           // Realiza a mutação com base na taxa de mutacão por indivíduo e por gene estipulada
        
        // cout << "----------DEPOIS DA MUTACAO----------" << endl;
        // population.print_population();
        
        // population.sort_individuals();                          // Ordena os indivíduos com base na qualidade
        
        // cout << "----------DEPOIS DO SORT----------" << endl;
        // population.print_population();
        
        while(population.get_individuals().size() > population.get_size())  // Realiza o ajuste populacional deixando apenas os de melhor qualidade
            population.pop_indv();
        
        // cout << "----------DEPOIS DA ANIQUILAÇÃO----------" << endl;
        // population.set_generation(population.get_generation() + 1);
        // cout << i << endl;



        
        // // criar filhos
        
        // Population offspring = reproducion_tools.create_offspring(population);
        
        // // muta filhos
        
        // offspring = mutation_tools.mutate_population(population);
        
        // // combina filhos
        
        // population.combine(offspring);
        
        // // mata, trunca os filhos
        
        // population.truncate();
        
        // // atualiza geracao
        
        
        int best = population.get_best_fit();
        float avg = population.get_average_fit();
        int worst = population.get_worst_fit();
        std::vector<std::pair<float, float>> best_solution = tools.individual_to_tuple_array(
            population.get_individuals_ref()[0].get_chromossome_ref(), 
            population.get_individuals_ref()[0].get_first_gene()
        );

        history << population.get_generation() << "," << best << "," << avg << "," << worst << "," 
        << population.get_individuals_ref()[0].get_first_gene().get_name(); 
        for (Gene& g : population.get_individuals_ref()[0].get_chromossome_ref()) history << g.get_name();
        history << population.get_individuals_ref()[0].get_first_gene().get_name(); 
        history << "\n";
        history.flush();
    }
    history.close();

    population.sort_individuals();
    cout << "----------Ultima populacao----------" << endl;

    population.print_population();
    return population.get_individuals()[0];
}

