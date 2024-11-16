#include "City.h"
#include <iostream>
#include <bitset>
#include <unordered_map>
#include <cmath>
#include <climits>
using namespace std;

vector<City*> cities;
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

void init();
int solution1(int N);
vector<int> solution2(vector<int> &A, int K);
int solution3(vector<int> &A);
int solution4(int X, int Y, int D);
int solution5(vector<int> &A);
int solution6(vector<int> &A);
void printIntVector(vector<int> vectorToPrint);


int main(int argc, char** argv) {

	// Travelling salesman problem
	cout<< "\nTravelling salesman problem : \n\n";
	init();
	for (size_t i = 0; i<cities.size(); i++)
	{
		cout<< "Smallest path from city " << cities[i]->getName() << "\n";
		std::vector<Road*> path = cities[i]->findSmallestPath();
		cities[i]->printPath(path);
		cout << "\n";
	}

	// Codility n1
	cout<<"\nCodility n1\n";
	int answer1 = solution1(1041);
	cout<<"The length of the longest binary gap of 1041 is : "<<answer1<<"\n";

	// Codility n2
	cout<<"\nCodility n2\n";
	vector<int> vector2{3, 8, 9, 7, 6};
	cout<<"The vector : ";
	printIntVector(vector2);
	cout<<" rotated 3 times gives : ";
	printIntVector(solution2(vector2, 3));

	// Codility n3
	cout<<"\n\nCodility n3\n";
	std::vector<int> vector3{9, 3, 9, 3, 9, 7, 9};
	cout<<"The unpaired element of the vector ";
	printIntVector(vector3);
	int answer3 = solution3(vector3);
	cout << " is " << answer3;

	// Codility n4
	cout<<"\n\nCodility n4\n";
	int answer4 = solution4(10,85,30);
	cout << "The minimal number of jumps from position 10 to a position equal to \nor greater than 85 with 30 per jump is : "<< answer4;

	// Codility n5
	cout<<"\n\nCodility n5\n";
	std::vector<int> vector5{2, 3, 1, 5};
	cout<<"The missing element of the array ";
	printIntVector(vector5);
	int answer5 = solution5(vector5);
	cout << " is "<< answer5;

	// Codility n6
	cout<<"\n\nCodility n6\n";
	std::vector<int> vector6{3, 1, 2, 4, 3};
	cout<<"The minimal difference of the non-empty array ";
	printIntVector(vector6);
	int answer6 = solution6(vector6);
	cout<<" is " << answer6 << "\n";
}

void init()
{
	A->setRoads(cityA);
	B->setRoads(cityB);
	C->setRoads(cityC);
	D->setRoads(cityD);
	E->setRoads(cityE);
	cities.emplace_back(A);
	cities.emplace_back(B);
	cities.emplace_back(C);
	cities.emplace_back(D);
	cities.emplace_back(E);
}

// Exercice 1

int solution1(int N) {
	std::bitset<64> bit(N);
	int current0 = 0;
	int max0 = 0;
	bool first1 = false;
	for(int i = 0; i<bit.size(); i++) {
		if(first1){
			if(bit[i] == 0){
				current0++;
			}
			if(bit[i] == 1){
				if(current0> max0) max0 = current0;
				current0 = 0;
			}
		}
		else{
			if(bit[i] == 1) first1 = true;
		}
	}
	return max0;
}

// Exercice 2

vector<int> solution2(vector<int> &A, int K) {
	vector<int> results(A.size());
	for(int i = 0; i<A.size(); i++){
		results[(i+K)%A.size()] = A[i];
	}
	return results;
}

// Exercice 3

int solution3(vector<int> &A) {
	std::unordered_map<int, int> answer;
	for(int i = 0; i<A.size(); i++){
		answer[A[i]]++;
	}
	for(auto& it: answer){
		if(it.second%2 == 1) return it.first;
	}
	return 0;
}

// Exercice 4

int solution4(int X, int Y, int D) {
	double answer = (Y-X)/D;
	if(X+answer*D < Y) answer++;
	return answer;
}

// Exercice 5

int solution5(vector<int> &A) {
	std::unordered_map<int, bool> answer;

	for(int i = 0; i<A.size(); i++){
		answer[i+1] = false;
	}
	answer[A.size()+1] = false;

	for(int i = 0; i<A.size(); i++){
		answer[A[i]] = true;
	}
	for(auto& it : answer){
		if(!it.second) return it.first;
	}
	return 0;
}

// Exercice 6

int solution6(vector<int> &A) {
	vector<int> sum(A.size());
	vector<int> invSum(A.size());

	// Store sum in ascending order
	int tempSum = 0;
	for(size_t i = 0; i<A.size(); i++){
		tempSum += A[i];
		sum[i] = tempSum;
	}

	// Store sum in descending order
	tempSum = 0;
	for(size_t i = 0; i<A.size(); i++){
		tempSum += A[A.size()-1-i];
		invSum[A.size()-1-i] = tempSum;
	}

	// Check lowest absolute sums
	int currentLowest = INT_MAX;
	int tempAnswer = 0;
	for(size_t i = 0; i<sum.size()-1; i++){
		tempAnswer = abs(sum[i]-invSum[i+1]);
		if(tempAnswer < currentLowest) currentLowest = tempAnswer;
	}
	return currentLowest;
}

void printIntVector(vector<int> vectorToPrint)
{
	cout<<"[";
	for (size_t i = 0; i < vectorToPrint.size(); ++i) {
		if (i==0) cout << vectorToPrint[i];
		else cout << " " << vectorToPrint[i];
	}
	cout<<"]";
}
