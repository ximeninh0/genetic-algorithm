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

// Construtor Padrão
Individual::Individual(vector<Gene> new_chromossome, int index, int generation, Gene first_route_city)
{
    this->chromossome = new_chromossome;
    this->index = index;
    this->generation = generation;
    this->first_city = first_route_city;
}

// Muda o cromossomo para um novo
void Individual::changeDNA(vector<Gene> &new_chrome){
    this->chromossome = new_chrome;
}

// Retorna a qualidade do indivíduo
int Individual::get_fitness()
{
    int fitness = 0;
    Tools tools;
    for (int i = 0; i < chromossome.size() - 1; i++)
    {
        if (i != 0 && i != (chromossome.size() - 1))
            fitness -= tools.weight(chromossome[i].get_point(), chromossome[i + 1].get_point());
        else if (i == 0)
            fitness -= tools.weight(this->first_city.get_point(), chromossome[i].get_point());
            else    
            fitness -= tools.weight(chromossome[i].get_point(), this->first_city.get_point());
        }        
    return fitness;
}

// Remove um gene pelo nome
void Individual::remove_gene_by_name(char gene_name)
{
    for (int i = 0; i < chromossome.size(); i++)
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

Gene Individual::get_first_gene(){return first_city;}

// Prints
void Individual::print_individual()
{
    cout << 'I' << generation << '_' << index;
    
    if(index >= 10) cout << "| ";
    else cout << " | ";

    cout << get_first_gene().get_name() << " | ";
    for (Gene gene : chromossome)
    {
        cout << gene.get_name() << " | ";
    }    
    cout << get_first_gene().get_name() << " |";
    cout << " Fit: " << get_fitness();
    cout << endl;
}    
