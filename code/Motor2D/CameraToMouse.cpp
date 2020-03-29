#include "CameraToMouse.h"
#include "TransitionManager.h"

CameraToMouse::CameraToMouse(iPoint mouse_position, float step_duration, bool non_lerp) : Transition(SCENES::NONE, step_duration, non_lerp)
, travel_time(0.0f)
, next_pos(0.0f, 0.0f)
{	
	InitCameraToMouse(mouse_position);
}

CameraToMouse::~CameraToMouse()
{

}

void CameraToMouse::StepTransition()
{
	switch (step)
	{
	case TRANSITION_STEP::ENTERING:

		Entering();

		break;

	case TRANSITION_STEP::EXITING:

		Exiting();

		break;
	}
}

void CameraToMouse::Entering()
{
	travel_time += GetCutoffRate(step_duration);

	if (travel_time <= MAX_TIME)
	{
		TranslateCamera();
	}
	else
	{	
		step = TRANSITION_STEP::EXITING;
	}
}

void CameraToMouse::Exiting()
{
	App->transition_manager->DeleteActiveTransition();
}

void CameraToMouse::TranslateCamera()
{
	if (!non_lerp)
	{
		next_pos.x = Lerp(origin.x, mouse_position.x, travel_time);
		next_pos.y = Lerp(origin.y, mouse_position.y, travel_time);
	}
	else
	{
		//next_pos.x = N_Lerp(origin.x, mouse_position.x, travel_time, true);
		//next_pos.y = N_Lerp(origin.y, mouse_position.y, travel_time, true);

		next_pos.x = N_Lerp(origin.x, mouse_position.x, travel_time);
		next_pos.y = N_Lerp(origin.y, mouse_position.y, travel_time);
	}

	App->render->camera.x = next_pos.x;
	App->render->camera.y = next_pos.y;
}

void CameraToMouse::InitCameraToMouse(iPoint mouse_position)
{
	origin.x = App->render->camera.x;
	origin.y = App->render->camera.y;

	this->mouse_position.x = (-mouse_position.x) + App->render->camera.w * 0.5f;
	this->mouse_position.y = (-mouse_position.y) + App->render->camera.h * 0.5f;

	step = TRANSITION_STEP::ENTERING;
}