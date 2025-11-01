#include "Entities/Individual.h"
#include "Genetics/Mutation.h"
#include "Tools/Tools.h"


Mutation::Mutation(float mutat_i_rate, float mutat_g_rate){
    this->mutation_gene_rate = mutat_g_rate;
    this->mutation_indv_rate = mutat_i_rate;

}

// Realiza a mutação nos indivíduos que foram selecionados para mutar (aleatóriamente), de acordo com a taxa de mutação de indivíduos
Population Mutation::mutate_population(Population &population){

    Tools tools;
    vector<Individual> indvs_from_population = population.get_individuals();
    Population updated_population(population.get_size(), population.get_generation(),population.get_elitism_size());
    int mutations_amount = (this->mutation_indv_rate  / 100) * population.get_size();

    for(int i = 0; i < population.get_size(); i++){
        int random_index = tools.random_number(population.get_elitism_size() - 2, population.get_size());
        this->mutate_individual(indvs_from_population[random_index]);
    }
    population.clear_population();
    updated_population.set_individuals(indvs_from_population);
    return updated_population;
}

// Mutação do indivíduo com base na taxa de mutação dos genes, realiza a seleção dos genes de acordo com a taxa e aleatóriamente
void Mutation::mutate_individual(Individual &individual){
    Tools tools;
    vector<Gene> chromossome = individual.get_chromossome();

    int chrom_size = individual.get_chromossome().size();
    for(int i = 0; i < chrom_size; i++){
        int probability = tools.random_number(1,100);
        if(probability <= this->mutation_gene_rate){
            int random_second_index;
            do{
                random_second_index = tools.random_number(1,chrom_size - 1);
            } while(random_second_index == i);
            Gene temp = chromossome[i];
            chromossome[i] = chromossome[random_second_index];
            chromossome[random_second_index] = temp;

            // cout << "Mutacao!" 
            // << individual.get_chromossome()[i].get_name() 
            // << individual.get_chromossome()[random_second_index].get_name() 
            // << endl;
        }
    }
    individual.changeDNA(chromossome);
    // cout << "RESULTADO! " << endl;
    // individual.print_individual();
}