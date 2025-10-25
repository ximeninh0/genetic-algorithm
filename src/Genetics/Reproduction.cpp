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


void Reproduction::reproduct_population(Population population)
{
    population.print_population();
    vector<Individual> selected_couple = this->roulette_method(population);
    vector<Individual> childrens = this->reproduct(selected_couple[0],selected_couple[1],true);
    Population updated_population = this->add_children_to_pop(population, childrens);
    // for(Individual indv : selected_couple) indv.print_individual();
    updated_population.print_population();

}

vector<Individual> Reproduction::roulette_method(Population population)
{
    vector<Individual> individuals = population.get_individuals();
    vector<float> roulette;
        int total_fitness = 0;
        for (Individual indv : individuals) total_fitness += indv.get_fitness() *(-1);
        for (Individual indv : individuals) {
            float indv_fit = indv.get_fitness() *(-1);
            float indv_slice = (float)indv_fit / (float)total_fitness;
            roulette.push_back(indv_slice);
        }

    Individual individual_1 = gene_giveaway(individuals,roulette,total_fitness);
    vector<float> roullet2;
    total_fitness = 0;
    for (Individual indv : individuals) total_fitness += indv.get_fitness() *(-1);
    for (Individual indv : individuals) {
        float indv_fit = indv.get_fitness() *(-1);
        float indv_slice = (float)indv_fit / (float)total_fitness;
        roullet2.push_back(indv_slice);
    }

    Individual individual_2 = gene_giveaway(individuals,roullet2,total_fitness);

    vector<Individual> elected_individuals;
    elected_individuals.push_back(individual_1);
    elected_individuals.push_back(individual_2);
    return elected_individuals;

}

Individual Reproduction::gene_giveaway(vector<Individual> &individuals, vector<float> &roulette, int &total_fit)
{
    int acc = 0;
    int slice_giveway = std::experimental::randint(1,total_fit);
    for (int i = 0; i < (roulette.size()); i++) {
        float gene_range = roulette[i] * total_fit;
        acc += gene_range;
        if(slice_giveway <= acc) {
            Individual selected = individuals[i];
            individuals.erase(individuals.begin() + i);
            roulette.erase(roulette.begin() + i);
            total_fit -= gene_range;
            
            return selected;
        }
    }
}

Population Reproduction::add_children_to_pop(Population population, vector<Individual> children){
    for (Individual child : children)
        population.add_individual(child);
    return population;
}


vector<Individual> Reproduction::reproduct(Individual individual_1, Individual individual_2, bool two_children)
{
    Tools tools;
    int max_index = individual_1.get_chromossome().size() - 1;
    int random_index = tools.random_number(1,max_index-1);
    cout << random_index << endl;
    // cout << 'm' << max_index << endl;
    cout << "Couple: " << individual_1.get_index() << individual_2.get_index() << endl;
    vector<Gene> f_children_chromossome, s_children_chromossome;
    queue<Gene> first_slice;
    queue<Gene> second_slice;
    queue<Gene> aux_queue;
    
    for(int i = 0; i <= max_index; i++){
        if(i <= random_index) {
            cout << "Pushing_fs: " << individual_1.get_chromossome()[i].get_name() << endl;
            first_slice.push(individual_1.get_chromossome()[i]);
        }
        else second_slice.push(individual_1.get_chromossome()[i]);
    }

    for(int i = 0; i < first_slice.size(); i++){
        // cout << first_slice.back().get_name() << endl;
    }

    for(int i = 0; i <= max_index; i++){
        Gene gene = individual_2.get_chromossome()[i];
        if(!is_gene_in_chrom(gene,first_slice)){
            cout << "Pushing_aux: " << gene.get_name() << endl;
            cout << first_slice.back().get_name() << endl;
            aux_queue.push(gene);
        }
    }

    for(int i = 0; i <= max_index; i++){
        Gene gene;
        if(!first_slice.empty()){
            gene = first_slice.front();
            first_slice.pop();
        }
        else{
            gene = aux_queue.front();
            aux_queue.pop();
        }
        f_children_chromossome.push_back(gene);
    }
    
    vector<Individual> childrens;
    Individual first_child(f_children_chromossome,individual_1.get_index(),individual_1.get_generation()+1,individual_1.get_first_gene());
    childrens.push_back(first_child);

    if(!two_children){
        return childrens;
    }
    else {
        if(aux_queue.empty())
            cout << "vazia" << endl;

        cout << aux_queue.front().get_name() << endl;
        for(int i = 0; i <= max_index; i++){
            Gene gene = individual_2.get_chromossome()[i];
            if(!is_gene_in_chrom(gene,second_slice)){
                aux_queue.push(gene);
            }
        }
        for(int i = 0; i <= max_index; i++){
            Gene gene;
            if(!second_slice.empty()){
                gene = second_slice.front();
                second_slice.pop();
            }
            else{
                gene = aux_queue.front();
                aux_queue.pop();
            }
            s_children_chromossome.push_back(gene);
        }
        Individual second_child(s_children_chromossome,individual_2.get_index(), individual_2.get_generation()+1, individual_2.get_first_gene());
        childrens.push_back(second_child);
        return childrens;
    }
}

bool Reproduction::is_gene_in_chrom(Gene gene, queue<Gene> chromossome)
{
    while(!chromossome.empty()){
        cout << "testando: " << chromossome.front().get_name() << endl;
        if(chromossome.front().get_name() == gene.get_name()){
            cout << "achou: " << chromossome.front().get_name() << endl;
            return true;
        }
        else chromossome.pop();
    }
    return false;
}
