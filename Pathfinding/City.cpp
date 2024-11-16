#include "City.h"
#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

City::City(std::string name) : name(std::move(name)), allPath()
{}

void City::setRoads(std::vector<Road*> roads)
{
	this->roads = std::move(roads);
}

vector<Road*> City::findSmallestPath()
{
	// Base for all paths
	vector<City*> path;
	path.emplace_back(this);

	// Get all possible paths
	findAllCityPaths(path);

	// Transform all possible cities path into roads path
	auto availablePaths = changeCityListToRoads(getAllPath());

	// Check the smallest path
	auto smallestPath = getSmallestPath(availablePaths);
	return smallestPath;
}

void City::findAllCityPaths(std::vector<City*> currentPath)
{
	//Init Current city
	City* currentCity = currentPath.back();
	
	// If last city/path
	if(currentPath.size() == 6)
	{
		if(currentPath.back() == currentPath[0]) allPath.emplace_back(currentPath);
	}
	
	// If between beginning and end of the whole path 
	else if(currentPath.size() < 6 && currentPath.size() > 1)
	{
		vector<Road*> currentRoads = currentCity->getRoads();
		
		for(size_t i = 0; i<currentRoads.size(); i++)
		{
			Road* currentRoad = currentRoads[i];
			bool alreadyTook = false;
			if (currentPath.size() != 5)
			{
				for(size_t j = 0; j < currentPath.size()-1; j++)
				{
					if(currentRoad->start == currentPath[j]) { alreadyTook = true; continue; }
					if(currentRoad->end == currentPath[j]) { alreadyTook = true; continue; }
				}
			}
			if (alreadyTook) continue;
			
			if(currentPath.back() == currentRoads[i]->start)
			{
				std::vector<City*> currentPathCopy = currentPath;
				currentPathCopy.emplace_back(currentRoads[i]->end);
				findAllCityPaths(currentPathCopy);
			}

			if(currentPath.back() == currentRoads[i]->end)
			{
				std::vector<City*> currentPathCopy = currentPath;
				currentPathCopy.emplace_back(currentRoads[i]->start);
				findAllCityPaths(currentPathCopy);
			}
		}
	}

	// If this is the first road
	if(currentPath.size() == 1)
	{
		vector<Road*> currentRoads = currentCity->getRoads();
		for(size_t i = 0; i<currentRoads.size(); i++)
		{
			if(currentPath.back() == currentRoads[i]->start)
			{
				std::vector<City*> currentPathCopy = currentPath;
				currentPathCopy.emplace_back(currentRoads[i]->end);
				findAllCityPaths(currentPathCopy);
			}

			if(currentPath.back() == currentRoads[i]->end)
			{
				std::vector<City*> currentPathCopy = currentPath;
				currentPathCopy.emplace_back(currentRoads[i]->start);
				findAllCityPaths(currentPathCopy);
			}
		}
	}
}

vector<vector<Road*>> City::changeCityListToRoads(vector<vector<City*>> citiesPath)
{
	// Convert a vector of cities into a vector of roads 
	vector<vector<Road*>> allRoads; 
	for (size_t i = 0; i<citiesPath.size(); i++)
	{
		vector<Road*> thisRoad;
		for (size_t j = 0; j<citiesPath[i].size()-1; j++)
		{
			for (size_t k = 0; k<citiesPath[i][j]->getRoads().size(); k++)
			{
				Road* currentRoad = citiesPath[i][j]->getRoads()[k];
				if ((currentRoad->start == citiesPath[i][j] || currentRoad->end == citiesPath[i][j]) && (currentRoad->start == citiesPath[i][j+1] || currentRoad->end == citiesPath[i][j+1]))
				{
					thisRoad.emplace_back(currentRoad);
				}
			}
		}
		allRoads.emplace_back(thisRoad);
	}
	return allRoads;
}

vector<Road*> City::getSmallestPath(vector<vector<Road*>> availablePath)
{
	// Check which roads path has the smallest distance
	vector<Road*> minimumPath;
	int minimumDistance = INT_MAX;
	for (size_t i = 0; i<availablePath.size(); i++)
	{
		int currentDistance = 0;
		for (size_t j = 0; j<availablePath[i].size(); j++)
		{
			currentDistance += availablePath[i][j]->length;
		}
		if (currentDistance<minimumDistance)
		{
			minimumDistance = currentDistance;
			minimumPath = availablePath[i];
		}
	}
	return minimumPath;
}

void City::printPath(vector<Road*> path)
{
	// Print a path and its cost in the console
	City* currentCity = this;
	cout << this->name;
	for (size_t  i = 0; i<path.size(); i++)
	{
		if (path[i]->start == currentCity)
		{
			std::cout<< " -> "<<path[i]->end->name;
			currentCity = path[i]->end;
		}
		else
		{
			std::cout<< " -> "<<path[i]->start->name;
			currentCity = path[i]->start;
		}
	}
	int distance = 0;
	for (size_t  i = 0; i<path.size(); i++)
	{
		distance += path[i]->length;
	}
	cout << "\nDistance : " << distance << "\n";
}