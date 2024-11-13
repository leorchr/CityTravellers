#include "City.h"
#include <iostream>
using namespace std;

City* A = new City("A");
City* B = new City("B");
City* C = new City("C");
City* D = new City("D");
City* E = new City("E");

Road* AB = new Road(2, A, B);
Road* AC = new Road(2,A,C);
Road* BC = new Road(3,B,C);
Road* BD = new Road(3,B,D);
Road* BE = new Road(1,B,E);
Road* CD = new Road(1,C,D);
Road* CE = new Road(3,C,E);
Road* DE = new Road(3,D,E);

std::vector<Road*> cityA = {AB, AC};
std::vector<Road*> cityB = {AB, BC, BD, BE};
std::vector<Road*> cityC = {AC, BC, CD, CE};
std::vector<Road*> cityD = {BD, CD, DE};
std::vector<Road*> cityE = {BE, CE, DE};


int main(int argc, char** argv) {
	std::cout << "Test" << std::endl;
	A->setRoads(cityA);
	B->setRoads(cityB);
	C->setRoads(cityC);
	D->setRoads(cityD);
	E->setRoads(cityE);
	A->findClosestPath(E);
	return 0;
}