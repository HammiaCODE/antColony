#ifndef TSP_LOADER_H
#define TSP_LOADER_H

#include "tsp_struct.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

vector<City> loadTSP(const string& filename) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Error: could not open file " + filename);
    }

    string line;
    vector<City> cities;

    while (getline(file, line)) {
        if (line.find("NODE_COORD_SECTION") != string::npos)
            break;
    }

    while (getline(file, line)) {
        if (line == "EOF" || line.empty()) break;
        stringstream ss(line);
        int id;
        City c;
        ss >> id >> c.x >> c.y;
        cities.push_back(c);
    }

    return cities;
}

#endif 
