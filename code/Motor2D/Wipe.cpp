#include "Wipe.h"
#include "TransitionManager.h"

Wipe::Wipe(SCENES next_scene, float step_duration, bool non_lerp, bool enter_from_left, Color wipe_colour) : Transition(next_scene, step_duration, non_lerp)
, enter_from_left(enter_from_left)
, wipe_colour(wipe_colour)
{
	InitWipe();
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
}

void Wipe::Changing(SCENES next_scene)
{
	App->scene_manager->SwitchScene(next_scene);

	step = TRANSITION_STEP::EXITING;
}

void Wipe::Exiting()
{					
	if (current_cutoff >= MAX_CUTOFF)
	{
		current_cutoff = MIN_CUTOFF;
		
		step = TRANSITION_STEP::NONE;

		App->transition_manager->DeleteActiveTransition();
	}
}

void Wipe::TranslateWipe()
{
	if (enter_from_left)
	{	
		if (step == TRANSITION_STEP::ENTERING)
		{			
			if (!non_lerp)
			{
				screen.x = Lerp(-screen.w, 0, current_cutoff);
			}
			else
			{
				//screen.x = N_Lerp(-screen.w, 0, current_cutoff, true);
				screen.x = N_Lerp(-screen.w, 0, current_cutoff);
			}
		}
		
		if (step == TRANSITION_STEP::EXITING)
		{
			if (!non_lerp)
			{
				screen.x = Lerp(0, screen.w, current_cutoff);
			}
			else
			{
				//screen.x = N_Lerp(0, screen.w, current_cutoff, true);
				screen.x = N_Lerp(0, screen.w, current_cutoff);
			}
		}
	}
	else
	{
		if (step == TRANSITION_STEP::ENTERING)
		{
			if (!non_lerp)
			{
				screen.x = Lerp(screen.w, 0, current_cutoff);
			}
			else
			{
				//screen.x = N_Lerp(screen.w, 0, current_cutoff, true);
				screen.x = N_Lerp(screen.w, 0, current_cutoff);
			}
		}

		if (step == TRANSITION_STEP::EXITING)
		{
			if (!non_lerp)
			{
				screen.x = Lerp(0, -screen.w, current_cutoff);
			}
			else
			{
				//screen.x = N_Lerp(0, -screen.w, current_cutoff, true);
				screen.x = N_Lerp(0, -screen.w, current_cutoff);
			}
		}
	}

	DrawWipe();
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