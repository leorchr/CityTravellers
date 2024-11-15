#include "City.h"
#include <climits>
#include <iostream>
using namespace std;

City::City(std::string name) : name(std::move(name)){}

void City::setRoads(std::vector<Road*> roads)
{
	this->roads = std::move(roads);
}

std::vector<City*> City::getAllPaths(City* endPoint, std::vector<City*> currentPath)
{
	if(currentPath.size() == 5)
	{
		if(currentPath.back() == endPoint) allPath.emplace_back(currentPath);
	}
	if(currentPath.size() < 5)
	{
		for(size_t i = 0; i<roads.size(); i++)
		{
			Road* currentRoad = roads[i];
			for(size_t i = 0; i < currentPath.size()-1; i++)
			{
				if(currentRoad->start == currentPath[i]) return std::vector<City*>();
				if(currentRoad->end == currentPath[i]) return std::vector<City*>();
			}

			if(currentPath.back() == roads[i]->start)
			{
				currentPath.emplace_back(roads[i]->end);
				return getAllPaths(endPoint, currentPath);
			}

			if(currentPath.back() == roads[i]->end)
			{
				currentPath.emplace_back(roads[i]->start);
				return getAllPaths(endPoint, currentPath);
			}
		}
	}
}


std::vector<City*> City::findClosestPath(City* endPoint)
{
	std::vector<City*> path;
	path.emplace_back(this);
	
	getAllPaths(endPoint, path);

	return path;
}

vector<vector<City*>> City::allPath = vector<vector<City*>>();