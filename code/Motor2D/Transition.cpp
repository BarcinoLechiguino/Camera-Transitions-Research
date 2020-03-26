#include "Transition.h"
#include "Render.h"
#include "Textures.h"

Transition::Transition(SCENES next_scene, float step_duration, float current_cutoff) : 
	next_scene(next_scene), 
	step_duration(step_duration), 
	current_cutoff(current_cutoff),
	is_initialized(false),
	has_finished(false)
{

}

Transition::~Transition()
{

}

void Transition::Start()
{

}

void Transition::StepTransition(float dt)
{

}

void Transition::CleanUp()
{

}

void Transition::Entering(float dt)
{

}

void Transition::Changing(SCENES next_scene)
{
	//App->scene_manager->SwitchScene(next_scene);
}

void Transition::Exiting(float dt)
{

}

float Transition::Lerp(float start_time, float total_time, float dt)
{
	float increment = (total_time - start_time) * dt;

	return start_time + increment;
}

float Transition::GetCutoffRate(float dt, float time)
{
	cutoff_rate = dt * (1 / time);

	return cutoff_rate;
}

SDL_Texture* Transition::CreateTransitionTexture()
{
	App->win->GetWindowSize(win_width, win_height);
	
	uint r = 0x00ff0000;
	uint g = 0x0000ff00;
	uint b = 0x000000ff;
	uint a = 0xff000000;

	SDL_Surface* sur	= SDL_CreateRGBSurface(0, win_width, win_height, 32, r, g, b, a);

	SDL_Renderer* rend	= SDL_CreateSoftwareRenderer(sur);

	//SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	//SDL_RenderClear(rend);

	//SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, sur);

	SDL_Texture* load_tex = App->tex->Load("gui/atlas.png", rend);

	App->render->Blit(load_tex, 0, 0, NULL, rend);

	SDL_Texture* tex = SDL_CreateTextureFromSurface(App->render->renderer, sur);

	return load_tex;
}