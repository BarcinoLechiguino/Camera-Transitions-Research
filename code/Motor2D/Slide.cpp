#include "Slide.h"
#include "TransitionManager.h"

Slide::Slide(SCENES next_scene, float step_duration, bool enter_from_left, Color slide_colour) : Transition(next_scene, step_duration)
, enter_from_left(enter_from_left)
, slide_colour(slide_colour)
{
	App->win->GetWindowRect(screen);

	step = TRANSITION_STEP::ENTERING;
}

Slide::~Slide()
{

}

void Slide::StepTransition()
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

	TranslateSlide();
}

void Slide::Entering()
{
	current_cutoff += GetCutoffRate(step_duration);

	if (current_cutoff >= MAX_CUTOFF)
	{
		current_cutoff = MAX_CUTOFF;

		step = TRANSITION_STEP::CHANGING;
	}
}

void Slide::Changing(SCENES next_scene)
{
	App->scene_manager->SwitchScene(next_scene);

	step = TRANSITION_STEP::EXITING;
}

void Slide::Exiting()
{
	current_cutoff -= GetCutoffRate(step_duration);

	if (current_cutoff <= MIN_CUTOFF)
	{
		current_cutoff = MIN_CUTOFF;
		
		step = TRANSITION_STEP::NONE;

		App->transition_manager->DeleteActiveTransition();
	}
}

void Slide::TranslateSlide()
{
	if (enter_from_left)
	{
		//screen.x = (-screen.w) + (current_cutoff * screen.w);
		screen.x = (-screen.w) + screen.w / current_cutoff;						// "Parabolic" slide

		//screen.x = Lerp(-screen.w, screen.w, current_cutoff);						
	}
	else
	{
		//screen.x = screen.w - (current_cutoff * screen.w);
		screen.x = (screen.w) - screen.w / current_cutoff;

		//screen.x = Lerp(screen.w, -screen.w, current_cutoff);
	}

	SDL_SetRenderDrawColor(App->render->renderer, slide_colour.r, slide_colour.g, slide_colour.b, 255);
	SDL_RenderFillRect(App->render->renderer, &screen);
}