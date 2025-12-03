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

using namespace std;

static double tourLength(const vector<int>& tour, const vector<vector<double>>& distances) {
    double sum = 0.0;
    int n = tour.size();
    for (int i = 0; i < n - 1; ++i) {
        sum += distances[tour[i]][tour[i+1]];
    }
    // close loop
    sum += distances[tour.back()][tour.front()];
    return sum;
}

static int rouletteSelect(const vector<double>& probs, mt19937 &gen) {
    double total = 0.0;
    for (double p : probs) total += p;
    if (total <= 0.0) {
        uniform_int_distribution<> dis(0, (int)probs.size()-1);
        return dis(gen);
    }
    uniform_real_distribution<> dist(0.0, total);
    double r = dist(gen);
    double s = 0.0;
    for (int i = 0; i < (int)probs.size(); ++i) {
        s += probs[i];
        if (s >= r) return i;
    }
    return (int)probs.size()-1;
}

int ACO_TSP(const vector<City>& cities, double alpha, double beta, double rho,
            int num_cities, int iterations, double initial_pheromone) {

    if (cities.empty() || num_cities <= 0) return 0;
    const int n = num_cities;
    const int nAnts = n; 
    const double Q = 100.0;

    // distance matrix from tsp_struct
    vector<vector<double>> distances = DistGraph(cities);

    // initialize pheromone matrix
    vector<vector<double>> pheromone(n, vector<double>(n, initial_pheromone));

    random_device rd;
    mt19937 gen(rd());

    double bestLength = numeric_limits<double>::infinity();
    vector<int> bestTour;

    for (int iter = 0; iter < iterations; ++iter) {

        vector<vector<int>> antsTours(nAnts);
        vector<double> antsLengths(nAnts, 0.0);

        for (int k = 0; k < nAnts; ++k) {
            vector<int> tour;
            tour.reserve(n);

            // pick random start
            uniform_int_distribution<> startDist(0, n-1);
            int start = startDist(gen);
            tour.push_back(start);

            vector<char> visited(n, 0);
            visited[start] = 1;

            for (int step = 1; step < n; ++step) {
                int current = tour.back();

                // compute weights for unvisited cities
                vector<double> weights;
                vector<int> candidates; 
                weights.reserve(n - step);
                candidates.reserve(n - step);

                for (int j = 0; j < n; ++j) {
                    if (!visited[j]) {
                        double tau = pow(pheromone[current][j], alpha);
                        double eta;
                        if (distances[current][j] <= 0.0) {

                            eta = 1e6;
                        } else {
                            eta = pow(1.0 / distances[current][j], beta); // 
                        }
                        double w = tau * eta;
                        weights.push_back(w);
                        candidates.push_back(j);
                    }
                }

                // select next city by roulette wheel on weights
                int pickIndex = rouletteSelect(weights, gen);
                int nextCity = candidates[pickIndex];
                tour.push_back(nextCity);
                visited[nextCity] = 1;
            }

            antsTours[k] = tour;
            double length = tourLength(tour, distances);
            antsLengths[k] = length;

            // update global best
            if (length < bestLength) {
                bestLength = length;
                bestTour = tour;
            }
        } 

        // pheromone evaporation
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                pheromone[i][j] *= (1.0 - rho);
                if (pheromone[i][j] < 1e-12) pheromone[i][j] = 1e-12;
            }
        }

        // pheromone deposit by ants
        for (int k = 0; k < nAnts; ++k) {
            double Lk = antsLengths[k];
            if (Lk <= 0.0) continue;
            double delta = Q / Lk;
            const vector<int>& tour = antsTours[k];
            for (int i = 0; i < (int)tour.size(); ++i) {
                int a = tour[i];
                int b = (i + 1 < (int)tour.size()) ? tour[i+1] : tour[0];
                pheromone[a][b] += delta;
                pheromone[b][a] += delta; 
            }
        }

    }

    cout << (int)round(bestLength) <<endl;
    cout << "Route:";

    for(int k=0;k<bestTour.size();k++){
        cout <<"["<< bestTour[k] <<"]"<< " -> ";
    }
    
    return 0;
}

#endif