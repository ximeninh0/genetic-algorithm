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
#include "Entities/Population.h"

using namespace std;

class Tools
{
public:
    float weight(Point P1, Point P2);
    void header();
    vector<Gene> PopulateCitiesWithRandomPoints(vector<Gene> cities);
    Population getBestHalf(Population &population);
};