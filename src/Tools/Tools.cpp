#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <ctime>
#include <chrono>
#include <experimental/random>
#include <random>
#include <nlohmann/json.hpp>
#include <algorithm>
#include "Entities/Individual.h"
#include "Entities/Gene.h"
#include "Entities/Point.h"
#include <fstream>

using json = nlohmann::json;

using namespace std;

// Função w, recebe dois pontos e calcula a distancia euclediana entre eles
float Tools::weight(Point P1, Point P2)
{
    float x_dist = P1.get_x() - P2.get_x();
    float y_dist = P1.get_y() - P2.get_y();
    float weight = pow(x_dist, 2) + pow(y_dist, 2);
    return sqrt(weight);
}


// Função para imprimir o header
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

// Preenche um vetor com n cidades, distribuídas em pontos aleatórios
vector<Gene> Tools::PopulateCitiesWithRandomPoints(vector<Gene> cities)
{
    char alfabeto[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                       'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                       'Y', 'Z'};

    int n, area;
    cout << "Insira a quantidade de pontos: " << endl;
    cin >> n;

    cout << "Insira o raio da área de cobertura dos pontos: " << endl;
    cin >> area;

    // Loop para gerar as cidades
    for (int i = 0; i < n; i++)
    {
        int random_x;
        int random_y;
        // Gera os pontos (x,y) aleatórios dentro da área cartesiana circular estipulada pelo usuário
        do
        {
            random_x = this->random_number((area * (-1)), area);
            random_y = this->random_number((area * (-1)), area);
        } while (pow(random_x, 2) + pow(random_y, 2) >= pow(area, 2));  // Repete até que esteja dentro do raio da circunferência

        char name = alfabeto[i];
        Gene new_city(name, random_x, random_y);
        cities.push_back(new_city);
    }
    return cities;
}

// Função para calcular números aleatórios dentro de um intervalo inteiro
int Tools::random_number(int limite_inferior,int limite_superior){
    // static std::mt19937 gen(
    //     static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count())
    // );
    static std::mt19937 gen(2213);
    std::uniform_int_distribution<> dist(limite_inferior, limite_superior);
    return dist(gen);
}

std::vector<std::pair<float,float>> Tools::individual_to_tuple_array(vector<Gene> chromossome, Gene first_point){
    std::vector<std::pair<float,float>> result;
    std::pair<float,float> first_point_t = {first_point.get_point().get_x(), first_point.get_point().get_y()};
    result.push_back(first_point_t);
    for(Gene gene : chromossome){
        std::pair<float,float> point = {gene.get_point().get_x(), gene.get_point().get_y()};
        result.push_back(point);
    }
    return result;
}


void Tools::save_generation(int gen, float bestFitness, const std::vector<std::pair<float,float>>& points, 
                            vector<Gene> route, Gene first_point) 
{
    json j;
    j["generation"] = gen;
    j["best_fitness"] = bestFitness;
    for (auto& p : points)
        j["points"].push_back({p.first, p.second});
    j["route"].push_back(first_point.get_name());
    for (auto& r : route)
        j["route"].push_back(r.get_name());
    j["route"].push_back(first_point.get_name());

    std::ofstream("data.json") << j.dump(4);
}