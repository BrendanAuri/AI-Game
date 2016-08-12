#include <SDL.h>
#include <SDL_scancode.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector2.h>
#include <vector3.h>
#include <vector4.h>
#include <matrix2.h>
#include <matrix3.h>
#include <matrix4.h>
#include <iostream>
#include "window.h"
#include "objects.h"
#include <fstream>
#include "settings.h"
#include "AI.h"


using namespace std;
	
using std::cout;
using std::endl;
using std::string;


int main(int argc, char* args[])
{
	Window window("Math Game", SCREEN_WIDTH, SCREEN_HEIGHT);

	//chl.localSpace.m31 = 100;
	//obj.children.push_back(&chl);
	//chl.parent = &obj;

	window.create();
	window.close();

	//close();
	return 0;
};

