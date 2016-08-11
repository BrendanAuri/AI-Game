#pragma once

#include <SDL.h>
#include <SDL_scancode.h>
#include <SDL_events.h>
#include <SDL_image.h>
#include <vector2.h>
#include <vector3.h>
#include <vector4.h>
#include <matrix2.h>
#include <matrix3.h>
#include <matrix4.h>
#include <vector>
#include <fstream>
#include "settings.h"
#include<algorithm>

Matrix3 world;

class Object {
public:
	Vector3 vecPos;
	Vector3 vecRot;
	Vector3 vecScale;

	float angle;

	Matrix3 rotation;

	SDL_Texture* tex;
	char* texPath;
	Matrix3 localSpace;
	Matrix3 globalSpace;

	Object* parent;
	std::vector<Object*> children;

	SDL_Texture * loadTexture(SDL_Renderer * rend,SDL_Surface * texPath) {
		IMG_Init(IMG_INIT_PNG);
		SDL_Texture * temp;

		temp = SDL_CreateTextureFromSurface(rend, texPath);
		(float)vecScale.x = (float)texPath->w;
		(float)vecScale.y = (float)texPath->h;
		SDL_FreeSurface(texPath);
		return temp;
	}


	void draw(SDL_Renderer * rend,SDL_Texture * surf) {
		//if (tex == nullptr) { tex = loadTexture(rend,surf); }

		this->localSpace.setRotateZ(angle);

		if (parent == nullptr) {
			globalSpace = world * localSpace ;
		}
		else {
			globalSpace = parent->globalSpace * this->localSpace ;
		}

		SDL_Rect rect;
		rect.x = (int)globalSpace.m31;
		rect.y = (int)globalSpace.m32;
		rect.w = (int)vecScale.x;
		rect.h = (int)vecScale.y;

		SDL_RenderCopyEx(rend, tex, NULL, &rect, angle * 57.2958, NULL, SDL_FLIP_NONE);
	}
};

