#ifndef _j1TRANSITIONMANAGER_H__
#define _j1TRANSITIONMANAGER_H__

#include "j1Module.h"
#include "j1Color.h"
#include "j1Transitions.h"
#include <list>

class j1TransitionManager : public j1Module {
public:

	j1TransitionManager();
	~j1TransitionManager();

	virtual bool Awake(pugi::xml_node&) { return true; }
	virtual bool Start() { return true; }
	virtual bool PostUpdate();
	virtual bool CleanUp();

	void MovingToMouse(iPoint mouse_position, float time = 2.0f);
	void ZoomToMouse(iPoint mouse_position, bool repeat = false, float zoom = 3.0f, float time = 2.0f);
	void FadingToColor(j1Color color = Black, float time = 1.0f);
	void Wiping(j1Color color = Black, float time = 2.0f);
	void LinesAppearing(j1Color color = Black, float time = 2.0f);
	void SquaresAppearing(int transition = 1, j1Color color = Black, float time = 2.0f);

	void CleanTransitions(j1Transitions* ended_transition);

public:

	bool transition;

private:

	std::list<j1Transitions*> transitions_list;
	SDL_Rect screen;

};

#endif