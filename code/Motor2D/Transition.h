#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#define MAX_CUTOFF 1.0f
#define MIN_CUTOFF 0.0f

#include "SDL/include/SDL.h"
#include "Application.h"
#include "Window.h"
#include "Render.h"
#include "SceneManager.h"

enum class TRANSITION_STEP
{
	NONE,
	ENTERING,
	CHANGING,
	EXITING
};

class Transition
{
public:
	Transition(SCENES next_scene, float step_duration, float current_cutoff = 0);
	virtual ~Transition();

	virtual void Start();

	virtual void StepTransition(float dt);

	virtual void CleanUp();

public:
	virtual void Entering(float dt);												// Method that will be used to execute the ENTERING transition step.
	virtual void Changing(SCENES next_scene);										// Method that will be used to execute the CHANGING transition step.
	virtual void Exiting(float dt);													// Method that will be used to execute the EXITING transition step.
	
	virtual SDL_Texture* CreateTransitionTexture();
	float Lerp(float start_time, float total_time, float dt);						// Method that will be used to interpolate the speed of a given transition.
	float GetCutoffRate(float dt, float time);										// Method that returns the cutoff rate for a given transition.

public:
	TRANSITION_STEP step;															// All the steps that a given transition will go through.
	SCENES			next_scene;														// The scene that will be transitioned to.

	float			step_duration;													// The duration of each transtion step in seconds.
	float			current_cutoff;													// The amount of time that has elapsed since the start of the transition step.

	bool			is_initialized;													// Will determine whether or not a transition has been initialized.
	bool			has_finished;													// Will determine whether or not a transition has finished.

private:
	float			cutoff_rate;													// The rate at which the transition will elapse. ranges from 0.0f to 1.0f where 0.0 = step_start & 1.0f = step_end.

private:
	SDL_Surface*	surface;
	int				win_width;
	int				win_height;
};

#endif // !__TRANSITION_H__