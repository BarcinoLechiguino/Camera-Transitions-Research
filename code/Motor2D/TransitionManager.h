#ifndef __TRANSITION_MANAGER_H__
#define __TRANSITION_MANAGER_H__

#include "Module.h"
#include "Color.h"
//#include "Transition.h"

class		Transition;
class		FadeToColour;
enum class	SCENES;

class TransitionManager :  public Module
{
public:
	TransitionManager();
	~TransitionManager();

	bool PostUpdate();

public:
	Transition* CreateCut(SCENES next_scene);
	Transition* CreateFadeToColour(SCENES next_scene, float step_duration = 1.0f, Color fade_colour = Black);

	void DeleteActiveTransition();

public:
	bool						is_transitioning;																	// Will define whether a transition is active or not.

private:
	//std::vector<Transition*>	transitions;
	Transition*					active_transition;																	// Pointer to the transtion that's active at any given time.

};

#endif // !__TRANSITION_MANAGER_H__
