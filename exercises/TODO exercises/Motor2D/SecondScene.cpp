#include "SecondScene.h"
#include "Render.h"
#include "Textures.h"
#include "Input.h"
#include "Map.h"
#include "SceneManager.h"
#include "TransitionManager.h"

SecondScene::SecondScene() : Scene(SCENES::SECOND_SCENE)
{

}

SecondScene::~SecondScene()
{

}

bool SecondScene::Awake(pugi::xml_node& config)
{
	LOG("Loading SecondScene");
	bool ret = true;

	return ret;
}

bool SecondScene::Start()
{
	bool ret = true;

	App->map->Load("Second_Scene.tmx");

	InitScene();

	return ret;
}

bool SecondScene::PreUpdate()
{
	bool ret = true;



	return ret;
}

bool SecondScene::Update(float dt)
{
	bool ret = true;

	CameraDebugMovement(dt);

	DrawScene();

	return ret;
}

bool SecondScene::PostUpdate()
{
	bool ret = true;

	ExecuteTransition();

	return ret;
}

bool SecondScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;

	App->map->CleanUp();

	return ret;
}

void SecondScene::InitScene()
{
	App->map->GetMapSize(map_width, map_height);

	App->render->camera.x = map_width * 0.3f;												// This camera position gets the camera close to the center of the map.
	App->render->camera.y = -40;
}

void SecondScene::DrawScene()
{
	App->map->Draw();
}

void SecondScene::ExecuteTransition()
{
	if (!App->transition_manager->is_transitioning)
	{
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			App->transition_manager->CreateCut(SCENES::FIRST_SCENE);
		}

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			// TODO 7B: Create and execute a FadeToColour transition on input. Remember in which scene you currently are.
			// Tip: Actually it's only one line of code.
			
			

		}

		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{
			App->transition_manager->CreateSlide(SCENES::FIRST_SCENE, 0.5f, true, false, true, false);
		}

		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		{
			App->transition_manager->CreateSlide(SCENES::FIRST_SCENE, 0.5f, true, true, false, true);
		}
		
		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		{
			App->transition_manager->CreateWipe(SCENES::FIRST_SCENE, 0.5f, true, false, true, false);
		}

		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		{
			App->transition_manager->CreateWipe(SCENES::FIRST_SCENE, 0.5f, true, true, false, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
		{
			App->transition_manager->CreateAlternatingBars(SCENES::FIRST_SCENE, 1.0f, true, 5, true, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
		{
			App->transition_manager->CreateExpandingBars(SCENES::FIRST_SCENE, 1.0f, true, 5, true, true);
		}

		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
		{
			iPoint mouse_pos = App->input->GetMouseToWorld();

			App->transition_manager->CreateZoomToMouse(SCENES::FIRST_SCENE, mouse_pos, 0.5f, true);
		}

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			iPoint mouse_pos = App->input->GetMouseToWorld();

			App->transition_manager->CreateCameraToMouse(mouse_pos, 0.5f, true);
		}
	}
}