#pragma once

#include "j1TransitionManager.h"
#include "j1Transitions.h"

class Lines : public j1Transitions {

public:

	Lines(j1Color color, float time);
	~Lines();

	void Start();
	void Change();
	void Exit();

private:

	uint w, h;
	SDL_Rect lines[11];
	SDL_Rect screen;

	float initial_x_right;
	float initial_x_left;
	int height = 0;

	j1Color color;

};