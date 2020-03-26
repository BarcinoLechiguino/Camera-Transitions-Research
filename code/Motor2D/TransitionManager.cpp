#include "TransitionManager.h"
#include "FadeToColour.h"

TransitionManager::TransitionManager()
{

}

TransitionManager::~TransitionManager()
{

}

bool TransitionManager::Awake(pugi::xml_node& config)
{
	bool ret = true;
	
	return ret;
}

bool TransitionManager::Start()
{
	bool ret = true;

	std::vector<Transition*>::iterator item = transitions.begin();

	for (; item != transitions.end(); ++item)
	{
		(*item)->Start();
	}

	return ret;
}

bool TransitionManager::PreUpdate()
{
	bool ret = true;

	std::vector<Transition*>::iterator item = transitions.begin();

	for (; item != transitions.end(); ++item)
	{
		if (!(*item)->is_initialized)
		{
			(*item)->Start();
		}
	}

	return ret;
}

bool TransitionManager::Update(float dt)
{
	bool ret = true;

	return ret;
}

bool TransitionManager::PostUpdate()
{
	bool ret = true;

	std::vector<Transition*>::reverse_iterator item = transitions.rbegin();

	for (; item != transitions.rend(); ++item)
	{
		(*item)->StepTransition(App->GetDT());
	}

	return ret;
}

bool TransitionManager::CleanUp()
{
	bool ret = true;
	
	transitions.clear();

	return ret;
}

Transition* TransitionManager::CreateFadeToColour(SCENES next_scene, float step_duration, Color fade_colour)
{
	Transition* transition = nullptr;

	transition = new FadeToColour(next_scene, step_duration, fade_colour);

	if (transition != nullptr)
	{
		transitions.push_back(transition);
	}

	return transition;
}

void TransitionManager::DeleteTransition(Transition* transition)
{
	std::vector<Transition*>::iterator item = transitions.begin();

	for (; item != transitions.end(); ++item)
	{
		if ((*item) == transition)
		{
			transitions.erase(item);
			break;
		}
	}
}