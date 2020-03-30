#include "p2Defs.h"
#include "p2Log.h"
#include "Application.h"
#include "Input.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "SceneManager.h"
#include "FirstScene.h"
#include "Transition.h"
#include "TransitionManager.h"

FirstScene::FirstScene() : Scene(SCENES::FIRST_SCENE)
{

}

// Destructor
FirstScene::~FirstScene()
{

}

// Called before render is available
bool FirstScene::Awake(pugi::xml_node& config)
{
	LOG("Loading FirstScene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool FirstScene::Start()
{
	bool ret = true;
	
	App->map->Load("First_Scene.tmx");

	InitScene();

	return ret;
}

// Called each loop iteration
bool FirstScene::PreUpdate()
{
	bool ret = true;

	return ret;
}

// Called each loop iteration
bool FirstScene::Update(float dt)
{
	bool ret = true;
	
	CameraDebugMovement(dt);

	DrawScene();

	return ret;
}

// Called each loop iteration
bool FirstScene::PostUpdate()
{
	bool ret = true;
	
	ExecuteTransition();

	return ret;
}

// Called before quitting
bool FirstScene::CleanUp()
{
	LOG("Freeing scene");
	bool ret = true;

	App->map->CleanUp();

	return ret;
}

void FirstScene::InitScene()
{
	App->map->GetMapSize(map_width, map_height);

	App->render->camera.x = map_width * 0.3f;										// This camera position gets the camera close to the center of the map.
	App->render->camera.y = -40;
}

void FirstScene::DrawScene()
{
	App->map->Draw();
}

void FirstScene::ExecuteTransition()
{
	if (!App->transition_manager->is_transitioning)
	{
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			App->transition_manager->CreateCut(SCENES::SECOND_SCENE);
		}

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			App->transition_manager->CreateFadeToColour(SCENES::SECOND_SCENE);
		}

		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{
			App->transition_manager->CreateSlide(SCENES::SECOND_SCENE, 0.5f, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		{
			App->transition_manager->CreateSlide(SCENES::SECOND_SCENE, 0.5f, true, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		{
			App->transition_manager->CreateWipe(SCENES::SECOND_SCENE, 0.5f, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		{
			App->transition_manager->CreateWipe(SCENES::SECOND_SCENE, 0.5f, true, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
		{
			App->transition_manager->CreateAlternatingBars(SCENES::SECOND_SCENE, 0.5f, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
		{
			App->transition_manager->CreateExpandingBars(SCENES::SECOND_SCENE, 0.5f, true);
		}

		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
		{
			iPoint mouse_pos = App->input->GetMouseToWorld();

			App->transition_manager->CreateZoomToMouse(SCENES::SECOND_SCENE, mouse_pos, 0.5f, true);
		}

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			iPoint mouse_pos = App->input->GetMouseToWorld();

			App->transition_manager->CreateCameraToMouse(mouse_pos, 0.5f, true);
		}
	}
}