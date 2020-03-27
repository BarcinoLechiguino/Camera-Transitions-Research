#include "Wipe.h"
#include "SceneManager.h"
#include "j1App.h"
#include "Render.h"
#include "Window.h"
#include "p2Log.h"


Wipe::Wipe(float transition_time, bool is_scene_change, int scene_to_change, Color color) : Transition(transition_time)
{
	this->is_scene_change = is_scene_change;
	this->scene_to_change = scene_to_change;
	this->color = color;

	App->win->GetWindowSize(width, height);
	rect = { -(int)width, 0, (int)width, (int)height };
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
}

Wipe::~Wipe()
{
}

void Wipe::Entering()
{
	Transition::Entering();

	//TODO 02
	//Save the current interpolation value in a local variable. Use the LerpValue() method.
	//The rect must cover the whole screen, so make sure the new value is not bigger than 0.
	//Assign the value to the x variable of the rect. 
	//Remember to draw the rect.
	int current_lerp_value = LerpValue(percent, current_time->ReadSec(), transition_time);

	rect.x = current_lerp_value;

	DrawRect();
}

void Wipe::Action()
{
	Transition::Action();

	//TODO 03
	//Its's time to make the scene change. Remember to check whether or not this is a scene change transition.
	//Remember to draw the rect.
}

void Wipe::Exiting()
{
	//TODO 04
	//Pretty similar to the Entering() method, but reversed.
}

void Wipe::SetColor(Color color)
{
	this->color = color;
}

void Wipe::DrawRect()
{
	//TODO 01
	//FIll the DrawRect() method by setting a render draw color and telling the render to fill the rect.
	//Remember to use the color and rect variables.
	SDL_SetRenderDrawColor(App->render->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(App->render->renderer, &rect);

}
