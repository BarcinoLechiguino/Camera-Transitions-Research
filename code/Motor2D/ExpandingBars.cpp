#include "ExpandingBars.h"
#include "TransitionManager.h"

ExpandingBars::ExpandingBars(SCENES next_scene, float step_duration, int bar_number) : Transition(next_scene, step_duration)
, bar_number(bar_number)
{

}

ExpandingBars::~ExpandingBars()
{

}

void ExpandingBars::StepTransition()
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

void ExpandingBars::Entering()
{
	if (current_cutoff >= MAX_CUTOFF)
	{
		step = TRANSITION_STEP::CHANGING;
	}
}

void ExpandingBars::Changing(SCENES next_scene)
{
	App->scene_manager->SwitchScene(next_scene);

	step = TRANSITION_STEP::EXITING;
}

void ExpandingBars::Exiting()
{
	if (current_cutoff <= MIN_CUTOFF)
	{
		step = TRANSITION_STEP::NONE;
	}
}

void ExpandingBars::TranslateBars()
{

}