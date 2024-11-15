#pragma once
#include <vector>
#include <string>

struct Road;

class City
{
public:
	
	City(std::string name);
	
	void setRoads(std::vector<Road*> roads);
	std::vector<City*> getAllPaths(City* endPoint, std::vector<City*> currentPath);

	std::vector<City*> findClosestPath(City* endPoint);
	std::vector<Road*> getRoads(){return roads;}
	
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