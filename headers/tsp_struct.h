#ifndef TSP_STRUCT_H
#define TSP_STRUCT_H

#include <cmath>
#include <vector>

using namespace std;

struct City {
    double x, y;
};

struct Edge{
    int a,b;
    double distance;

    //operator overload < to compare 2 edges
    bool operator<(const Edge& other) const {
        return distance < other.distance;
    }
};

double euclidean(const City& a, const City& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

vector<vector<double>> DistGraph(const vector<City>& cities){
    int n = cities.size();
    vector<vector<double>> distances(n, vector<double>(n)); // n x n

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i == j){
                distances[i][j] = 0.0;
            } else {
                distances[i][j] = euclidean(cities[i], cities[j]);
            }
        }
    }
    return distances;
}

vector<Edge> BuildEdges(const vector<vector<double>>& distances, int n){
    vector<Edge> edges;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            edges.push_back(Edge{i, j, distances[i][j]});
        }
    }
    sort(edges.begin(), edges.end());
    return edges;
}

#endif