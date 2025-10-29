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
#include "Entities/Population.h"
#include "Tools/Tools.h"
using namespace std;

// Costrutor da população, realiza permutações aleatórias para formar as primeiras rotas
Population::Population(Gene first_route_city, vector<Gene> cities, int size_p)
{
    this->size_p = size_p;
    Tools tools;

    vector<Gene> initial_chromossome;

    cities.erase(cities.begin());

    initial_chromossome = cities;
    int size = initial_chromossome.size();
    for (int indv_index = 0; indv_index < size_p; indv_index++)
    {
        vector<Gene> new_indiv_chromo = initial_chromossome;

        for (int i = 0; i < initial_chromossome.size(); i++)
        {
            int random_index = tools.random_number(i, size - 1);

            Gene temp = new_indiv_chromo[random_index];
            new_indiv_chromo[random_index] = new_indiv_chromo[i];
            new_indiv_chromo[i] = temp;
        }

        Individual individual(new_indiv_chromo, indv_index + 1, 1, first_route_city);
        this->individuals.push_back(individual);
    }
}

// Construtor vazio para aplicações do código
Population::Population(){}

// Remove um indivíduo pelo seu index
void Population::remove_individual_by_index(int index) { individuals.erase(individuals.begin() + index - 1); }

// Retorna o tamanho P especificado para a população no início
int Population::get_size(){ return this->size_p; }

// Adiciona um indivíduo para a população
void Population::add_individual(Individual new_individual) { individuals.push_back(new_individual); }

void Population::pop_indv(){
    this->individuals.pop_back();
}

// Ordena os indivíduos com base na qualidade (do melhor pro pior) !!!== APLICAR QUICK SORT ==!!!
void Population::sort_individuals(){
    vector<Individual> individuals = this->get_individuals();
    for (int i = 0; i < individuals.size(); i++){
        for(int j = i; j < individuals.size(); j++){
            if(individuals[j].get_fitness() > individuals[i].get_fitness()){
                Individual temp = individuals[j];
                individuals[j] = individuals[i];
                individuals[i] = temp;
            }
        }
    }
    this->individuals = individuals;
}

// Getters e Setters
int Population::get_index() { return index; }
void Population::set_index(char new_index) { index = new_index; }

int Population::get_generation() { return generation; }
void Population::set_generation(char new_generation) { generation = new_generation; }

vector<Individual> Population::get_individuals(){return individuals;}
void Population::set_individuals(vector<Individual> indvs) {this->individuals = indvs; }


// Prints
void Population::print_population()
{
    for (Individual individual : individuals)
    {
        individual.print_individual();
    }
    cout << "\n" << endl;
}



