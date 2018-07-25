#pragma once
#include "Gui_Elements.h"
enum EntityType;
class Entity
{
public:

	Entity(EntityType name, int x, int y, const SDL_Rect collider, bool active, j1Module* callback) {}

	~Entity();

public:
	int position;
	int active;

};

