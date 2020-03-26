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

	bool Awake(pugi::xml_node& config);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

public:
	Transition* CreateFadeToColour(SCENES next_scene, float step_duration = 1.0f, Color fade_colour = Black);
	
	void DeleteTransition(Transition* transition);

private:
	std::vector<Transition*> transitions;

};

#endif // !__TRANSITION_MANAGER_H__
