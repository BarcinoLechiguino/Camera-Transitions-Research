#include "p2Defs.h"
#include "p2Log.h"
#include "Application.h"
#include "Input.h"
#include "Fonts.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "SceneManager.h"
#include "FirstScene.h"
#include "Transition.h"
#include "TransitionManager.h"

FirstScene::FirstScene() : Scene(SCENES::FIRST_SCENE)
{
	name = "first_scene";
}

FirstScene::FirstScene(SCENES scene) : Scene(scene)
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

	name = "FirstScene";
	
	App->map->Load("First_Scene_Flooded.tmx");

	/*int win_width = 0;
	int win_height = 0;

	App->win->GetWindowSize(win_width, win_height);

	uint r = 0x00ff0000;
	uint g = 0x0000ff00;
	uint b = 0x000000ff;
	uint a = 0xff000000;
	
	SDL_Surface* sur	= SDL_CreateRGBSurface(0, win_width, win_height, 32, r, g, b, a);

	SDL_Renderer* rend	= SDL_CreateSoftwareRenderer(sur);

	SDL_Texture* tex	= App->tex->Load("gui/atlas.png", rend);

	//App->render->Blit(tex, 0, 0, NULL, false, rend);

	debug_tex = SDL_CreateTextureFromSurface(App->render->renderer, sur);*/

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
	
	// Camera Debug Movement ---
	CameraDebugMovement(dt);

	// Map ---
	App->map->Draw();

	//App->render->Blit(debug_tex, 0, 0, NULL);
	//App->render->Blit(tex, 0, 0, NULL);

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

	//App->gui->CleanUp();

	App->map->CleanUp();

	return ret;
}

void FirstScene::ExecuteTransition()
{
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->transition_manager->CreateCut(SCENES::SECOND_SCENE);
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		App->transition_manager->CreateFadeToColour(SCENES::SECOND_SCENE, 1.0f, White);
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		App->transition_manager->CreateSlide(SCENES::SECOND_SCENE, 1.0f, false, White);
	}

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		App->transition_manager->CreateWipe(SCENES::SECOND_SCENE, 1.0f, false, White);
	}

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		iPoint mouse_pos = { 0, 0 };
		
		App->input->GetMousePosition(mouse_pos.x, mouse_pos.y);

		App->transition_manager->CreateCameraToMouse(mouse_pos);
	}
}