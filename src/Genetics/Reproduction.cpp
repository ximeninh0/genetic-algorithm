#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <ctime>
#include <queue>
#include <experimental/random>
#include <random>
#include <experimental/random>
#include "Entities/Population.h"
#include "Genetics/Reproduction.h"
#include "Entities/Individual.h"
#include "Tools/Tools.h"
using namespace std;

// Construtor principal
Reproduction::Reproduction(int elite_size)
{
    this->new_indv_index = 1;
    this->generation_index = 1;
    this->elite_size = elite_size;
}

// Realiza a reprodução da população passada por rerefência
Population Reproduction::reproduct_population(Population &population)
{
    this->generation_index++;
    Population updated_population(population.get_size(), population.get_generation() + 1, population.get_elitism_size());
    vector<Individual> new_population_individuals;

    // Adiciona os indivíduos da elite
    for (int i = 0; i < updated_population.get_elitism_size(); i++)
    {
        new_population_individuals.push_back(population.get_individuals()[i]);
    }

    int reproductions_amount = updated_population.get_size() - updated_population.get_elitism_size();
    for (int i = 0; i < reproductions_amount; i++)
    {
        bool make_two = false;

        vector<Individual> selected_couple;
        this->roulette_method(population, selected_couple);

        if ((updated_population.get_size() - new_population_individuals.size()) > 1)
            make_two = true;

        vector<Individual> childrens;
        this->reproduct(selected_couple[0], selected_couple[1], make_two, childrens);

        if (make_two)
        {
            new_population_individuals.push_back(childrens[0]);
            new_population_individuals.push_back(childrens[1]);
        }
        else
            new_population_individuals.push_back(childrens[0]);

        if (make_two)
            this->new_indv_index += 2;
        else
            this->new_indv_index++;
    }
    // this->add_children_to_pop(population, childs);
    this->new_indv_index = 1; 
    population.clear_population();
    updated_population.set_individuals(new_population_individuals);
    new_population_individuals.clear();
    return updated_population;
}

// Método da roleta, escolhe indivíduos para reproduzir e tem mais chance de escolher indivíduos de melhor qualidade
void Reproduction::roulette_method(Population &population, vector<Individual> &out_couple)
{
    vector<Individual> individuals = population.get_individuals();
    vector<float> roulette;
    int total_fitness = 0;
    for (Individual &indv : individuals)
        total_fitness += indv.get_fitness() * (-1);
    for (Individual &indv : individuals)
    {
        float indv_fit = indv.get_fitness() * (-1);
        float indv_slice = (float)indv_fit / (float)total_fitness;
        roulette.push_back(indv_slice);
    }

    Individual individual_1 = individual_giveaway(individuals,roulette,total_fitness);
    roulette.clear();
    total_fitness = 0;
    for (Individual &indv : individuals)
        total_fitness += indv.get_fitness() * (-1);
    for (Individual &indv : individuals)
    {
        float indv_fit = indv.get_fitness() * (-1);
        float indv_slice = (float)indv_fit / (float)total_fitness;
        roulette.push_back(indv_slice);
    }

    Individual individual_2 = individual_giveaway(individuals, roullet2, total_fitness);

    vector<Individual> elected_individuals;
    elected_individuals.push_back(individual_1);
    elected_individuals.push_back(individual_2);
    return elected_individuals;
}

// Sorteia um indivíduo levando em conta sua fatia na roleta
Individual Reproduction::individual_giveaway(vector<Individual> &individuals, vector<float> &roulette, int &total_fit)
{
    Tools tools;
    int acc = 0;
    int slice_giveway = tools.random_number(1, total_fit);

    for (int i = 0; i < (roulette.size()); i++)
    {
        float gene_range = roulette[i] * total_fit;
        acc += gene_range;
        if (slice_giveway <= acc)
        {
            Individual selected = individuals[i];
            individuals.erase(individuals.begin() + i);
            roulette.erase(roulette.begin() + i);
            total_fit -= gene_range;

            return selected;
        }
    }
    return individuals.back();
}

// Adiciona os filhos para uma população, utilizada ao fim do algorimto de reprodução
void Reproduction::add_children_to_pop(Population &population, vector<Individual> &children)
{
    for (Individual &child : children)
        population.add_individual(child);
}

// Lógica da reprodução, pega características do individuo 1 e mescla com as do indivíduo 2 gerando 1 ou 2 filhos a partir do filamento genético
void Reproduction::reproduct(Individual &individual_1, Individual &individual_2, bool two_children, vector<Individual> &out_childrens)
{

    Tools tools;
    int chrom_size = individual_1.get_chromossome().size();

    // *** FIX: Adicionar um guarda ***
    // Crossover não é possível se houver menos de 3 genes (max_index < 2)
    if (chrom_size < 3)
    {
        vector<Individual> childrens;
        childrens.push_back(individual_1); // Apenas retorna o pai 1
        if (two_children)
        {
            childrens.push_back(individual_2); // E o pai 2
        }
        return childrens;
    }

    int max_index = chrom_size - 1;
    // Agora 'max_index - 1' é no mínimo 1 (pois max_index >= 2)
    int random_index = tools.random_number(1, max_index - 1);

    vector<Gene> f_children_chromossome, s_children_chromossome; //----- chromossomos dos filhos
    queue<Gene> first_slice;                                     //----------------------------------------- primeira fatia recortada do cromossomo de 1
    queue<Gene> second_slice;                                    //---------------------------------------- segunda fatia recortada do cromossomo de 1
    queue<Gene> aux_queue;                                       //------------------------------------------- fila auxiliar para formar o cromossomo filho

    // Popula as fatias com base no corte aleatório
    for (int i = 0; i <= max_index; i++)
    {
        if (i <= random_index)
            first_slice.push(individual_1.get_chromossome()[i]);
        else
            second_slice.push(individual_1.get_chromossome()[i]);
    }

    // Popula a fila auxiliar em ordem levando em conta genes que NÃO estão na fatia
    for (int i = 0; i <= max_index; i++)
    {
        Gene gene = individual_2.get_chromossome()[i];
        if (!is_gene_in_chrom(gene, first_slice))
        {
            aux_queue.push(gene);
        }
    }

    // Forma o cromossomo filho, inserindo primeiro a fatia recortada e depois a fila auxiliar com os genes ordenados
    for (int i = 0; i <= max_index; i++)
    {
        Gene gene;
        if (!first_slice.empty())
        {
            gene = first_slice.front();
            first_slice.pop();
        }
        else
        {
            gene = aux_queue.front();
            aux_queue.pop();
        }
        f_children_chromossome.push_back(gene);
    }
    
    // Insere o primeiro filho no vetor de retorno 
    Individual first_child(f_children_chromossome,this->new_indv_index,
                           individual_1.get_generation()+1,
                           individual_1.get_first_gene()
                        );

    out_childrens.push_back(first_child);

    while (!aux_queue.empty()) aux_queue.pop();
    
    if(two_children){
        // Caso contrário repete o mesmo processo levando em conta a segunda fatia recortada para formar o segundo filho
        for (int i = 0; i <= max_index; i++)
        {
            Gene gene = individual_2.get_chromossome()[i];
            if (!is_gene_in_chrom(gene, second_slice))
            {
                aux_queue.push(gene);
            }
        }
        for (int i = 0; i <= max_index; i++)
        {
            Gene gene;
            if (!second_slice.empty())
            {
                gene = second_slice.front();
                second_slice.pop();
            }
            else
            {
                gene = aux_queue.front();
                aux_queue.pop();
            }
            s_children_chromossome.push_back(gene);
        }

        // Insere o segundo filho ao vetor resposta e retorna
        Individual second_child(s_children_chromossome,this->new_indv_index + 1,
                                individual_2.get_generation()+1, 
                                individual_2.get_first_gene()
                                );
        out_childrens.push_back(second_child);
    }
}

// Retorna verdade se o Gene estiver presente no cromossomo(fila)
bool Reproduction::is_gene_in_chrom(Gene &gene, queue<Gene> chromossome)
{
    while (!chromossome.empty())
    {
        if (chromossome.front().get_name() == gene.get_name())
            return true;
        else
            chromossome.pop();
    }
    return false;
}

// Função do pedro :D
Population Reproduction::getBestHalf(Population &population)
{
    int half_size = population.get_size() / 2;
    vector<Individual> vetor_ind = population.get_individuals();

    Population new_population;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < half_size; i++)
    {

        if (vetor_ind.size() < 2)
        {
            if (!vetor_ind.empty())
            {
                new_population.add_individual(vetor_ind[0]);
            }
            break;
        }

        std::uniform_int_distribution<> dist1(0, vetor_ind.size() - 1);
        int ind1_index = dist1(gen);
        Individual ind1 = vetor_ind[ind1_index];
        vetor_ind.erase(vetor_ind.begin() + ind1_index);

        std::uniform_int_distribution<> dist2(0, vetor_ind.size() - 1);
        int ind2_index = dist2(gen);
        Individual ind2 = vetor_ind[ind2_index];
        vetor_ind.erase(vetor_ind.begin() + ind2_index);

        if (ind1.get_fitness() < ind2.get_fitness())
        {
            new_population.add_individual(ind1);
        }
        else if (ind2.get_fitness() < ind1.get_fitness())
        {
            new_population.add_individual(ind2);
        }
        else
        {
            new_population.add_individual(ind1);
        }
    }

    return new_population;
}
