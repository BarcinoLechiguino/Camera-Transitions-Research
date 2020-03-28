#ifndef __EXPANDING_BARS_H__
#define __EXPANDING_BARS_H__

#include "Transition.h"

class ExpandingBars : public Transition
{
public:
	ExpandingBars(SCENES next_scene, float step_duration, int bar_number);
	~ExpandingBars();

	void StepTransition();

public:
	void Entering();
	void Changing(SCENES next_scene);
	void Exiting();

	void TranslateBars();

private:
	SDL_Rect	bar;
	int			bar_number;

};

#endif // !__EXPANDING_BARS_H__
