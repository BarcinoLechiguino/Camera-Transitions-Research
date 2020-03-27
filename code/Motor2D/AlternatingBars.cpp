#include "AlternatingBars.h"
#include "TransitionManager.h"

AlternatingBars::AlternatingBars(SCENES next_scene, float step_duration) : Transition(next_scene, step_duration)
{

}

AlternatingBars::~AlternatingBars()
{

}

void AlternatingBars::StepTransition()
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

	TranslateBars();
}

void AlternatingBars::Entering()
{
	if (current_cutoff >= MAX_CUTOFF)
	{
		step = TRANSITION_STEP::CHANGING;
	}
}

void AlternatingBars::Changing(SCENES next_scene)
{
	App->scene_manager->SwitchScene(next_scene);

	step = TRANSITION_STEP::EXITING;
}

void AlternatingBars::Exiting()
{
	if (current_cutoff <= MIN_CUTOFF)
	{
		step = TRANSITION_STEP::NONE;
	}
}

void AlternatingBars::TranslateBars()
{

}