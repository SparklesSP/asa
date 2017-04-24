#include <iostream>
#include <vector>

#define FAIL "Insuficiente"

using namespace std;


class Connection {

  public:

    int city1;
    int city2;
    int cost;

  Connection(int a, int b, int c) : city1(a), city2(b), cost(c){}

};

class City {

  public:

    int id;
    bool hasAirport = false;
    int airportCost;
    vector<Connection *> connectionsList;

  City(int ID) : id(ID) {}
  
};



int main() {

  vector<City *> cityList;
  int numCities;
  int numAeroports;
  int numRoads;

  cin >> numCities >> numAeroports;

  for (int i = 0; i < numCities; i++) {

    cityList.push_back(new City(i));
  }

  for (int i = 0; i < numAeroports; i++) {

    int city;
    int cost;

    cin >> city >> cost;
    city--;

    cityList.at(city)->hasAirport = true;
    cityList.at(city)->airportCost = cost;
  }

  cin >> numRoads;

  for (int i = 0; i < numRoads; i++) {

    int a;
    int b;
    int c;

    cin >> a >> b >> c;
    a--;
    b--;

    Connection* con = new Connection(a, b, c);
    cityList.at(a)->connectionsList.push_back(con);
    cityList.at(b)->connectionsList.push_back(con);
  }

  return 1;
}
