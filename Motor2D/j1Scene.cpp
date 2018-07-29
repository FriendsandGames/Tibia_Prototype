#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Fonts.h"
#include "j1Window.h"
#include "j1SceneGui.h"
#include "j1EntityController.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	
	if(App->map->Load("map1.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}
	debug_tex = App->tex->Load("maps/path.png");

	player_texture = App->tex->Load("Assets/Footman_Spritesheet.png");

	App->entity->AddEnemy(GRUNT, 100, 100);

	


	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}


	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if (App->scene_gui->startgameaction == true)
	{
		App->map->Draw();
	}
	App->map->Draw();

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		if (isDebuggin == false)
		{
			isDebuggin = true;
		}
		else
		{
			isDebuggin = false;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");


	PlayerMovementInputs();
	App->entity->BlitEntities();
	CameraMovement(dt);

	

	int x, y;
	App->input->GetMousePosition(x, y);
	x = x * 2;
	y = y * 2;
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					x, y);

	App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	int x2 = 0;
	int y2 = 0;
	App->input->GetMousePosition(x2, y2);
	iPoint p = App->render->ScreenToWorld(x2, y2);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y,(const SDL_Rect *)0,2.0f);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y,(const SDL_Rect *)0);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	App->tex->CleanUp();
	return true;
}

void j1Scene::PlayerMovementInputs()
{


	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && player_moving_s == false && player_moving_e == false && player_moving_w == false || player_moving_n == true )
	{
		if (player_y >=  original_y - App->map->data.tile_height)
		{
			player_y = player_y - 3;
			player_moving_n = true;
		}
		else
		{
			player_moving_n = false;
			original_y = player_y;
		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && player_moving_e == false && player_moving_n == false && player_moving_s == false || player_moving_w == true )
	{
		if (player_x >= original_x - App->map->data.tile_width)
		{
			player_x = player_x - 3;
			player_moving_w = true;
		}
		else
		{
			player_moving_w = false;
			original_x = player_x;
		}
	}		
	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && player_moving_n == false && player_moving_e == false && player_moving_w == false || player_moving_s == true )
	{
		if (player_y >= original_y + App->map->data.tile_height)
		{
			player_y = player_y + 3;
			player_moving_s = true;
		}
		else
		{
			player_moving_s = false;
			original_y = player_y;
		}
	}		
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && player_moving_n == false && player_moving_s == false && player_moving_w == false || player_moving_e == true )
	{
		if (player_x >= original_x + App->map->data.tile_width)
		{
			player_x = player_x + 3;
			player_moving_e = true;
		}
		else
		{
			player_moving_e = false; 
			original_x = player_x;
		}
	}
	else
	{
		original_y = player_y;
		original_x = player_x;
		player_moving_e = false;
		player_moving_s = false;
		player_moving_w = false;
		player_moving_n = false;
	}
		

	SDL_Rect rect = { 317, 10, App->map->data.tile_width * 2, App->map->data.tile_height * 2 };

	App->render->Blit(player_texture, player_x - App->map->data.tile_width / 12, player_y- App->map->data.tile_height/4, &rect, 2.0f);
}

void j1Scene::CameraMovement(float dt)
{
	if (isDebuggin)
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			App->render->camera.y += floor(2000.0f * dt);

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			App->render->camera.y -= floor(2000.0f * dt);

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			App->render->camera.x += floor(2000.0f * dt);

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			App->render->camera.x -= floor(2000.0f * dt);
	}
	else
	{
		App->render->camera.x = -player_x * 2 + App->render->camera.w/2;
		App->render->camera.y = -player_y * 2 + App->render->camera.h/2;
	}
	
	


}
