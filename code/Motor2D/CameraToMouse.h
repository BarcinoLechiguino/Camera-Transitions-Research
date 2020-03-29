#ifndef __CAMERA_TO_MOUSE
#define __CAMERA_TO_MOUSE

#define MAX_TIME 1.0f

#include "Transition.h"

class CameraToMouse : public Transition
{
public:
	CameraToMouse(iPoint mouse_position, float step_duration, bool non_lerp);
	~CameraToMouse();

	void StepTransition();

public:
	void Entering();
	void Exiting();

	void TranslateCamera();

	void InitCameraToMouse(iPoint mouse_position);

private:
	iPoint	origin;
	iPoint	mouse_position;

	fPoint	next_pos;

	float	travel_time;
};

#endif // !__CAMERA_TO_MOUSE

