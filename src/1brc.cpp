#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

struct cityStruct {
    float total = 0;
    int steps = 0;

    float min = 999;
    float max = -999;

    string name;
    bool isEmpty() const {return name == "";}
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

int main() {
    long long steps = 0;
    map <string, cityStruct> cities;
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open("measurements.txt", ios::in);
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