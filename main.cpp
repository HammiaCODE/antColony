#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include "./headers/tsp_loader.h"
#include "./headers/ACO.h"


using namespace std;

int main(){
    vector<City> total_cities;
    try{
        total_cities = loadTSP("dsj1000.txt");
        cout << "Loaded " << total_cities.size() << endl;
    } catch(const exception& e){
        cerr << e.what() << '\n';
    }

    cout << "Ant Colony Optimization Algorithm for TSP" << endl; 

    int num_cities, iterations;
    int beta, alpha, rho;
    cout << "How many cities? ";
    cin >> num_cities;

    cout<< endl;
    cout << "How many iterations? ";
    cin >> iterations;

    cout<< endl;
    cout << "Beta (β): ";
    cin >> beta;

    cout<< endl;
    cout << "Alpha (a): ";
    cin >> alpha;

    cout<< endl;
    cout << "Rho (P): ";
    cin >> rho;

    if(num_cities > total_cities.size()){
        num_cities = total_cities.size();
    }

    // funcion random de n ciudades para guardarlas en cities no repetidas
    vector<int> unique_n(total_cities.size());
    for(int i = 0; i < total_cities.size(); ++i){
        unique_n[i] = i;
    }

    random_device rd;
    mt19937 gen(rd());

    for(int i = 0; i < num_cities; ++i){
        uniform_int_distribution<> dis(i, total_cities.size() - 1);
        int j = dis(gen);
        swap(unique_n[i], unique_n[j]);
    }

    vector<City> cities;
    for (int i = 0; i < num_cities; ++i) {
        cities.push_back(total_cities[unique_n[i]]);
    }

    for(int i=0;i<iterations;i++){
        //cout << ACO_TSP(cities,alpha,beta,rho)<<endl;

    }

    return 0;
}