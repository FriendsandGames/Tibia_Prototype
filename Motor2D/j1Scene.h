#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "j1Map.h"

struct SDL_Texture;
class GuiImage;
class GuiText;
struct _TTF_Font;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void PlayerMovementInputs();

	void CameraMovement(float dt);

private:
	SDL_Texture*		debug_tex;
	GuiImage*			banner;
	GuiText*			text;
	SDL_Texture*		player_texture;

	int					player_x = 0;
	int					player_y = 0;

private:
	_TTF_Font*			Font;

public:
	int					score;
	p2SString			display_score;

	p2SString			display_floating_score;
	bool				isDebuggin = false;
	int					original_y, original_x;
	bool				player_moving_n = false;
	bool				player_moving_s = false;
	bool				player_moving_e = false;
	bool				player_moving_w = false;




	
};

#endif // __j1SCENE_H__