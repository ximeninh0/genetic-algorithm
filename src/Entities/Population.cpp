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
#include "entities/Population.h"
using namespace std;

Population::Population(Gene first_route_city, vector<Gene> cities, int size_p)
{
    this->size_p = size_p;

    vector<Gene> initial_chromossome;

    cities.erase(cities.begin());

    initial_chromossome = cities;
    int size = initial_chromossome.size();
    for (int indv_index = 0; indv_index < size_p; indv_index++)
    {
        vector<Gene> new_indiv_chromo = initial_chromossome;

        for (int i = 0; i < initial_chromossome.size(); i++)
        {
            int random_index = std::experimental::randint(i, size - 1);

            Gene temp = new_indiv_chromo[random_index];
            new_indiv_chromo[random_index] = new_indiv_chromo[i];
            new_indiv_chromo[i] = temp;
        }

        Individual individual(new_indiv_chromo, indv_index + 1, 1, first_route_city);
        this->individuals.push_back(individual);
    }
}

int Population::get_index() { return index; }
void Population::set_index(char new_index) { index = new_index; }

int Population::get_generation() { return generation; }
void Population::set_generation(char new_generation) { generation = new_generation; }

vector<Individual> Population::get_individuals(){return individuals;}
void Population::add_individual(Individual new_individual) { individuals.push_back(new_individual); }

void Population::remove_individual_by_index(int index) { individuals.erase(individuals.begin() + index - 1); }

void Population::print_population()
{
    for (Individual individual : individuals)
    {
        individual.print_individual();
    }
    cout << "\n" << endl;
}

