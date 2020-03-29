#ifndef __WIPE_H__
#define __WIPE_H__

#include "Transition.h"
#include "Color.h"

class Wipe : public Transition
{
public:
	Wipe(SCENES next_scene, float step_duration, bool non_lerp, bool enter_from_left, Color wipe_colour);
	~Wipe();

	void StepTransition();

public:
	void Entering();
	void Changing(SCENES next_scene);
	void Exiting();

	void TranslateWipe();
	void DrawWipe();

	void InitWipe();

private:
	SDL_Rect	screen;
	Color		wipe_colour;

	bool		enter_from_left;
};

#endif // !__WIPE_H__