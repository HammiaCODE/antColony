#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include "./headers/tsp_loader.h"


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
    cout << "How many cities? ";
    cin >> num_cities;

    cout<< endl;
    cout << "How many iterations? ";
    cin >> iterations;

    if(num_cities > total_cities.size()){
        num_cities = total_cities.size();
    }

    for(int i=0;i<iterations;i++){
        
    }

    return 0;
}