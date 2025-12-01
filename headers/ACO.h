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



float probabilities(const vector<City>& cities, double alpha,double beta, double rho,int num_cities){

    vector<double> probTabu;
    vector<double> probConstruct;


    // distance matrix, time and space complexity O(n^2)
    vector<vector<double>> distances = DistGraph(cities);

    //build edges, O(n^2)
    vector<Edge> edges = BuildEdges(distances, num_cities);
    
    double desirability = 1/num_cities;
    double pheromone;
    
    double probs = ((pheromone)*alpha)*(desirability*(beta));
    double sumProbs,construct;
    probTabu.push_back(probs);

    for(int j=0;j<num_cities;j++){
        sumProbs= probTabu[j]+probTabu[j+1];
        construct=probs/sumProbs;
        probConstruct.push_back(construct);
    }
}


int ACO_TSP(const vector<City>& cities, double alpha, double beta, double rho,int num_cities){
    // distance matrix, time and space complexity O(n^2)
    vector<vector<double>> distances = DistGraph(cities);

    //build edges, O(n^2)
    vector<Edge> edges = BuildEdges(distances, num_cities);

}

#endif