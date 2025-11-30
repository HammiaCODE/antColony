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

    int number_of_cities;
    cout << "How many cities? ";
    cin >> number_of_cities;

    if(number_of_cities > total_cities.size()){
        number_of_cities = total_cities.size();
    }



    return 0;
}