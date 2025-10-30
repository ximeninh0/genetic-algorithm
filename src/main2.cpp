#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <ctime>
#include <experimental/random>
#include <random>
#include <algorithm>
#include "Entities/Gene.h"
#include "Entities/Individual.h"
#include "Entities/Point.h"
#include "Entities/Population.h"
#include "Tools/Tools.h"
#include "Genetics/GeneticAlgorithm.h"

using namespace std;

// g++ -Iinclude src/main.cpp src/Entities/*.cpp src/Tools/*.cpp src/Genetics/*.cpp -o main

int main()
{
    vector<Gene> genes;
    for (int i = 0; i < 1000000000; i++)
    {
        Gene gene('T', 10, 20);
        genes.push_back(gene);
    }
    for (int i = 0; i < 1000000000; i++)
    {
        genes.pop_back();
    }
}