#ifndef __FADE_TO_COLOUR_H__
#define __FADE_TO_COLOUR_H__

#include "Transition.h"
#include "Color.h"

class FadeToColour : public Transition
{
public:
	FadeToColour(SCENES next_scene, float step_duration, Color colour);
	~FadeToColour();

	void StepTransition(float dt);

public:
	void Entering(float dt);												// Method that will be used to execute the ENTERING transition step.
	void Changing(SCENES next_scene);										// Method that will be used to execute the CHANGING transition step.
	void Exiting(float dt);													// Method that will be used to execute the EXITING transition step.
	
	void ApplyFade();														// Method that will be used to update the alpha value of the fade. //TMP NAME AND COMMENT

	void GetScreenRect(SDL_Rect& rect);										// Method that will get the current dimensions of the screen and assign them to a given rect.

private:
	SDL_Rect	screen;
	Color		fade_colour;
};

#endif // !__FADE_TO_COLOUR_H__