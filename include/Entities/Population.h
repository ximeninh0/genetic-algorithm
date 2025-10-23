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
    int index;
    int generation;
    int size_p;
    vector<Individual> individuals;

public:
    Population(Gene first_route_city, vector<Gene> cities, int size_p);
    void print_population();
    int get_index();
    void set_index(char new_index);
    int get_generation();
    void set_generation(char new_generation);
    void add_individual(Individual new_individual);
    void remove_individual_by_index(int index);
};