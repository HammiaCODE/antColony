#ifndef ACO_H
#define ACO_H

#include "tsp_struct.h"
#include "tsp_loader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>

int ACO_TSP(const vector<City>& cities, int alpha,int beta, int rho,int num_cities){
    // distance matrix, time and space complexity O(n^2)
    vector<vector<double>> distances = DistGraph(cities);

    //build edges, O(n^2)
    vector<Edge> edges = BuildEdges(distances, num_cities);

}

#endif