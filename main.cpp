#include <iostream>
#include <iomanip>
#include <vector>
// #include <chrono>
#include <math.h>
#include <ctime>
#include <experimental/random>

using namespace std;

class Point
{
private:
    int x;
    int y;

public:
    int get_x()
    {
        return x;
    }

    int get_y()
    {
        return y;
    }

    void set_x(int new_x)
    {
        x = new_x;
    }

    void set_y(int new_y)
    {
        y = new_y;
    }
};

class City
{
private:
    char name;
    Point coordinates;

public:
    City(char name, int x, int y)
    {
        set_name(name);
        set_coordinates(x, y);
    }
    void print_name()
    {
        cout << name << endl;
    }
    void print_gene()
    {
        cout << name << "(" << coordinates.get_x() << "," << coordinates.get_y() << ")" << endl;
    }

    char get_name()
    {
        return name;
    }

    void set_name(char new_name)
    {
        name = new_name;
    }
    void set_coordinates(int x, int y)
    {
        coordinates.set_x(x);
        coordinates.set_y(y);
    }
};

class Gene : public City
{
};

class Individual
{
private:
    int index;
    int generation;
    vector<Gene> chromossome;

public:
    // get_individual_fitness(){}
    void print_individual()
    {
        cout << generation << index;
        cout << "| ";
        for (Gene gene : chromossome)
        {
            cout << gene.get_name();
            cout << " | ";
        }
        cout << endl;
    }

    int get_index()
    {
        return index;
    }
    void set_index(char new_index)
    {
        index = new_index;
    }

    int get_generation()
    {
        return generation;
    }
    void set_generation(char new_generation)
    {
        generation = new_generation;
    }

    void add_gene(Gene new_gene)
    {
        chromossome.push_back(new_gene);
    }

    void remove_gene_by_name(char gene_name)
    {
        for (int i = 0; i < chromossome.size(); i++)
        {
            if (chromossome[i].get_name() == gene_name)
                chromossome.erase(chromossome.begin() + i);
        }
    }
};

class Population
{
private:
    int index;
    int generation;
    int size_p;
    vector<Individual> individuals;

public:
    void print_population()
    {
        for (Individual individual : individuals)
        {
            individual.print_individual();
        }
    }

    int get_index()
    {
        return index;
    }
    void set_index(char new_index)
    {
        index = new_index;
    }

    int get_generation()
    {
        return generation;
    }
    void set_generation(char new_generation)
    {
        generation = new_generation;
    }

    void add_individual(Individual new_individual)
    {
        individuals.push_back(new_individual);
    }

    void remove_individual_by_index(int index)
    {
        individuals.erase(individuals.begin() + index - 1);
    }
};

class GeneticEstrategy
{
private:
public:
};

class Reproduction
{
private:
public:
};

class Mutation
{
private:
public:
};

class PopulationAdjust
{
private:
public:
};

class Tools
{
public:
    float weight(Point P1, Point P2)
    {
        float x_dist = P1.get_x() - P2.get_x();
        float y_dist = P1.get_y() - P2.get_y();
        float weight = pow(x_dist, 2) + pow(y_dist, 2);
        return sqrt(weight);
    }
    void header()
    {
        cout << "------------------------------ \n"
             << "-----{Algoritmo Genético}----- \n"
             << "-----{Caixeiro Viajante }----- \n"
             << "------------------------------ \n"
             << "[1] Gerar pontos aleatórios\n"
             << "[2] Gerar pontos em cículo (benchmark)\n"
             << endl;
    }

    vector<City> PopulateCitiesWithRandomPoints(vector<City> cities)
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
                random_x = std::experimental::randint((area * (-1)), area);
                random_y = std::experimental::randint((area * (-1)), area);
            } while (pow(random_x, 2) + pow(random_y, 2) >= pow(area, 2));

            char name = alfabeto[i];
            City new_city(name, random_x, random_y);
            new_city.print_gene();
            cities.push_back(new_city);
        }
        return cities;
    }
};

int main()
{
    int option;
    vector<City> cities;
    Tools tools;

    tools.header();

    do
    {
        cin >> option;
        switch (option)
        {
        case 1:
            cities = tools.PopulateCitiesWithRandomPoints(cities);
            break;
        case 2:
            for (City city : cities)
                city.print_gene();
            break;
        }
    } while (option != 3);
}