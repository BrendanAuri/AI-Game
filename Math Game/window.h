#pragma once
#include <SDL.h>
#include <fstream>
#include "objects.h"
#include "AI.h"

Map map;

using namespace std;

Object obj;
Object chl;
Object tile;
vector<Object> tiles;
SDL_Surface * objTex = IMG_Load("img/greendude.png");
SDL_Surface * tlsTex = IMG_Load("img/dirt.png");

//void saving() {
//	std::ofstream save("sav.bin", std::ios::out | ios::binary);
//	if (save.good()) {
//		save.write((char*)&obj.localSpace, sizeof(Matrix3));
//		save.write((char*)&chl.localSpace, sizeof(Matrix3));
//	}		
//	save.close();
//}
//
//void loading() {
//	std::ifstream load("sav.bin", std::ios::in | ios::binary);
//	if (load.good()) {
//		load.read((char*)&obj.localSpace, sizeof(Matrix3));
//		load.read((char*)&chl.localSpace, sizeof(Matrix3));
//	}	
//	load.close();
//}

class Window {
private:
	bool initialize();
	void update();
public:
	int mouseX, mousey;
	friend class Object;
	Window() {};
	Window(const char * windowName, int screenWidth, int screenHeight);
	const char * windowName;
	int screenWidth, screenHeight;
	SDL_Window * SDLWindow;
	SDL_Renderer * SDLRender;
	SDL_Surface* surface;
	void close();

	void create() {
		initialize();
		update();
	}
	void Draw(SDL_Renderer* renderer, SDL_Event* e);
};

bool Window::initialize() {
	if (SDL_Init(NULL) < 0) return false;

	SDLWindow = SDL_CreateWindow("Math Game", 20, 40, screenWidth, screenHeight, 0);

	if (SDLWindow == nullptr) return false;

	SDLRender = SDL_CreateRenderer(SDLWindow, 0, SDL_RENDERER_ACCELERATED);
	this->surface = SDL_GetWindowSurface(this->SDLWindow);
	if (tile.tex == nullptr) tile.tex = tile.loadTexture(SDLRender, tlsTex);

	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 12; y++) {
			tiles.push_back(tile);
		}
	}

	/*loading();*/

	return true;
}

void Window::update() {
	SDL_Event e;
	bool running = true;
	while(running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) { running = false; }
		}
		SDL_SetRenderDrawColor(this->SDLRender, 0, 0, 0, 0);
		SDL_RenderClear(SDLRender);
		Draw(SDLRender, &e);
		SDL_RenderPresent(SDLRender);
	}
}

Window::Window(const char * windowName, int screenWidth, int screenHeight) {
	this->windowName = windowName;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

void Window::close() {
	//saving();
	SDL_DestroyWindow(this->SDLWindow);
	if (SDLRender != nullptr) {
		SDL_DestroyRenderer(this->SDLRender);
	}
	if (obj.tex != nullptr) {
		SDL_DestroyTexture(obj.tex);
		obj.tex = nullptr;
	}
	if (chl.tex != nullptr) {
		SDL_DestroyTexture(obj.tex);
		chl.tex = nullptr;
	}
	SDL_Quit();
}


void move() {
	const Uint8 * keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W]) { obj.localSpace.m32 -= 0.05f; }
	if (keys[SDL_SCANCODE_S]) { obj.localSpace.m32 += 0.05f; }
	if (keys[SDL_SCANCODE_D]) { obj.localSpace.m31 += 0.05f; }
	if (keys[SDL_SCANCODE_A]) { obj.localSpace.m31 -= 0.05f; }
	if (keys[SDL_SCANCODE_Q]) {
		obj.angle -= 0.005f;
	}
	if (keys[SDL_SCANCODE_E]) {
		obj.angle += 0.005f;
	}

	if (keys[SDL_SCANCODE_UP]) { chl.localSpace.m32 -= 0.07f; }
	if (keys[SDL_SCANCODE_DOWN]) { chl.localSpace.m32 += 0.07f; }
	if (keys[SDL_SCANCODE_RIGHT]) { chl.localSpace.m31 += 0.07f; }
	if (keys[SDL_SCANCODE_LEFT]) { chl.localSpace.m31 -= 0.07f; }
};

void Window::Draw(SDL_Renderer* renderer, SDL_Event* e) {

	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 12; y++) {
			tiles[x + y].localSpace.m31 = x * 70;
			tiles[x + y].localSpace.m32 = y * 70;
			tiles[x + y].draw(SDLRender, tile.tex);
		}
	}

	if (obj.tex == nullptr) { obj.tex = obj.loadTexture(SDLRender, objTex); }
	//if (chl.tex == nullptr) { chl.tex = chl.loadTexture(SDLRender, chlTex); }

	//move();

	int start = 5;
	int goal = 50;

	obj.draw(this->SDLRender, obj.tex);
	//chl.draw(this->SDLRender, obj.tex);
	SDL_Rect rect = {0, 0, 9, 9};

	vector<Node*> path = map.dijkstra(map.nodes[start], map.nodes[goal]);
	obj.vecPos.x = map.nodes[start].x;
	obj.vecPos.y = map.nodes[start].y;

	for (int i = 0; i < map.nodes.size(); i++) {
		//map.nodes[i]->edge[0]->draw(renderer);
		for (int k = 0; k < path.size(); k++) {
			if (map.nodes[i]->myVec.x == path[k]->myVec.x && map.nodes[i]->myVec.y == path[k]->myVec.y) {
				rect.x = map.nodes[i]->myVec.x - 4;
				rect.y = map.nodes[i]->myVec.y - 4;
				SDL_RenderDrawRect(renderer, &rect);
			}
		}
		for (int j = 0; j != map.nodes[i]->edge.size(); j++) {
			SDL_RenderDrawLine(renderer, map.nodes[i]->myVec.x, map.nodes[i]->myVec.y, map.nodes[i]->edge[j]->to->myVec.x, map.nodes[i]->edge[j]->to->myVec.y);
		}
	}
}