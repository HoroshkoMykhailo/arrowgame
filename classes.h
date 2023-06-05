#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>
using namespace std;
class cell{
    int num;
    int num_of_arrows;
public:
    cell();
    cell(int);
    void add_arrow();
    void remove_arrow();
    bool is_safe();
    bool is_solved();
};
class field{
    vector<vector<cell>> square;
    vector<int> right;
    vector<int> left;
    vector<int> up;
    vector<int> down;
    void add_arrow(int, size_t, char);
    void remove_arrow(size_t, char);
    bool is_safe(int, size_t, char);
    bool is_solved();
public:
    field();
    field(vector<vector<int>>);
    vector<int> getright();
    vector<int> getleft();
    vector<int> getup();
    vector<int> getdown();
    bool solve(pair<size_t, char>);
    pair<size_t, char> next(pair<size_t, char>);
};
vector<vector<int>> generate(size_t);
int random(int,int);
#endif // CLASSES_H
