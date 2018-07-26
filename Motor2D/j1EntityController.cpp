#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "p2Animation.h"
#include "j1Scene.h"
#include "j1EntityController.h"
#include "Entity.h"

j1EntityController::j1EntityController() : j1Module()
{
	name.create("entity");
}

// Destructor
j1EntityController::~j1EntityController()
{}

// Called before render is available
bool j1EntityController::Awake(pugi::xml_node& conf)
{
	bool ret = true;



	return ret;
}

// Called before the first frame
bool j1EntityController::Start()
{

	return true;
}

// Update all guis
bool j1EntityController::PreUpdate(float dt)
{

	return true;
}

bool j1EntityController::Update(float dt)
{

	return true;
}
// Called after all Updates
bool j1EntityController::PostUpdate()
{
	BlitEntities();
	return true;
}

// Called before quitting
bool j1EntityController::CleanUp()
{
	
	return true;
}

void j1EntityController::AddPlayer(int x, int y)
{



}

Entity * j1EntityController::AddEnemy(EntityType type, int x, int y)
{
	Entity* ret = new Entity(type, x, y);
	
	entity_list.push_back(ret);
	return ret;
}

void j1EntityController::BlitEntities()
{
	for (std::list<Entity*>::iterator it = entity_list.begin(); it != entity_list.end(); it++)
	{
		
	}
	
}