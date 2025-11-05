#pragma once
class Point{
private:
    int x;
    int y;

public:
    int get_x() const;
    int get_y() const;
    void set_x(int new_x);
    void set_y(int new_y);
};