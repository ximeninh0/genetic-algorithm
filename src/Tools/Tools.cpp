#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <ctime>
#include <random> // Para substituir std::experimental::randint
#include <algorithm>
#include "Entities/Individual.h"
#include "Entities/Gene.h"
#include "Entities/Point.h"
#include "Entities/Population.h"

using namespace std;

float Tools::weight(Point P1, Point P2)
{
    float x_dist = P1.get_x() - P2.get_x();
    float y_dist = P1.get_y() - P2.get_y();
    float weight = pow(x_dist, 2) + pow(y_dist, 2);
    return sqrt(weight);
}

void Tools::header()
{
    cout << "------------------------------ \n"
         << "-----{Algoritmo Genético}----- \n"
         << "-----{Caixeiro  Viajante}----- \n"
         << "------------------------------ \n"
         << "[1] Gerar pontos aleatórios\n"
         << "[2] Gerar pontos em círculo (benchmark)\n"
         << endl;
}

vector<Gene> Tools::PopulateCitiesWithRandomPoints(vector<Gene> cities)
{
    std::srand(std::time(nullptr));
    char alfabeto[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                       'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                       'Y', 'Z'};

    int n, area;
    cout << "Insira a quantidade de pontos: " << endl;
    cin >> n;

    cout << "Insira o raio da área de cobertura dos pontos: " << endl;
    cin >> area;

    for (int i = 0; i < n; i++)
    {
        int random_x;
        int random_y;

        do
        {
            random_x = std::rand() % (area * 2) - area;
            random_y = std::rand() % (area * 2) - area;
        } while (pow(random_x, 2) + pow(random_y, 2) >= pow(area, 2));

        char name = alfabeto[i];
        Gene new_city(name, random_x, random_y);
        // new_city.print_gene();
        cities.push_back(new_city);
    }
    return cities;
}

Population Tools::getBestHalf(Population &population)
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
        else if(ind2.get_fitness() < ind1.get_fitness())
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
