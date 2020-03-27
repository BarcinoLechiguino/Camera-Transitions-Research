#include "Wipe.h"
#include "TransitionManager.h"

Wipe::Wipe(SCENES next_scene, float step_duration, bool enter_from_left, Color wipe_colour) : Transition(next_scene, step_duration)
, enter_from_left(enter_from_left)
, wipe_colour(wipe_colour)
{
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

	App->win->GetWindowRect(screen);

	step = TRANSITION_STEP::ENTERING;
}

Wipe::~Wipe()
{

}

void Wipe::StepTransition()
{
	current_cutoff += GetCutoffRate(step_duration);
	
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

	TranslateWipe();
}

void Wipe::Entering()
{
	if (current_cutoff >= MAX_CUTOFF)
	{
		current_cutoff = MIN_CUTOFF;

		step = TRANSITION_STEP::CHANGING;
	}

	/*current_cutoff += GetCutoffRate(step_duration);

	if (current_cutoff >= MAX_CUTOFF)
	{
		current_cutoff = MAX_CUTOFF;

		step = TRANSITION_STEP::CHANGING;
	}*/
}

void Wipe::Changing(SCENES next_scene)
{
	App->scene_manager->SwitchScene(next_scene);

	step = TRANSITION_STEP::EXITING;
}

void Wipe::Exiting()
{					
	//current_cutoff += GetCutoffRate(step_duration);					//Doubles the cutoff. Makes for a speedy exit.	// Notice that, exiting in this case increases cutoff too.
																														// This was modified to make TranslateWipe() easier to understand.
	if (current_cutoff >= MAX_CUTOFF)
	{
		current_cutoff = MIN_CUTOFF;

		App->transition_manager->DeleteActiveTransition();

		step = TRANSITION_STEP::NONE;
	}

	/*current_cutoff -= GetCutoffRate(step_duration);
	
	if (current_cutoff <= MIN_CUTOFF)
	{
		current_cutoff = MIN_CUTOFF;

		App->transition_manager->DeleteActiveTransition();

		step = TRANSITION_STEP::NONE;
	}*/
}

void Wipe::TranslateWipe()
{
	if (enter_from_left)
	{	
		if (step == TRANSITION_STEP::ENTERING)
		{	
			//screen.x = (-screen.w) + screen.w * current_cutoff;
			
			screen.x = Lerp(-screen.w, 0, current_cutoff);
		}
		
		if (step == TRANSITION_STEP::EXITING)
		{
			//screen.x = screen.w * current_cutoff;
			
			//screen.x = Lerp(screen.w, 0, current_cutoff);
			
			screen.x = Lerp(0, screen.w, current_cutoff);
		}
	}
	else
	{
		if (step == TRANSITION_STEP::ENTERING)
		{
			//screen.x = screen.w - screen.w * current_cutoff;
			
			screen.x = Lerp(screen.w, 0, current_cutoff);
		}

		if (step == TRANSITION_STEP::EXITING)
		{
			//screen.x = -screen.w * current_cutoff;
			
			//screen.x = Lerp(-screen.w, 0, current_cutoff);
			
			screen.x = Lerp(0, -screen.w, current_cutoff);
		}
	}


	
	/*if (enter_from_left)															// Only works with cutoff rate going from 0.0f to 1.0f and then from 1.0f to 0.0f.
	{
		if (step == TRANSITION_STEP::ENTERING)
		{
			screen.x = (screen.w) - screen.w / current_cutoff;
		}

		if (step == TRANSITION_STEP::EXITING)
		{
			screen.x = (-screen.w) + screen.w / current_cutoff;
		}
	}
	else
	{
		if (step == TRANSITION_STEP::ENTERING)
		{
			screen.x = (screen.w) - screen.w / current_cutoff;
		}

		if (step == TRANSITION_STEP::EXITING)
		{
			screen.x = (-screen.w) + screen.w / current_cutoff;
		}
	}*/


	SDL_SetRenderDrawColor(App->render->renderer, wipe_colour.r, wipe_colour.g, wipe_colour.b, 255);
	SDL_RenderFillRect(App->render->renderer, &screen);

	LOG("screen.x = %d", screen.x);
}