#include "Slide.h"
#include "TransitionManager.h"

Slide::Slide(SCENES next_scene, float step_duration, bool non_lerp, bool enter_from_left, Color slide_colour) : Transition(next_scene, step_duration, non_lerp)
, enter_from_left(enter_from_left)
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
		if (!non_lerp)
		{
			screen.x = Lerp(-screen.w, 0, current_cutoff);
		}
		else
		{
			//screen.x = N_Lerp(-screen.w, 0, current_cutoff, true);
			screen.x = N_Lerp(0, -screen.w, current_cutoff);
		}
	}
	else
	{
		if (!non_lerp)
		{
			screen.x = Lerp(screen.w, 0, current_cutoff);
		}
		else
		{
			//screen.x = N_Lerp(screen.w, 0, current_cutoff, true);
			screen.x = N_Lerp(0, screen.w, current_cutoff);
		}
	}

	DrawSlide();
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