#pragma once

#include "Entities/Gene.h"
#include "Tools/Tools.h"
#include <iostream>
#include <iomanip>
#include <vector>

class Individual
{
private:
    int index;
    int generation;
    vector<Gene> chromossome;
    Gene first_city;

public:
    Individual();
    Individual(vector<Gene> new_chromossome, int index, int generation, Gene first_route_city);
    void print_individual();
    int get_index();
    void set_index(char new_index);
    int get_generation();
    vector<Gene> get_chromossome();
    void changeDNA(vector<Gene> &new_chrome);
    void set_generation(char new_generation);
    void add_gene(Gene new_gene);
    void remove_gene_by_name(char gene_name);
    int get_fitness();
    Gene get_first_gene();
};