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


// Exercice 1

#include <bitset>

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

#include <unordered_map>

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

#include <unordered_map>

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

#include <cmath>
#include <climits>

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