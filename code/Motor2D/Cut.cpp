#include "Cut.h"
#include "TransitionManager.h"

Cut::Cut(SCENES next_scene) : Transition(next_scene, 0.0f)
{
	this->next_scene = next_scene;
}

Cut::~Cut()
{

}

void Cut::StepTransition(float dt)
{
	App->scene_manager->SwitchScene(next_scene);

	App->transition_manager->DeleteActiveTransition();
}