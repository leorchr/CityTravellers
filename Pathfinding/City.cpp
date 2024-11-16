#include "City.h"
#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

City::City(std::string name) : name(std::move(name)){}

void City::setRoads(std::vector<Road*> roads)
{
	this->roads = std::move(roads);
}

void City::findAllPaths(std::vector<City*> currentPath)
{
	
	// Si on arrive à la fin
	if(currentPath.size() == 6)
	{
		if(currentPath.back() == currentPath[0]) allPath.emplace_back(currentPath);
	}

	//Init Current city
	City* currentCity = currentPath.back();
	
	// Si on est en cours de route 
	if(currentPath.size() < 6 && currentPath.size() > 1)
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
				findAllPaths(currentPathCopy);
			}

			if(currentPath.back() == currentRoads[i]->end)
			{
				std::vector<City*> currentPathCopy = currentPath;
				currentPathCopy.emplace_back(currentRoads[i]->start);
				findAllPaths(currentPathCopy);
			}
		}
	}
	if(currentPath.size() == 1)
	{
		vector<Road*> currentRoads = currentCity->getRoads();
		for(size_t i = 0; i<currentRoads.size(); i++)
		{
			if(currentPath.back() == currentRoads[i]->start)
			{
				std::vector<City*> currentPathCopy = currentPath;
				currentPathCopy.emplace_back(currentRoads[i]->end);
				findAllPaths(currentPathCopy);
			}

			if(currentPath.back() == currentRoads[i]->end)
			{
				std::vector<City*> currentPathCopy = currentPath;
				currentPathCopy.emplace_back(currentRoads[i]->start);
				findAllPaths(currentPathCopy);
			}
		}
	}
}

vector<Road*> City::getMinimumDistance()
{
	auto paths = transformCitiesInPath(getAllPath());
	vector<Road*> minimumPath;
	int minimumDistance = INT_MAX;
	for (size_t i = 0; i<paths.size(); i++)
	{
		int currentDistance = 0;
		for (size_t j = 0; j<paths[i].size(); j++)
		{
			currentDistance += paths[i][j]->length;
		}
		if (currentDistance<minimumDistance)
		{
			minimumDistance = currentDistance;
			minimumPath = paths[i];
		}
	}
	return minimumPath;
}

vector<vector<Road*>> City::transformCitiesInPath(vector<vector<City*>> citiesPath)
{
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

std::vector<Road*> City::findClosestPath()
{
	std::vector<City*> path;
	path.emplace_back(this);
	findAllPaths(path);

	transformCitiesInPath(getAllPath());
	auto minimumPath = getMinimumDistance();
	return minimumPath;
}

void City::printPath(vector<Road*> path)
{
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

vector<vector<City*>> City::allPath = vector<vector<City*>>();
