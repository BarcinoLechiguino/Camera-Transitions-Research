#include "FadeToColour.h"
#include "TransitionManager.h"

FadeToColour::FadeToColour(SCENES scene_name, float step_duration, Color fade_colour) : Transition(scene_name, step_duration)
{
	GetScreenRect(screen);
	this->fade_colour = fade_colour;

	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

	step = TRANSITION_STEP::ENTERING;
}

FadeToColour::~FadeToColour()
{

}

void FadeToColour::StepTransition(float dt)
{
	switch (step)
	{
	case TRANSITION_STEP::ENTERING:
		
		Entering(dt);
		
		break;

	case TRANSITION_STEP::CHANGING:

		Changing(next_scene);

		break;

	case TRANSITION_STEP::EXITING:
		
		Exiting(dt);
		
		break;
	}

	ApplyFade();
}

void FadeToColour::Entering(float dt)
{
	current_cutoff += GetCutoffRate(dt, step_duration);

	if (current_cutoff >= MAX_CUTOFF)
	{
		current_cutoff = MAX_CUTOFF;

		step = TRANSITION_STEP::CHANGING;
	}
}

void FadeToColour::Changing(SCENES next_scene)
{
	App->scene_manager->SwitchScene(next_scene);

	step = TRANSITION_STEP::EXITING;
}

void FadeToColour::Exiting(float dt)
{
	current_cutoff -= GetCutoffRate(dt, step_duration);

	LOG("Cutoff Rate: %f", GetCutoffRate(dt, step_duration));

	if (current_cutoff <= MIN_CUTOFF)
	{
		current_cutoff = MIN_CUTOFF;

		has_finished = true;

		step = TRANSITION_STEP::NONE;

		App->transition_manager->DeleteActiveTransition();
	}
}

void FadeToColour::ApplyFade()
{
	SDL_SetRenderDrawColor(App->render->renderer, fade_colour.r, fade_colour.g, fade_colour.b, current_cutoff * 255.0f);

	SDL_RenderFillRect(App->render->renderer, &screen);
}

void FadeToColour::GetScreenRect(SDL_Rect& rect)
{
	int win_width	= 0;
	int win_height = 0;

	App->win->GetWindowSize(win_width, win_height);

	rect = { 0, 0, win_width, win_height };
}