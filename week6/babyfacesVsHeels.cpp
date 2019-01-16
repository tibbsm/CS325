#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

class Vertex {
	
public:
	std::string name, baby_heel, color;
	std::vector<Vertex> neighbors;
	int distance;

	Vertex(std::string n);
	void addNeighbor(Vertex v);

};

Vertex::Vertex(std::string n){
	name = n;
	std::string babyHeel;
	std::vector<std::string> neighbors;
	int distance = INT_MAX;
	std::string color = "WHITE";
};

void Vertex::addNeighbor(Vertex v){
	neighbors.push_back(v);
};

class Graph
{
public:
	Graph();
	~Graph();
	
};

int main(int argc, const char * argv[]) {

	Vertex v("A");
	std::cout << v.name << std::endl;


	return 0;
}
