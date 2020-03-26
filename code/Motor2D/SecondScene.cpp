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

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->transition_manager->CreateFadeToColour(SCENES::FIRST_SCENE);
	}

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

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		ret = false;
	}

	return ret;
}

bool SecondScene::CleanUp()
{
	LOG("Freeing Scene");
	bool ret = true;

	App->map->CleanUp();

	return ret;
}