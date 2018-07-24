#ifndef __j1ENTITYCONTROLLER_H__
#define __j1ENTITYCONTROLLER_H__

#include "j1Module.h"
#include <list>
#include "SDL_ttf\include\SDL_ttf.h"
#include "PugiXml\src\pugixml.hpp"
#include "j1Scene.h"
#include "p2Point.h"

// TODO 1: Create your structure of classes
struct SDL_Texture;
struct SDL_Rect;
class Entity;
// ---------------------------------------------------
class j1EntityController : public j1Module
{
public:

	j1EntityController();

	// Destructor
	virtual ~j1EntityController();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate(float dt);

	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


	// Entity creation functions


	void BlitEntities();
	
};

#endif 