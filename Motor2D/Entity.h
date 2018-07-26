#pragma once
#include "Gui_Elements.h"
enum EntityType;
class Entity
{
public:
	Entity(){}
	Entity(EntityType name, int x, int y) 
	{
		this->x = x;
		this->y = y;
		type = name;
	}

	~Entity();

public:
	int x;
	int y;
	EntityType type;

};

