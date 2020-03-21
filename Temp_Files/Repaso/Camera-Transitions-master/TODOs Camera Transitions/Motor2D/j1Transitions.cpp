#include <math.h>
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Transitions.h"
#include "j1Render.h"
#include "j1TransitionManager.h"
#include "j1Window.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"

// This module controls each single transitions, with a start, 
// a change of scenes, and the exit of the transition

j1Transitions::j1Transitions(float time) 
{
	// Total time that each step of the transition takes (start and exit)
	this->time = time;

	// We start a timer at current_time
	current_time = new Timer();
	current_time->Start();

	// Transition starts
	state = Transition_Step::START;
	App->transitions->transition = true;
}

j1Transitions::~j1Transitions() 
{
	delete current_time;
}

float j1Transitions::Interpolation(float start, float end, float percentage) {

	// With a percentage from 0 to 1, this returns values from the 
	// starting point to the end point depending on the percentage.
	return start + percentage * (end - start);
}

void j1Transitions::PostUpdate() 
{
	// Switching the state of the transition
	switch (state)
	{
	case j1Transitions::Transition_Step::NONE:
		break;

		// Transition starts
	case j1Transitions::Transition_Step::START:
		Start();
		break;

		// Transition hits middle point
	case j1Transitions::Transition_Step::CHANGE:
		Change();
		break;

		// Transition is finishing
	case j1Transitions::Transition_Step::EXIT:
		Exit();
		break;

	default:
		break;
	}
}

void j1Transitions::Start() {

	// Percentage changes from 0 to 1
	percentage = current_time->ReadSec() * (1 / time);

	// TODO 1: Declare a condition that makes the step change when time's over.
	// You will have to do the same on the Exit() void below.
}

void j1Transitions::Change() {

	// Timer starts over again
	current_time->Start();

	// Transitions starts to exit
	state = Transition_Step::EXIT;
}

void j1Transitions::Exit() {

	// Percentage changes from 0 to 1
	percentage = current_time->ReadSec() * (1 / time);

	// TODO 1: The next state of the transition is... no transition.
	// You also have to clean the transition in some way.
	// TIP: See TransitionManager (or ask for help :D)
}