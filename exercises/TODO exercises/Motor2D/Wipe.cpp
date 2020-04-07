#include "Wipe.h"
#include "TransitionManager.h"

Wipe::Wipe(SCENES next_scene, float step_duration, bool non_lerp, bool vertical, bool wipe_from_right, bool wipe_from_bottom, Color wipe_colour) 
	: Transition(next_scene, step_duration, non_lerp)
	, vertical(vertical)
	, wipe_from_right(wipe_from_right)
	, wipe_from_bottom(wipe_from_bottom)
	, wipe_colour(wipe_colour)
{
	InitWipe();
}

Wipe::~Wipe()
{

}

void Wipe::StepTransition()
{
	// TODO 10: Check what is different in this update loop 
	// from the others you have seen so far.
	
	current_cutoff += GetCutoffRate(step_duration);
	
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

	TranslateWipe();
}

void Wipe::Entering()
{
	//  TODO 10: Check what is different in this Entering() method
	// from the ones that you have previously seen.
	
	if (current_cutoff >= MAX_CUTOFF)
	{
		current_cutoff = MIN_CUTOFF;

		step = TRANSITION_STEP::CHANGING;
	}
}

void Wipe::Changing()
{
	App->scene_manager->SwitchScene(next_scene);

	step = TRANSITION_STEP::EXITING;
}

void Wipe::Exiting()
{					
	//  TODO 10: Check what is different in this Exiting() method
	// from the ones that you have previously seen.
	
	if (current_cutoff >= MAX_CUTOFF)
	{
		current_cutoff = MIN_CUTOFF;
		
		step = TRANSITION_STEP::NONE;

		App->transition_manager->DeleteActiveTransition();
	}
}

void Wipe::TranslateWipe()
{
	if (!vertical)
	{
		HorizontalWipe();
	}
	else
	{
		VerticalWipe();
	}

	DrawWipe();
}

void Wipe::HorizontalWipe()
{
	// TODO 10A: Recreate the wipe effect by making the screen rect cross from either of both sides to the other using Lerp() or N_Lerp().
	// To make the rect cross the screen, the transition needs to be broken down into two steps using the transition steps.
	// Tip: Be careful with current_step. It will range from 0 to 1 differently from other transitions.
	 
	
	if (!wipe_from_right)
	{
		if (step == TRANSITION_STEP::ENTERING)
		{

		}
		
		if (step == TRANSITION_STEP::EXITING)
		{

		}
	}
	else
	{
		if (step == TRANSITION_STEP::ENTERING)
		{

		}

		if (step == TRANSITION_STEP::EXITING)
		{

		}
	}
}

void Wipe::VerticalWipe()
{
	// TODO 10B: Again, similar to it's horizontal counterpart, but taking into account that
	// the wipe will happen from top to bottom and from bottom to top.
	// Now you have to code the step breakdown yourself.

	if (!wipe_from_bottom)
	{

	}
	else
	{

	}
}

void Wipe::DrawWipe()
{
	SDL_SetRenderDrawColor(App->render->renderer, wipe_colour.r, wipe_colour.g, wipe_colour.b, 255);
	SDL_RenderFillRect(App->render->renderer, &screen);
}

void Wipe::InitWipe()
{
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

	App->win->GetWindowRect(screen);

	step = TRANSITION_STEP::ENTERING;
}