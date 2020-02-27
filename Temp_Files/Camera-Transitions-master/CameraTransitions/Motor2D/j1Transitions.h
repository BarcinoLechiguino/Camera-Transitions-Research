#ifndef __j1TRANSITIONS_H__
#define __j1TRANSITIONS_H__

#include "j1Module.h"
#include "j1Color.h"
#include "Timer.h"
#include "SDL/include/SDL_rect.h"
#include "p2Point.h"

class j1Transitions 
{
public:
	enum class Transition_Step {
		NONE,
		START,
		CHANGE,
		EXIT
	};

public:
	j1Transitions(float time);
	~j1Transitions();

	void PostUpdate();

	virtual void Start();
	virtual void Change();
	virtual void Exit();

	Timer* current_time = nullptr;
	Transition_Step state;
	float time;
	float percentage = 0;
	float Interpolation(float start, float end, float percentage);
};

#endif