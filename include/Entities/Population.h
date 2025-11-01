#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <ctime>
#include <experimental/random>
#include <random>
#include <algorithm>
#include "Entities/Point.h"
#include "Entities/Gene.h"
#include "Entities/Individual.h"

using namespace std;

class Population
{
private:
    int generation;
    int size_p;
    int elitism_size;
    vector<Individual> individuals;

public:
    Population();
    ~Population();

    Population(Gene first_route_city, vector<Gene> cities, int size_p, int elitsm_size);
    Population(int size_p, int generation, int elitism_size);
    void print_population();
    int get_generation();
    void set_generation(int new_generation);
    
    int get_elitism_size();
    void set_elitism_size(int elitsm);

    int get_best_fit();
    int get_worst_fit();
    float get_average_fit();

    int get_size();
    void add_individual(Individual new_individual);

    void set_individuals(vector<Individual> indvs);

    void pop_indv();
    vector<Individual> get_individuals();
    vector<Individual>& get_individuals_ref();
    void remove_individual_by_index(int index);
    void sort_individuals();
    void clear_population();

};