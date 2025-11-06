#include <map>
#include <array>
#include <string>
#include <vector>
#include <functional>
#include <cstring>
#include <iostream>
#include "Entities/Individual.h"
#include "Entities/Gene.h"
#include "Tools/Tools.h"
using namespace std;

Individual::Individual(){}


// Construtor Padrão
Individual::Individual(vector<Gene> new_chromossome, int index, int generation, Gene first_route_city)
{
    this->chromossome = new_chromossome;
    this->index = index;
    this->generation = generation;
    this->first_city = first_route_city;
    this->fitness_is_dirty = true;
}

Individual::~Individual(){
}
// Muda o cromossomo para um novo
void Individual::changeDNA(vector<Gene> &new_chrome){
    this->chromossome = new_chrome;

    this->fitness_is_dirty = true;
}

// Retorna a qualidade do indivíduo
int Individual::get_fitness() const
{

    if (!this->fitness_is_dirty)
    {
        return this->cache_fitness;
    }
    

    // Se o cromossomo estiver vazio (ex: n=1 cidade), a rota é A->A.
    // O fitness (distância) é 0.
    if (chromossome.empty())
    {
        return 0;
    }

    int fitness = 0;
    Tools tools;

    fitness -= tools.weight(this->first_city.get_point(), chromossome[0].get_point());

    for (size_t i = 0; i < chromossome.size() - 1; i++)
    {
        fitness -= tools.weight(chromossome[i].get_point(), chromossome[i + 1].get_point());
    }

    fitness -= tools.weight(chromossome.back().get_point(), this->first_city.get_point());

    this->cache_fitness = fitness;
    this->fitness_is_dirty = false;

    return fitness;
}

// Remove um gene pelo nome
void Individual::remove_gene_by_name(char gene_name)
{
    for (size_t i = 0; i < chromossome.size(); i++)
    {
        if (chromossome[i].get_name() == gene_name)
            chromossome.erase(chromossome.begin() + i);
    }
}

// Adiciona um novo Gene ao cromossomo
void Individual::add_gene(Gene new_gene) { chromossome.push_back(new_gene); }


// Getters e Setters
int Individual::get_index() { return index; }
void Individual::set_index(char new_index) { index = new_index; }

int Individual::get_generation() { return generation; }
void Individual::set_generation(char new_generation) { generation = new_generation; }

vector<Gene> Individual::get_chromossome(){return this->chromossome;}
vector<Gene>& Individual::get_chromossome_ref(){return this->chromossome;}

void Individual::set_chromossome(vector<Gene> chrom){this->chromossome = chrom;}

Gene Individual::get_first_gene(){return first_city;}
void Individual::set_first_gene(Gene gene){this->first_city = gene;}

// Prints
void Individual::print_individual()
{
    cout << 'I' << generation << '_' << index;
    
    if(index >= 10) cout << "| ";
    else cout << " | ";

    cout << get_first_gene().get_name() << " | ";
    for (Gene &gene : chromossome)
    {
        cout << gene.get_name() << " | ";
    }    
    cout << get_first_gene().get_name() << " |";
    cout << " Fit: " << get_fitness();
    cout << endl;
}    

bool Individual::operator>(const Individual& other) const
{

    return this->get_fitness() > other.get_fitness();
}

void Individual::set_dirty_fitness()
{
    this->fitness_is_dirty = true;
}