#include "Slide.h"
#include "TransitionManager.h"

Slide::Slide(SCENES next_scene, float step_duration, bool non_lerp, bool vertical, bool slide_from_right, bool slide_from_bottom, Color slide_colour)
	: Transition(next_scene, step_duration, non_lerp)
	, vertical(vertical)
	, slide_from_right(slide_from_right)
	, slide_from_bottom(slide_from_bottom)
	, slide_colour(slide_colour)
{
	InitSlide();
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

		Changing();

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

void Slide::Changing()
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
	if (!vertical)
	{
		HorizontalSlide();
	}
	else
	{
		VerticalSlide();
	}

	DrawSlide();
}

void Slide::HorizontalSlide()
{	
	// TODO 9A: The Slide transition is a rect that comes from one side, reaches the other, and returns to where it came from.
	// Make use of either of the interpolation functions used in the previous TODO to recreate that effect.
	// Tip: There already exists a screen rect variable. Current_cutoff still goes from 0 to 1 to 0 through the whole transition.
	
	if (!slide_from_right)
	{

	}
	else
	{

	}

}

void Slide::VerticalSlide()
{
	// TODO 9B: Very similar to its A counterpart
	// Instead of manipulating the x of the screen rect, the y is manupulated instead.
	// Think about which parameter of the screen use for the Lerp() or N_Lerp().
	
	if (!slide_from_bottom)
	{

	}
	else
	{

	}
}

void Slide::DrawSlide()
{
	SDL_SetRenderDrawColor(App->render->renderer, slide_colour.r, slide_colour.g, slide_colour.b, 255);
	SDL_RenderFillRect(App->render->renderer, &screen);
}

void Slide::InitSlide()
{
	App->win->GetWindowRect(screen);

	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

	step = TRANSITION_STEP::ENTERING;
}