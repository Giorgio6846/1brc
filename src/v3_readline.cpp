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

void addData(map <string,cityStruct> &cities, string nameCity, float tempCity) {
    int tmpFCity = int(tempCity * 10);

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

void lectureFile(const char * filePath) {
    long int steps = 0;
    map <string, cityStruct> cities;
    ifstream inputFile;

    FILE *fp = fopen(filePath, "r");

    char nameC[25];
    float tempC = 0;

    string line;
    string nameCity, tempCity;

    while(fscanf(fp,"%49[^;];%f", nameC, &tempC) != EOF)
    {
        nameCity = string(nameC);

        if(steps % 100000 == 0 && steps != 0) {
            cout << steps << endl;
        }

        addData(cities, nameCity, tempC);

        steps = steps + 1;
    }

    ofstream outputFile;
    string cityString;
    outputFile.open("./src/output.txt");
    for ( const auto & city : cities) {
        cityString = city.first + ";" + to_string(city.second.min/10) + ";" + to_string(city.second.total/city.second.steps*10) + ";" + to_string(city.second.max/10) + "\n";
        outputFile << cityString;
    }
    outputFile.close();

}

int main() {
    const char *filePath = "./1brc/measurements.txt";

    lectureFile(filePath);
}