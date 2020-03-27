#ifndef __SLIDE_H__
#define __SLIDE_H__

#include "Transition.h"
#include "Color.h"

class Slide : public Transition
{
public:
	Slide(SCENES next_scene, float step_duration, bool enter_from_left, Color slide_colour);
	~Slide();

	void StepTransition();

public:
	void Entering();
	void Changing(SCENES next_scene);
	void Exiting();

	void TranslateSlide();

private:
	SDL_Rect	screen;
	Color		slide_colour;

	bool		enter_from_left;
};

#endif // !__WIPE_H__