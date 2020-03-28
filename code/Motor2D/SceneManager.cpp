#include "SceneManager.h"
#include "FirstScene.h"
#include "SecondScene.h"
#include "Render.h"
#include "Input.h"

SceneManager::SceneManager() : current_scene(nullptr)
{
	name = "scene_manager";
}

SceneManager::~SceneManager()
{

}

bool SceneManager::Awake(pugi::xml_node& config)
{
	bool ret = true;
	
	ScenePushbacks();
	
	LoadInitialScene();

	current_scene->Awake(config);

	return ret;
}

bool SceneManager::Start()
{
	bool ret = true;

	current_scene->Start();

	return ret;
}

bool SceneManager::PreUpdate()
{
	bool ret = true;

	current_scene->PreUpdate();

	return ret;
}

bool SceneManager::Update(float dt)
{
	bool ret = true;

	current_scene->Update(dt);

	return ret;
}

bool SceneManager::PostUpdate()
{
	bool ret = true;

	current_scene->PostUpdate();

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		App->ExitApplication(ret);
	}

	return ret;
}

bool SceneManager::CleanUp()
{
	bool ret = true;

	std::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		RELEASE((*item));
	}
	scenes.clear();
	
	if (current_scene != nullptr)
	{
		//current_scene->CleanUp();
	}

	return ret;
}

void SceneManager::LoadInitialScene()
{
	current_scene = (*scenes.begin());
}

void SceneManager::SwitchScene(SCENES scene_name)
{	
	current_scene->CleanUp();

	std::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		if ((*item)->scene_name == scene_name)
		{
			current_scene = (*item);
		}
	}

	if (current_scene != nullptr)
	{
		current_scene->Start();
	}
}

void SceneManager::LoadScene(SCENES scene_name)
{
	std::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		if ((*item)->scene_name == scene_name)
		{
			next_scene = (*item);
		}
	}

	next_scene->Start();
}

void SceneManager::UnloadScene(Scene* scene_to_unload)
{
	std::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		if ((*item) == scene_to_unload)
		{
			if ((*item) == current_scene)
			{
				if (next_scene != nullptr)															// Cleaning up current_scene. next_scene is re-assigned to current_scene first.
				{
					Scene* tmp = current_scene;

					current_scene = next_scene;

					next_scene = tmp;

					tmp = nullptr;

					next_scene->CleanUp();

					next_scene = nullptr;
				}
				else
				{
					LOG("UNLOAD SCENE ERROR: Two scenes were not active at the same time.");
				}

				break;
			}
			else
			{
				if (current_scene != nullptr)
				{
					(*item)->CleanUp();

					next_scene = nullptr;
				}
				else
				{
					LOG("UNLOAD SCENE ERROR: Two scenes were not active at the same time.");
				}
				
				break;
			}
		}
	}
}

// ---------------- CREATE SCENE METHODS ----------------
Scene* SceneManager::CreateScene(SCENES scene_name)
{
	Scene* item = nullptr;

	switch (scene_name)
	{
	case SCENES::FIRST_SCENE:

		item = new FirstScene();
		
		break;

	case SCENES::SECOND_SCENE:
		
		item = new SecondScene();
		
	break;
	}

	if (item != nullptr)
	{
		scenes.push_back(item);
	}

	return item;
}

void SceneManager::ScenePushbacks()
{
	CreateScene(SCENES::FIRST_SCENE);
	CreateScene(SCENES::SECOND_SCENE);
}

// ------------------------------------------------------

void SceneManager::CaseSwitchScene(SCENES scene_name)
{
	if (current_scene != nullptr)
	{
		current_scene->CleanUp();
	}

	/*switch (scene)
	{
	case SCENE::FIRST_SCENE:

		current_scene = new FirstScene(scene_name);

		break;

	case SCENE::SECOND_SCENE:

		current_scene = new SecondScene(scene_name);

		break;
	}*/

	current_scene->Start();
}

void SceneManager::VectorSwitchScene(SCENES scene_name)
{
	if (current_scene != nullptr)
	{
		current_scene->CleanUp();
	}

	std::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		if ((*item)->scene_name == scene_name)
		{
			current_scene = (*item);
		}
	}

	current_scene->Start();
}
