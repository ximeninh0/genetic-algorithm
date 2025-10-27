#include "Entities/Individual.h"
#include "Genetics/Mutation.h"
#include "Tools/Tools.h"


Mutation::Mutation(float mutat_rate){
    this->mutation_rate = mutat_rate;
}

void Mutation::mutate_individual(Individual &individual){
    Tools tools;    
    int chrom_size = individual.get_chromossome().size();
    int random_first_index = tools.random_number(1,chrom_size - 1);
    int random_second_index;

    do{
        random_second_index = tools.random_number(1,chrom_size - 1);
    } while(random_second_index == random_first_index);

    Gene temp = individual.get_chromossome()[random_first_index];
    individual.get_chromossome()[random_first_index] = individual.get_chromossome()[random_second_index];
    individual.get_chromossome()[random_second_index] = temp;

}