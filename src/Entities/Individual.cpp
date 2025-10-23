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

Individual::Individual(vector<Gene> new_chromossome, int index, int generation, Gene first_route_city)
{
    this->chromossome = new_chromossome;
    this->index = index;
    this->generation = generation;
    this->first_city = first_route_city;
}
void Individual::print_individual()
{
    cout << 'I' << generation << '_' << index << "| ";
    for (Gene gene : chromossome)
    {
        cout << gene.get_name() << " | ";
    }
    cout << endl;
}

int Individual::get_index() { return index; }
void Individual::set_index(char new_index) { index = new_index; }

int Individual::get_generation() { return generation; }
void Individual::set_generation(char new_generation) { generation = new_generation; }

void Individual::add_gene(Gene new_gene) { chromossome.push_back(new_gene); }

void Individual::remove_gene_by_name(char gene_name)
{
    for (int i = 0; i < chromossome.size(); i++)
    {
        if (chromossome[i].get_name() == gene_name)
            chromossome.erase(chromossome.begin() + i);
    }
}

int Individual::get_fitness()
{
    int fitness = 0;
    Tools tools;
    for (int i = 0; i < chromossome.size() - 1; i++)
    {
        if (i != 0 && i != (chromossome.size() - 1))
            tools.weight(chromossome[i].get_point(), chromossome[i + 1].get_point());
        else if (i == 0)
            tools.weight(this->first_city.get_point(), chromossome[i].get_point());
        else
            tools.weight(chromossome[i].get_point(), this->first_city.get_point());
    }
    return fitness;
}