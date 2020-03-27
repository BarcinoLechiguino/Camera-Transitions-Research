#ifndef __CAMERA_TO_MOUSE
#define __CAMERA_TO_MOUSE

#include "Transition.h"

class CameraToMouse : public Transition
{
public:
	CameraToMouse(iPoint destination, float speed);
	~CameraToMouse();

	void StepTransition();

public:
	//void Entering();
	//void Exiting();

	void TranslateCamera();

private:
	iPoint origin;
	iPoint destination;
	iPoint camera_center;

	float speed;

	bool reached_destination;
	bool reached_x;
	bool reached_y;
};

#endif // !__CAMERA_TO_MOUSE

