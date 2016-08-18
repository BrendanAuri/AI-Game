#include "AI.h"
#include <list>
#include <iostream>
#include <algorithm>
#include "settings.h"
void Node::addEdge(Edge * newEdge)
{
	edge.push_back(newEdge);
};

Node::Node(int x, int y, bool travelled)
{
	this->myVec.x = (float)x;
	this->myVec.y = (float)y;
	this->traversed = travelled;
}
vector<Edge*> Node::getPaths()
{
	return this->edge;
}


Edge::Edge(int p_cost, Node * p_from, Node * p_to)
{
	cost = p_cost;
	from = p_from;
	to = p_to;
}

void Edge::draw(SDL_Renderer * rend)
{
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 0);
	SDL_RenderDrawLine(rend, (int)this->from->myVec.x, (int)this->from->myVec.y, (int)this->to->myVec.x, (int)this->to->myVec.y);
}

bool Map::findNode(vector<Node*> vec, Node * node)
{
	bool result = false;

	for (int i = 0; i != vec.size(); i++) {
		if (vec[i] == node) {
			result = true;
		}
	}
	return result;
}
Node * Map::getNodeFromPos(Vector2 pos) {
	for (unsigned int i = 0; i < nodes.size(); i++) {
		if (this->nodes[i]->myVec.x == pos.x && this->nodes[i]->myVec.y == pos.y) {
			return nodes[i];
		}
	}

	return nullptr;
}

Map::Map() {
	//this->nodes.resize(COLS * ROWS);

	for (unsigned int x = 0; x < COLS; x++) {
		for (unsigned int y = 0; y < ROWS; y++) {
			if(!(y == x * x  + 3 || x == y * y + 3 || x == y % 10))
				this->nodes.push_back(new Node(OFFSET + x * UNIT, OFFSET + y * UNIT, 0));
		}
	}

	for (unsigned int i = 0; i < nodes.size(); i++){
		if (getNodeFromPos(Vector2(this->nodes[i]->myVec.x + UNIT, this->nodes[i]->myVec.y)) != nullptr) {
			this->nodes[i]->addEdge(new Edge(UNIT, this->nodes[i], getNodeFromPos(Vector2(this->nodes[i]->myVec.x + UNIT, this->nodes[i]->myVec.y))));
		}
		if (getNodeFromPos(Vector2(this->nodes[i]->myVec.x - UNIT, this->nodes[i]->myVec.y)) != nullptr) {
			this->nodes[i]->addEdge(new Edge(UNIT, this->nodes[i], getNodeFromPos(Vector2(this->nodes[i]->myVec.x - UNIT, this->nodes[i]->myVec.y))));
		}
		if (getNodeFromPos(Vector2(this->nodes[i]->myVec.x, this->nodes[i]->myVec.y + UNIT)) != nullptr) {
			this->nodes[i]->addEdge(new Edge(UNIT, this->nodes[i], getNodeFromPos(Vector2(this->nodes[i]->myVec.x, this->nodes[i]->myVec.y + UNIT))));
		}
		if (getNodeFromPos(Vector2(this->nodes[i]->myVec.x, this->nodes[i]->myVec.y - UNIT)) != nullptr) {
			this->nodes[i]->addEdge(new Edge(UNIT, this->nodes[i], getNodeFromPos(Vector2(this->nodes[i]->myVec.x, this->nodes[i]->myVec.y - UNIT))));
		}
	}
};

bool compareG(Node * a, Node * b)
{
	return a->costFromStart < b->costFromStart;
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
		for (unsigned int i = 0; i != currentNode->edge.size(); i++) {
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
}
