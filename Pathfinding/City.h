#pragma once
#include <vector>
#include <string>

struct Road;

class City
{
public:
	
	City(std::string name);
	
	void setRoads(std::vector<Road*> roads);

	std::vector<City*> findClosestPath(City* endPoint);
	std::vector<Road*> getRoads(){return roads;}
	
private:
	std::string name;
	std::vector<Road*> roads;
};

struct Road {
	
	Road(int length, City* start, City* end) : length(length), start(start), end(end){}
	int length;
	City* start;
	City* end;
};