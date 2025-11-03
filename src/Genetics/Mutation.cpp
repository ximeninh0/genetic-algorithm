#include "Entities/Individual.h"
#include "Genetics/Mutation.h"
#include "Tools/Tools.h"

Mutation::Mutation(float mutat_i_rate, float mutat_g_rate)
{
    this->mutation_gene_rate = mutat_g_rate;
    this->mutation_indv_rate = mutat_i_rate;
}

// Realiza a mutação nos indivíduos que foram selecionados para mutar (aleatóriamente), de acordo com a taxa de mutação de indivíduos
Population Mutation::mutate_population(Population &population)
{

    Tools tools;

    vector<Individual>& indvs_from_population = population.get_individuals_ref();

    int p_size = population.get_size();
    int elite_size = population.get_elitism_size();

    for (int i = 0; i < p_size; i++)
    {
        int probability = tools.random_number(1, 100);

        if (probability <= this->mutation_indv_rate)
        {
            this->mutate_indv_by_inverse(indvs_from_population[i]);
        }
    }

    return population;
}

// Mutação do indivíduo com base na taxa de mutação dos genes, realiza a seleção dos genes de acordo com a taxa e aleatóriamente
// Em Mutation.cpp
void Mutation::mutate_indv_by_rand_indx(Individual &individual)
{
    Tools tools;
    vector<Gene> chromossome = individual.get_chromossome();
    int chrom_size = individual.get_chromossome().size();

    // *** FIX 1: Adicionar um guarda ***
    // Mutação não é possível se houver menos de 2 genes para trocar
    if (chrom_size < 2)
    {
        return;
    }

    for (int i = 0; i < chrom_size; i++)
    {
        int probability = tools.random_number(1, 100);
        if (probability <= this->mutation_gene_rate)
        {
            int random_second_index;
            do
            {
                // *** FIX 2: Corrigir o intervalo ***
                random_second_index = tools.random_number(0, chrom_size - 1);
            } while (random_second_index == i); // O loop do-while agora está seguro

            Gene temp = chromossome[i];
            chromossome[i] = chromossome[random_second_index];
            chromossome[random_second_index] = temp;
        }
    }
    individual.changeDNA(chromossome);
}

void Mutation::mutate_indv_by_inverse(Individual &individual)
{
    // vector<Gene> &chromossome = individual.get_chromossome_ref();
    // vector<Gene> new_chromossome;

    // for (int i = chromossome.size() - 1; i >= 0; i--)
    // {
    //     new_chromossome.push_back(chromossome[i]);
    // }

    // individual.changeDNA(new_chromossome);

    Tools tools;

    vector<Gene> &chromossome = individual.get_chromossome_ref();

    int c_size = chromossome.size();

    if (c_size < 2)
        return;

    int pos1;
    int pos2;
    do
    {
        pos1 = tools.random_number(0, c_size - 1);
        pos2 = tools.random_number(0, c_size - 1);
    } while (pos1 == pos2);

    if (pos1 > pos2)
        swap(pos1, pos2);

    reverse(chromossome.begin() + pos1, chromossome.begin() + pos2 + 1);
}

int Mutation::twins_score(Population &population)
{
    int twins_count = 0;
    int best_fit = population.get_individuals_ref()[0].get_fitness();
    for (int i = 1; i < population.get_elitism_size(); i++)
        if (population.get_individuals_ref()[i].get_fitness() == best_fit)
            twins_count++;

    return twins_count;
}
