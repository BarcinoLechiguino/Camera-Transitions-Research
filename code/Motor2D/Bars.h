#ifndef __BARS_H__
#define __BARS_H__

#include "Transition.h"
#include "Color.h"

//struct Bar
//{
//	SDL_Rect	bar;
//	Color		colour;
//};

class Bars : public Transition
{
public:
	Bars(SCENES next_scene, float step_duration, bool non_lerp, int bar_number, bool vertical, bool random_colours, Color even_colour, Color odd_colour);
	~Bars();

	void StepTransition();

public:
	void Entering();
	void Changing();
	void Exiting();

	//virtual void DrawBars();

	//virtual void AssignHorizontalBar(Bar& new_bar, int win_width, int win_height, int index);
	//virtual void AssignVerticalBar(Bar& new_bar, int win_width, int win_height, int index);
	//virtual void AssignBarColour(Bar& new_bar, int index);

public:
	// std::vector<Bar>	bars;

	bool				vertical;

	int					bar_number;
	int					win_width;
	int					win_height;

	Color				even_colour;
	Color				odd_colour;
};

#endif // !__BARS_H__

