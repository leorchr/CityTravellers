#include "City.h"
#include <iostream>
using namespace std;

City::City(std::string name) : name(std::move(name)){}

void City::setRoads(std::vector<Road*> roads)
{
	this->roads = std::move(roads);
}

std::vector<City*> City::findClosestPath(City* endPoint)
{
	City* currentCity = this;
	int cost = 0;
	std::vector<City*> path;
	path.emplace_back(currentCity);
	
	while(currentCity != endPoint)
	{
		int currentLowestCost = 10000;
		for(int i = 0; i<currentCity->getRoads().size(); i++)
		{

			//Find the city
			if(currentCity->getRoads()[i]->start == endPoint)
			{
				currentCity = currentCity->getRoads()[i]->start;
				break;
			}
			if(currentCity->getRoads()[i]->end == endPoint)
			{
				currentCity = currentCity->getRoads()[i]->end;
				break;
			}



			//Not find
			//Need to choose another one with the lowest length
			if(currentCity->getRoads()[i]->length < currentLowestCost)
			{
				currentLowestCost = currentCity->getRoads()[i]->length;
				if(currentCity->getRoads()[i]->start == currentCity) currentCity = currentCity->getRoads()[i]->start;
				else currentCity = currentCity->getRoads()[i]->end;
			}
		}
		cost += currentLowestCost;
		path.emplace_back(currentCity);
	}

	return path;
}