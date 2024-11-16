#pragma once
#include <vector>
#include <string>

struct Road;

class City
{
public:
	
	City(std::string name);
	
	void setRoads(std::vector<Road*> roads);
	void findAllPaths(std::vector<City*> currentPath);

	std::vector<Road*> getMinimumDistance();
	std::vector<std::vector<Road*>> transformCitiesInPath(std::vector<std::vector<City*>> citiesPath);
	std::vector<Road*> findClosestPath();
	std::vector<Road*> getRoads(){return roads;}

	std::vector<std::vector<City*>> getAllPath() { return allPath;}
	void printPath(std::vector<Road*> path);
	std::string getName() { return name; }

private:
	std::string name;
	std::vector<Road*> roads;

	static std::vector<std::vector<City*>> allPath;
};

struct Road {
	
	Road(int length, City* start, City* end) : length(length), start(start), end(end){}
	int length;
	City* start;
	City* end;
};