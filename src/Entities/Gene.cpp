#include <map>
#include <array>
#include <string>
#include <vector>
#include <functional>
#include <cstring>
#include <iostream>
#include "Entities/Point.h"
#include "Entities/Gene.h"

using namespace std;

// Construtores
Gene::Gene() {}
Gene::Gene(char name, int x, int y)
{
    set_name(name);
    set_point(x, y);
}
Gene::~Gene(){ }

// Getters e Setters
char Gene::get_name() { return name; }
void Gene::set_name(char name) { this->name = name; }

Point Gene::get_point() { return this->coordinates; }
void Gene::set_point(int x, int y)
{
    this->coordinates.set_x(x);
    this->coordinates.set_y(y);
}

// Prints
void Gene::print_gene()
{
    cout << name << "(" << coordinates.get_x() << "," << coordinates.get_y() << ")" << endl;
}