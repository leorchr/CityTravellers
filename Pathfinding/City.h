#pragma once
#include <vector>
#include <string>

struct Road;

class City
{
public:
	
	City(std::string name);
	
	void setRoads(std::vector<Road*> roads);
	
	std::vector<Road*> findSmallestPath();
	void findAllCityPaths(std::vector<City*> currentPath);
	std::vector<std::vector<Road*>> changeCityListToRoads(std::vector<std::vector<City*>> citiesPath);
	std::vector<Road*> getSmallestPath(std::vector<std::vector<Road*>> availablePath);
	void printPath(std::vector<Road*> path);

	// Getters and setters
	std::vector<Road*> getRoads(){return roads;}
	std::vector<std::vector<City*>> getAllPath() { return allPath;}
	std::string getName() { return name; }

private:
	std::string name;
	std::vector<Road*> roads;
	std::vector<std::vector<City*>> allPath;
};

struct Road {
	
	Road(int length, City* start, City* end) : length(length), start(start), end(end){}
	int length;
	City* start;
	City* end;
};
