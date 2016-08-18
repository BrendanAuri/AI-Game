#pragma once
#include <vector>
#include "vector2.h"
#include "vector3.h"
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <string>
#include <list>
#include <memory>

using namespace std;

class Edge;

class Node
{
public:
	Vector3 myVec = Vector3(0, 0, 0); // x y and travelled bool
	bool traversed;
	std::vector<Edge *> edge;
	void addEdge(Edge * newEdge);
	Node(int x, int y, bool travelled);
	int costFromStart;
	Node * from;
	std::vector<Edge*> getPaths();
	void setVisited(bool v) { traversed = v; };
	bool isVisited() { return traversed; }


};

class Edge {
public:
	int cost;
	Node * from;
	Node * to;

	Edge(int p_cost, Node * p_from, Node * p_to);


	Node * getDest() const { return to; };
	int getCost() { return cost; }
	Node * getSource() const { return from; }
	void draw(SDL_Renderer * rend);

};

class Map {
public:
	vector<Node*> nodes;
	bool findNode(vector<Node*> vec, Node * node);
	Node* getNodeFromPos(Vector2 pos);
	vector<Node*> dijkstra(Node * from, Node * to);
	//~Map();
	Map();
};
