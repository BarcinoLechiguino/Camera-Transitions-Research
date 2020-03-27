#include "TransitionManager.h"
#include "Cut.h"
#include "FadeToColour.h"
#include "Slide.h"
#include "Wipe.h"
#include "AlternatingBars.h"
#include "CameraToMouse.h"

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
		active_transition->StepTransition();
	}

	return ret;
}

bool TransitionManager::CleanUp()
{
	bool ret = true;
	
	if (active_transition != nullptr)
	{
		delete active_transition;
		active_transition = nullptr;
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

Transition* TransitionManager::CreateSlide(SCENES next_scene, float step_duration, bool enter_from_left, Color slide_colour)
{
	if (!is_transitioning)
	{
		active_transition = new Slide(next_scene, step_duration, enter_from_left, slide_colour);

		is_transitioning = true;
	}

	return active_transition;
}

Transition* TransitionManager::CreateWipe(SCENES next_scene, float step_duration, bool enter_from_left, Color fade_colour)
{
	if (!is_transitioning)
	{
		active_transition = new Wipe(next_scene, step_duration, enter_from_left, fade_colour);

		is_transitioning = true;
	}

	return active_transition;
}

Transition* TransitionManager::CreateAlternateBars(SCENES next_scene, float step_duration)
{
	return active_transition;
}

Transition* TransitionManager::CreateCameraToMouse(iPoint destination, float travel_time)
{
	if (!is_transitioning)
	{
		active_transition = new CameraToMouse(destination, travel_time);

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