#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <cstdio>
#include "Headers/stdc++.h"

using namespace std;

struct cityStruct {
    long long total;
    int steps;

    float min;
    float max;
};

void addData(map <string,cityStruct> &cities, string nameCity, float tempCity) {
    auto city = cities.find(nameCity);

    if (city == cities.end()) {
        cities.emplace(nameCity, cityStruct{1, 1, 999, -999});
    }

    city -> second.min = min(city->second.min, tempCity);
    city -> second.max = max(city->second.max, tempCity);

    city -> second.total += int(tempCity*100);
    city -> second.steps++;
}

void lectureFile(const char * filePath, map <string, cityStruct> &cities) {
    long int steps = 0;
    ifstream inputFile;
    FILE *fp = fopen(filePath, "r");

    char nameC[25];
    float tempC = 0;

    string line;
    string nameCity;

    while(fscanf(fp,"%49[^;];%f", nameC, &tempC) != EOF)
    {
        nameCity = string(nameC);

        if(steps % 100000 == 0 && steps != 0) {
            cout << steps << endl;
        }

        addData(cities, nameCity, tempC);

        steps = steps + 1;
    }
}

void writeFile(string filePath, map <string,cityStruct> &cities) {
    ofstream outputFile;
    string cityString;
    outputFile.open(filePath);
    for ( const auto & city : cities) {
        outputFile << city.first + ";" + to_string(city.second.min) + ";" + to_string((float(city.second.total)/float(city.second.steps))/100) + ";" + to_string(city.second.max);
    }
    outputFile.close();
}

int main() {
    const char *inputPath = "./1brc/measurements.txt";
    string outputPath = "./src/output.txt";
    map <string, cityStruct> cities;

    lectureFile(inputPath, cities);
    writeFile(outputPath, cities);
}