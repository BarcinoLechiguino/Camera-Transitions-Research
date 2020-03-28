#ifndef __ALTERNATING_BARS_H__
#define __ALTERNAING_BARS_H__

#include "Transition.h"

class AlternatingBars : public Transition
{
public:
	AlternatingBars(SCENES next_scene, float step_duration, int bar_number);
	~AlternatingBars();

	void StepTransition();

public:
	void Entering();
	void Changing(SCENES next_scene);
	void Exiting();

	void TranslateBars();

private:
	std::vector<SDL_Rect> bars;
	int			bar_number;

};

#endif // !__ALTERNATE_BARS_H__

