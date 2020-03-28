#ifndef __ZOOM_TO_MOUSE_H__
#define __ZOOM_TO_MOUSE_H__

#include  "Transition.h"

class ZoomToMouse : public Transition
{
public:
	ZoomToMouse(SCENES next_scene, iPoint mouse_position, float step_duration, float zoom_scale);
	~ZoomToMouse();

	void StepTransition();

public:
	void Entering();
	void Changing(SCENES next_scene);
	void Exiting();

	void ApplyZoom();

	void InitZoomToMouse(iPoint mouse_position);

private:
	iPoint mouse_position;

	float original_scale;									// Represents the scale previous to being incerased by the zoom.
	float zoom_scale;										// Represents the increase percentage of the scale. zoom_scale = 1.0f --> 100% scale increase.
	float zoom_rate;										// Representes the pace at which the zoom will be increased.

	float x_increase_rate;
	float y_increase_rate;

	SDL_Texture* target_to_zoom;

};

#endif // !__ZOOM_TO_MOUSE_H__
