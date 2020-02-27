#include "j1Scene.h"
#include "j1Scene2.h"
#include "j1TransitionManager.h"
#include "j1Transitions.h"
#include "j1Render.h"
#include "FadeToColor.h"
#include "j1App.h"
#include "j1Window.h"
#include "p2Log.h"

// Similar code to FadeToBlack, but now we can control the color easily

FadeToColor::FadeToColor(j1Color color, float time) : j1Transitions(time) {

	this->color = color;

	uint w, h;
	App->win->GetWindowSize(w, h);
	screen = { 0, 0, (int)w, (int)h };
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

}

FadeToColor::~FadeToColor()
{}

void FadeToColor::Start() {

	j1Transitions::Start();

	// TODO 2: Fade to color. A color fades from 0 to 100% opacity.
	// Call the function FillScreen() and think about which value you pass
	// TIP: You'll have to use the Interpolation() function
	FillScreen(Interpolation(0.0f, 255.0f, percentage));
}

void FadeToColor::Change() {

	FillScreen(255.0f);
		
	// Scene changes
	if (App->scene->active)
		App->scene->ChangeScene();

	else
		App->scene2->ChangeScene();

	j1Transitions::Change();
}

void FadeToColor::Exit() {

	j1Transitions::Exit();

	// TODO 3: Make the fade out effect
	FillScreen(Interpolation(255.0f, 0.0f, percentage));
}

void FadeToColor::FillScreen(float opacity) {
	
	if (opacity < 0)
		opacity = 0;
	
	if (opacity > 255)
		opacity = 255;

	SDL_SetRenderDrawColor(App->render->renderer, color.r, color.g, color.b, opacity);
	SDL_RenderFillRect(App->render->renderer, &screen);
}