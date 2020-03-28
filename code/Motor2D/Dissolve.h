#ifndef __DISSOLVE_H__
#define __DISSOLVE_H__

#include "Transition.h"

class Dissolve : public Transition
{
public:
	Dissolve(SCENES next_scene, float step_duration);
	~Dissolve();

	void StepTransition();

public:
	void Entering();
	void Changing(SCENES next_scene);
	void Exiting();

	void ApplyDissolve();

	void InitDissolve();

private:


};

#endif // !__DISSOLVE_H__