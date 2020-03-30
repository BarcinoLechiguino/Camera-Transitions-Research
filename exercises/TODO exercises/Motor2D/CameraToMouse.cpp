#include "CameraToMouse.h"
#include "TransitionManager.h"

CameraToMouse::CameraToMouse(iPoint mouse_position, float step_duration, bool non_lerp) : Transition(SCENES::NONE, step_duration, non_lerp)
, origin(0.0f, 0.0f)
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
	current_cutoff += GetCutoffRate(step_duration);

	if (current_cutoff <= MAX_CUTOFF)
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
	// TODO 8: Make the camera move from it's origin position to the mouse's position.
	// You will need to use either Lerp() or N_Lerp() as well as the next_pos buffer to move the camera accurately.
	// Tip: Check what Lerp() and N_Lerp() do and which values they require as parameters.
	
	

}

void CameraToMouse::InitCameraToMouse(iPoint mouse_position)
{
	origin.x = App->render->camera.x;
	origin.y = App->render->camera.y;

	this->mouse_position.x = (-mouse_position.x) + App->render->camera.w * 0.5f;		// The mouse position that was passed as argument will be re-calculated so the value
	this->mouse_position.y = (-mouse_position.y) + App->render->camera.h * 0.5f;		// can be applied to the camera x and y positions.

	step = TRANSITION_STEP::ENTERING;
}