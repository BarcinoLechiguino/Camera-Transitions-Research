#include "TransitionManager.h"
#include "Cut.h"
#include "FadeToColour.h"

TransitionManager::TransitionManager() : active_transition(nullptr), is_transitioning(false)
{

}

TransitionManager::~TransitionManager()
{

}

bool TransitionManager::PostUpdate()
{
	bool ret = true;

	if (active_transition != nullptr)
	{
		active_transition->StepTransition(App->GetDT());
	}

	return ret;
}

Transition* TransitionManager::CreateCut(SCENES next_scene)
{
	if (!is_transitioning)
	{
		active_transition = new Cut(next_scene);

		is_transitioning = true;
	}

	return active_transition;
}

Transition* TransitionManager::CreateFadeToColour(SCENES next_scene, float step_duration, Color fade_colour)
{	
	if (!is_transitioning)
	{
		active_transition = new FadeToColour(next_scene, step_duration, fade_colour);

		is_transitioning = true;
	}

	return active_transition;
}

void TransitionManager::DeleteActiveTransition()
{
	is_transitioning = false;
	
	delete active_transition;

	active_transition = nullptr;
}