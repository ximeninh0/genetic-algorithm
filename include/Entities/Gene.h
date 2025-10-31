#pragma once

#include "Entities/Point.h"

class Gene
{
private:
    char name;
    Point coordinates;

public:
    Gene();
    ~Gene();
    Gene(char name, int x, int y);
    void print_gene();
    char get_name();
    void set_name(char new_name);
    Point get_point();
    void set_point(int x, int y);
};