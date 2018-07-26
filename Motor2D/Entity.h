#pragma once
#include "Gui_Elements.h"
enum EntityType;
class Entity
{
public:
	Entity(){}
	Entity(EntityType name, int x, int y) {}

	~Entity();

public:
	int position;
	int active;

};

