#ifndef ACO_H
#define ACO_H

#include "tsp_struct.h"
#include "tsp_loader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>



double probabilities(const vector<City>& cities, double alpha, double beta, double rho, int num_cities)
{
    vector<double> desTab;
    vector<double> probTab;
    double prob;

    // distance matrix
    vector<vector<double>> distances = DistGraph(cities);

    // edges
    vector<Edge> edges = BuildEdges(distances, num_cities);

    for (int j = 0; j < edges.size(); j++) {
        double desirability = 1.0 / edges[j].distance;  
        desTab.push_back(desirability);                
    }

    double dSum = 0.0;
    for (double d : desTab) dSum += d;

    for(int k=0;k<desTab.size();k++){
        prob = (rho * desTab[k]) / dSum;
        probTab.push_back(prob);
    }

    sort(probTab.begin(),probTab.end());

    return probTab[0];
}



int ACO_TSP(const vector<City>& cities, double alpha, double beta, double rho,int num_cities){
    // distance matrix
    vector<vector<double>> distances = DistGraph(cities);

    //edges
    vector<Edge> edges = BuildEdges(distances, num_cities);

}

#endif