#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <ctime>
#include <chrono>
#include <experimental/random>
#include <random>
#include <algorithm>
#include "Entities/Individual.h"
#include "Entities/Gene.h"
#include "Entities/Point.h"

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
            random_x = this->random_number((area * (-1)), area);
            random_y = this->random_number((area * (-1)), area);
        } while (pow(random_x, 2) + pow(random_y, 2) >= pow(area, 2));

        char name = alfabeto[i];
        Gene new_city(name, random_x, random_y);
        cities.push_back(new_city);
    }
    return cities;
}

int Tools::random_number(int n1,int n2){
    // static std::mt19937 gen(
    //     static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count())
    // );
    static std::mt19937 gen(220);
    std::uniform_int_distribution<> dist(n1, n2);
    return dist(gen);
}