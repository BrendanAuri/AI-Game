#include "AI.h"
#include <list>
#include <iostream>
#include <algorithm>
#include "settings.h"

using namespace std;
Map map;

void Node::addEdge(Edge * newEdge)
{
	edge.push_back(newEdge);
};

Node::Node(int x, int y, bool travelled)
{
	this->myVec.x = (float)x;
	this->myVec.y = (float)y;
	this->traversed = travelled;
};


Edge::Edge(int p_cost, Node * p_from, Node * p_to)
{
	cost = p_cost;
	from = p_from;
	to = p_to;
};

void Edge::draw(SDL_Renderer * rend)
{
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 0);
	SDL_Rect rect;
	rect.x = ((int)from->myVec.x - 1);
	rect.y = ((int)from->myVec.y - 1);
	rect.h = 3;
	rect.w = 3;
	SDL_RenderDrawRect(rend, &rect);
};

void setUp(SDL_Renderer * rend) {
	map.nodes.resize(COLS);

	for (int x = 0; x < ROWS; x++) {
		for (int y = 0; y < ROWS; y++) {
			Node* np = new Node(x * 40, y * 40, 0);
			map.nodes[x].push_back(np);
		}
	}

	for (int x = 0; x < COLS; x++) {
		for (int y = 0; y < ROWS; y++) {
			if (x - 1 < 0 == false) {
				Edge * ep = new Edge(1, map.nodes[x][y], map.nodes[x - 1][y]);
				map.nodes[x][y]->addEdge(ep);
			}
			if (x + 1 >= COLS == false) {
				Edge * ep = new Edge(1, map.nodes[x][y], map.nodes[x + 1][y]);
				map.nodes[x][y]->addEdge(ep);
			}
			if (y - 1 < 0 == false) {
				Edge * ep = new Edge(1, map.nodes[x][y], map.nodes[x][y - 1]);
				map.nodes[x][y]->addEdge(ep);
			}

			if (y + 1 >= ROWS == false) {
				Edge * ep = new Edge(1, map.nodes[x][y], map.nodes[x][y + 1]);
				map.nodes[x][y]->addEdge(ep);
			}


			if (x - 1 < 0 == false && y - 1 < 0 == false) {
				Edge * ep = new Edge(1, map.nodes[x][y], map.nodes[x - 1][y - 1]);
				map.nodes[x][y]->addEdge(ep);
			}

			if (x + 1 >= COLS == false && y - 1 < 0 == false) {
				Edge * ep = new Edge(1, map.nodes[x][y], map.nodes[x + 1][y - 1]);
				map.nodes[x][y]->addEdge(ep);
			}

			if (x + 1 >= COLS == false && y + 1 >= ROWS == false) {
				Edge * ep = new Edge(1, map.nodes[x][y], map.nodes[x + 1][y + 1]);
				map.nodes[x][y]->addEdge(ep);
			}

			if (x - 1 < 0 == false && y + 1 >= ROWS == false) {
				Edge * ep = new Edge(1, map.nodes[x][y], map.nodes[x - 1][y + 1]);
				map.nodes[x][y]->addEdge(ep);
			}

		}
	}

};

bool compareG(Node * a, Node * b)
{
	return a->costFromStart < b->costFromStart;
};



bool Map::findNode(vector<Node*> vec, Node * node)
{
	bool result = false;

	for (int i = 0; i != vec.size(); i++) {
		if (vec[i] == node) {
			result = true;
		}
	}
	return result;
};



vector<Node*> Map::dijkstra(Node * from, Node * to)
{
	vector<Node*> openList;
	vector<Node*> closedList;

	openList.push_back(from);
	Node* currentNode = nullptr;

	while (openList.size() > 0) {
		std::sort(openList.begin(), openList.end(), compareG);
		currentNode = openList[0];
		if (currentNode == to) {
			break;
		}
		for (int i = 0; i != currentNode->edge.size(); i++) {
			Edge * connection = currentNode->edge[i];
			if (findNode(closedList, connection->to)) {
				continue;
			}
			int temp = currentNode->costFromStart + connection->getCost();
			if (findNode(openList, connection->to) == false) {
				openList.push_back(connection->to);

			}
			else if (temp >= connection->to->costFromStart) {
				continue;
			}
			connection->to->costFromStart = temp;
			connection->to->from = currentNode;
		}
		openList.erase(openList.begin());
		closedList.push_back(currentNode);
	}
	if (currentNode != to) {
		return vector<Node*>();
	}
	vector<Node*> path;

	while (currentNode != from) {
		path.push_back(currentNode);
		currentNode = currentNode->from;
	}
	std::reverse(path.begin(), path.end());
	return path;
};
