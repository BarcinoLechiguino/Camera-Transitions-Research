#include "j1App.h"
#include "j1Input.h"
#include "j1Scene.h"
#include "j1Scene2.h"
#include "p2Log.h"
#include "j1Audio.h"
#include "j1Map.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1TransitionManager.h"
#include "j1Transitions.h"

j1Scene2::j1Scene2() : j1Module()
{
	name = "scene2";
	active = false;
}

j1Scene2::~j1Scene2()
{}

bool j1Scene2::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene2");

	if (App->scene->active == true)
		this->active = false;

	bool ret = true;

	return ret;
}

bool j1Scene2::Start()
{
	LOG("Starting scene 2");

	App->map->Load("scene2.tmx");

	return true;
}

bool j1Scene2::PreUpdate()
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

		if (App->input->GetMouseButtonDown(1) == KEY_DOWN) {
			App->transitions->MovingToMouse(mouse_position, 1.0f);
		}

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

bool j1Scene2::Update(float dt)
{
	App->map->Draw();

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 1;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 1;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 1;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 1;

	return true;
}

bool j1Scene2::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

bool j1Scene2::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Scene2::ChangeScene() {

	this->active = false;
	App->map->CleanUp();
	CleanUp();

	App->scene->active = true;
	App->scene->Start();
}