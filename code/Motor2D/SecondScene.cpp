#include "SecondScene.h"
#include "Render.h"
#include "Input.h"
#include "Map.h"
#include "SceneManager.h"
#include "TransitionManager.h"

SecondScene::SecondScene() : Scene(SCENES::SECOND_SCENE)
{
	name = "second_scene";
}

SecondScene::SecondScene(SCENES scene) : Scene(scene)
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

	App->map->Draw();

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

void SecondScene::ExecuteTransition()
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->transition_manager->CreateCut(SCENES::FIRST_SCENE);
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		App->transition_manager->CreateFadeToColour(SCENES::FIRST_SCENE);
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		App->transition_manager->CreateSlide(SCENES::FIRST_SCENE);
	}

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		App->transition_manager->CreateWipe(SCENES::FIRST_SCENE);
	}
}