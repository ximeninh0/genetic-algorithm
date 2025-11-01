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

const double PI = std::acos(-1.0);

using namespace std;


Tools::Tools() : gen(std::chrono::system_clock::now().time_since_epoch().count()) {
    gen.seed(2213);
}

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
vector<Gene> Tools::PopulateCitiesWithRandomPoints()
{
    std::vector<Gene> cities;

    int n, area;

    do
    {
        cout << "Insira a quantidade de pontos: " << endl;
        cin >> n;
        /* code */
    } while (n > 26 || n <= 0 );

    cout << "Insira o raio da área de cobertura dos pontos: " << endl;
    cin >> area;

    cities.clear();
    cities.reserve(n);

    // Loop para gerar as cidades
    for (int i = 0; i < n; i++)
    {
        int random_x;
        int random_y;
        // Gera os pontos (x,y) aleatórios dentro da área cartesiana circular estipulada pelo usuário
        do
        {

            random_x = this->random_number((area * (-1)), area, 2213);
            random_y = this->random_number((area * (-1)), area, 2213);
        } while (pow(random_x, 2) + pow(random_y, 2) >= pow(area, 2)); // Repete até que esteja dentro do raio da circunferência

        char name = this->alfabeto[i % 26]; // Nomeia a cidade com letras do alfabeto
        cities.emplace_back(name, random_x, random_y);
    }

    return cities;
}

vector<Gene> Tools::PopulateCitiesinCircle()
{
    std::vector<Gene> cities;

    int n_points, Radius;
    cout << "Insira a quantidade de pontos: " << endl;
    cin >> n_points;

    cout << "Insira o raio da circunferencia: " << endl;
    cin >> Radius;

    double angleStep = 2.0 * PI / n_points;

    for (int i = 0; i < n_points; i++)
    {
        double currentAngle = i * angleStep;

        double x = 0 + Radius * cos(currentAngle);
        double y = 0 + Radius * sin(currentAngle);

        char name = this->alfabeto[i];
        Gene new_city(name, x, y);
        cities.push_back(new_city);
    }
    
    return cities;
}

// Função para calcular números aleatórios dentro de um intervalo inteiro com seed
int Tools::random_number(int limite_inferior, int limite_superior, int seed) {
    std::uniform_int_distribution<> dist(limite_inferior, limite_superior);
    return dist(this->gen); // 'this->gen' é o gerador da instância da classe
}

// Função para calcular números aleatórios dentro de um intervalo inteiro sem seed
int Tools::random_number(int limite_inferior, int limite_superior)
{
    static std::mt19937 gen(
        static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<> dist(limite_inferior, limite_superior);
    return dist(gen);
}

std::vector<std::pair<float, float>> Tools::individual_to_tuple_array(vector<Gene> chromossome, Gene first_point)
{
    std::vector<std::pair<float, float>> result;
    std::pair<float, float> first_point_t = {first_point.get_point().get_x(), first_point.get_point().get_y()};
    result.push_back(first_point_t);
    for (Gene gene : chromossome)
    {
        std::pair<float, float> point = {gene.get_point().get_x(), gene.get_point().get_y()};
        result.push_back(point);
    }
    return result;
}

void Tools::save_generation(int gen, float bestFitness, const std::vector<std::pair<float, float>> &points,
                            vector<Gene> route, Gene first_point)
{
    json j;
    j["generation"] = gen;
    j["best_fitness"] = bestFitness;
    for (auto &p : points)
        j["points"].push_back({p.first, p.second});
    j["route"].push_back(first_point.get_name());
    for (auto &r : route)
        j["route"].push_back(r.get_name());
    j["route"].push_back(first_point.get_name());

    std::ofstream("data.json") << j.dump(4);
}