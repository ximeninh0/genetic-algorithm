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

class Tools
{
public:
    float weight(Point P1, Point P2);
    void header();
    vector<Gene> PopulateCitiesWithRandomPoints(vector<Gene> cities);
    int random_number(int n1, int n2);
    int random_number(int n1, int n2, int seed);

    void save_generation(int gen, float bestFitness, const std::vector<std::pair<float,float>>& points, 
                            vector<Gene> route, Gene first_point);
    std::vector<std::pair<float,float>> individual_to_tuple_array(vector<Gene> chromossome, Gene first_point);
};