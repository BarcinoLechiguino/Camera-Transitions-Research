#include "FadeToColour.h"
#include "TransitionManager.h"

FadeToColour::FadeToColour(SCENES next_scene, float step_duration, Color fade_colour) : Transition(next_scene, step_duration)
, fade_colour(fade_colour)
{	
	InitFadeToColour();
}

FadeToColour::~FadeToColour()
{

}

void FadeToColour::StepTransition()
{	
	switch (step)
	{
	case TRANSITION_STEP::ENTERING:
		
		Entering();
		
		break;

	case TRANSITION_STEP::CHANGING:

		Changing();

		break;

	case TRANSITION_STEP::EXITING:
		
		Exiting();
		
		break;
	}

	ApplyFade();
}

void FadeToColour::Entering()
{
	// TODO 3: Add the cutoff_rate to the current_cutoff each loop.
	// Moreover, change the transition step when the current_cutoff
	// reaches the MAX limit value. Remember to keep that limit value.
	// Tip: Check what current_cutoff and current_rate is.
	


}

void FadeToColour::Changing()
{
	App->scene_manager->SwitchScene(next_scene);

	step = TRANSITION_STEP::EXITING;
}

void FadeToColour::Exiting()
{
	// TODO 4: Substract the cutoff_rate off of the current_cutoff each loop. Very similar to the previous TODO, but reversed.
	// In addition to that, when the current_cutoff reaches the MIN limit value, change the step and delete the transition.
	// Tip: Remember what you did in TODO 1.



}

void FadeToColour::ApplyFade()
{
	// TODO 5: It's time to apply the current_cutoff to make the alpha fluctuate.
	// Make use of the SDL_SetRenderDrawColor() and SDL_RenderFillRect() to draw
	// the screen rect as well as to change it's alpha over time.
	// Tip: Remember the value range of current_cutoff. Do not forget about fade_colour.
	


}

void FadeToColour::InitFadeToColour()
{
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	
	// TODO 2: Initialize the variables of the FadeToColour transition.
	// Initialize the screen rect with the parameters of the window's rect.
	// After that, the  transition needs to get going. For that change the transition step.
	// Tip: Remember to check StepTransition() and which elements a transition has.



}