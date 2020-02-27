#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Scene2.h"
#include "j1Transitions.h"
#include "j1TransitionManager.h"
#include "FadeToColor.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("scene1.tmx");
	
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	int mouse_x, mouse_y;
	App->input->GetMousePosition(mouse_x, mouse_y);
	iPoint mouse_position = App->render->ScreenToWorld(mouse_x, mouse_y);

	if (!App->transitions->transition) {
		 
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_REPEAT)
			App->transitions->FadingToColor(White);

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_REPEAT)
			App->transitions->Wiping(Black, 0.5f);

		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_REPEAT)
			App->transitions->LinesAppearing(Black, 1.0f);

		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_REPEAT)
			App->transitions->SquaresAppearing(1);

		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_REPEAT)
			App->transitions->SquaresAppearing(2);

		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_REPEAT)
			App->transitions->SquaresAppearing(3);

		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_REPEAT)
			App->transitions->SquaresAppearing(4);

		if (App->input->GetMouseButtonDown(1) == KEY_DOWN)
			App->transitions->MovingToMouse(mouse_position, 1.0f);

		if (App->input->GetMouseButtonDown(3) == KEY_DOWN) {
			zoom_done != zoom_done;

			if (!zoom_done)
				App->transitions->ZoomToMouse(mouse_position, false, 3.0f, 0.5f);
			else 
				App->transitions->ZoomToMouse(mouse_position, true, 3.0f, 0.5f);
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 1;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 1;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 1;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 1;

	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Camera Transitions Research || CurrentTile: %d, %d", map_coordinates.x, map_coordinates.y);

	App->win->SetTitle(title.GetString());
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Scene::ChangeScene() 
{
	this->active = false;
	App->map->CleanUp();
	CleanUp();

	App->scene2->active = true;
	App->scene2->Start();
}