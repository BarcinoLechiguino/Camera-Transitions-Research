#include "CameraToMouse.h"
#include "TransitionManager.h"

CameraToMouse::CameraToMouse(iPoint destination, float speed) : Transition(SCENES::NONE, 0)
, destination(destination)
, reached_destination(false)
, reached_x(false)
, reached_y(false)
{	
	this->destination.x = (-this->destination.x + App->render->camera.w * 0.5f);
	this->destination.y = (-this->destination.y + App->render->camera.h * 0.5f);

	origin = { App->render->camera.x, App->render->camera.y };
}

CameraToMouse::~CameraToMouse()
{

}

void CameraToMouse::StepTransition()
{
	current_cutoff = GetCutoffRate(speed);

	if (!reached_destination)
	{
		TranslateCamera();
	}
	else
	{
		App->transition_manager->DeleteActiveTransition();
	}
}

void CameraToMouse::TranslateCamera()
{
	float pos_x = Lerp(origin.x, destination.x, App->GetDT());
	float pos_y = Lerp(origin.y, destination.y, App->GetDT());

	App->render->camera.x = pos_x;
	App->render->camera.y = pos_y;

	LOG("Destination pos: %d, %d", destination.x, destination.y);
	LOG("Camera pos: %d, %d", App->render->camera.x, App->render->camera.y);
	
	
	if (App->render->camera.x == destination.x && App->render->camera.y == destination.y)
	{
		reached_destination = true;
	}
}