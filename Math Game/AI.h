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

class Edge;
class Node;

class Map {
public:
	vector<vector<Node*>> nodes;
	vector<Node*>  dijkstra(Node * from, Node * to);
	//~Map();
	bool findNode(vector<Node*> vec, Node * node);
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

class  Node
{
public:
	Vector2 myVec; // x y and travelled bool
	bool traversed;
	vector<Edge *> edge;
	void addEdge(Edge * newEdge);
	Node(int x, int y, bool travelled);
	int costFromStart;
	Node * from;
	vector<Edge*> getPaths() { return edge; };
	void setVisited(bool v) { traversed = v; };
	bool isVisited() { return traversed; }


};


extern Map map;

extern void setUp(SDL_Renderer * rend);

