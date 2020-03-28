#include "Dissolve.h"
#include "TransitionManager.h"

Dissolve::Dissolve(SCENES next_scene, float step_duration) : Transition(next_scene, step_duration)
{
	InitDissolve();
}

Dissolve::~Dissolve()
{

}

void Dissolve::StepTransition()
{	
	switch (step)
	{
	case TRANSITION_STEP::ENTERING:

		Entering();

		break;

	case TRANSITION_STEP::CHANGING:

		Changing(next_scene);

		break;

	case TRANSITION_STEP::EXITING:

		Exiting();

		break;
	}

	ApplyDissolve();
}

void Dissolve::Entering()
{
	//SDL_SetTextureAlphaMod(App->scene_manager->next_scene->tileset_texture, 0.0f);

	current_cutoff += GetCutoffRate(step_duration);

	if (current_cutoff <= MAX_CUTOFF)
	{
		current_cutoff = MAX_CUTOFF;

		step = TRANSITION_STEP::CHANGING;
	}
}

void Dissolve::Changing(SCENES next_scene)
{

}

void Dissolve::Exiting()
{

}

void Dissolve::ApplyDissolve()
{
	SDL_SetTextureAlphaMod(App->scene_manager->current_scene->tileset_texture, current_cutoff * 255.0f);
	SDL_SetTextureAlphaMod(App->scene_manager->next_scene->tileset_texture, current_cutoff * 255.0f);
}

void Dissolve::InitDissolve()
{
	App->scene_manager->LoadScene(next_scene);
	
	SDL_SetTextureAlphaMod(App->scene_manager->next_scene->tileset_texture, 0.0f);

	step = TRANSITION_STEP::ENTERING;
}