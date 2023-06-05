#ifndef FILEWORK_H
#define FILEWORK_H
#include "classes.h"
#include <fstream>
#include <QCoreApplication>
class filework{
    string path;
public:
    filework(string);
    void write_to(vector<int>, vector<int>, vector<int>, vector<int>, vector<vector<int>>);
};

#endif // FILEWORK_H
