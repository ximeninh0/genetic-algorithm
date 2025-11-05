#pragma once

#include "Entities/Point.h"

class Gene
{
private:
    int name;
    Point coordinates;

public:
    Gene();
    ~Gene();
    Gene(int name, int x, int y);
    void print_gene();
    int get_name();
    void set_name(int new_name);
    Point get_point() const;
    void set_point(int x, int y);
};