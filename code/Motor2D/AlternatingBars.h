#ifndef __ALTERNATING_BARS_H__
#define __ALTERNAING_BARS_H__

#include "Transition.h"

class AlternatingBars : Transition
{
public:
	AlternatingBars(SCENES next_scene, float step_duration);
	~AlternatingBars();

	void StepTransition();

public:
	void Entering();
	void Changing(SCENES next_scene);
	void Exiting();

	void TranslateBars();

private:
	SDL_Rect bar;

};

#endif // !__ALTERNATE_BARS_H__

