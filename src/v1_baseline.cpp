#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <cstdio>
#include "Headers/stdc++.h"

using namespace std;

struct cityStruct {
    int total = 0;
    int steps = 0;

    int min = 999;
    int max = -999;
};

void addData(map <string,cityStruct> &cities, string nameCity, string tempCity) {
    float tmpFCity;
    tmpFCity = stof(tempCity);

    cityStruct city = cities[nameCity];

    city.total = city.total + tmpFCity;
    city.steps = city.steps + 1;

    if (city.min > tmpFCity) {
        city.min = tmpFCity;
    }

    if (city.max < tmpFCity) {
        city.max = tmpFCity;
    }

    cities[nameCity] = city;
}

void lectureFile(string filePath) {
    long long steps = 0;
    map <string, cityStruct> cities;
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(filePath, ios::in);
    string line;
    string nameCity, tempCity;

    while(getline(inputFile, line))
    {
        if(steps % 100000 == 0 && steps != 0) {
            cout << steps << endl;
        }
        stringstream stream(line);

        getline(stream, nameCity, ';');
        getline(stream, tempCity, ';');

        addData(cities, nameCity, tempCity);

        steps = steps + 1;
    }

    string cityString;
    outputFile.open("./output.txt");
    for ( const auto & city : cities) {
        cityString = city.first + ";" + to_string(city.second.min) + ";" + to_string(city.second.total/city.second.steps) + ";" + to_string(city.second.max);
        outputFile << cityString;
    }
    outputFile.close();

}

int main() {
    lectureFile("./1brc/measurements.txt");
}