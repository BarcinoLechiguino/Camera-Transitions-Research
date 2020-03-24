#include "SceneManager.h"
#include "FirstScene.h"
#include "SecondScene.h"

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

	CreateScene(SCENES::FIRST_SCENE);
	CreateScene(SCENES::SECOND_SCENE);
	
	LoadInitialScene(SCENES::FIRST_SCENE);

	//current_scene = new FirstScene(SCENE::FIRST_SCENE);

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

	return ret;
}

bool SceneManager::CleanUp()
{
	bool ret = true;

	std::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		RELEASE((*item));
		scenes.erase(item);
	}

	scenes.clear();
	
	if (current_scene != nullptr)
	{
		//current_scene->CleanUp();
	}

	return ret;
}

void SceneManager::LoadInitialScene(SCENES scene_name)
{
	SwitchScene(scene_name);
}

void SceneManager::SwitchScene(SCENES scene_name)
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

	std::vector<Scene*>::iterator item = scenes.begin();

	for (; item != scenes.end(); ++item)
	{
		if ((*item)->scene_name == scene_name)
		{
			current_scene = (*item);
		}
	}

	//current_scene->Start();
}

Scene* SceneManager::CreateScene(SCENES scene_name)
{
	Scene* item = nullptr;

	switch (scene_name)
	{
	case SCENES::FIRST_SCENE:

		item = new FirstScene(scene_name);
		
		break;

	case SCENES::SECOND_SCENE:
		
		item = new SecondScene(scene_name);
		
	break;
	}

	if (item != nullptr)
	{
		scenes.push_back(item);
	}

	return item;
}