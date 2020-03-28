#include "Transition.h"
#include "Render.h"
#include "Textures.h"

Transition::Transition(SCENES next_scene, float step_duration, float current_cutoff) : 
	next_scene(next_scene), 
	step_duration(step_duration), 
	current_cutoff(current_cutoff)
{

}

Transition::~Transition()
{

}

void Transition::Start()
{

}

void Transition::StepTransition()
{

}

void Transition::CleanUp()
{

}

void Transition::Entering()
{
	
}

void Transition::Changing(SCENES next_scene)
{
	//App->scene_manager->SwitchScene(next_scene);
}

void Transition::Exiting()
{

}

float Transition::Lerp(float start, float end, float rate)								// Rate goes from 0.0f (0 %) to 1.0f (100 %) advancement per frame.
{																						// If Lerp(0.0f, 10.0f, 1.0f), then the advancement per frame will be of 10.0f.
	float increment = (end - start) * rate;

	return start + increment;
}

float Transition::GetCutoffRate(float step_duration, float dt)
{
	cutoff_rate = dt / step_duration;

	return cutoff_rate;
}