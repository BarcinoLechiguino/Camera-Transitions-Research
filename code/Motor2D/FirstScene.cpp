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

	App->tex->UnLoad(scene_texture);
	App->tex->UnLoad(tileset_texture);

	if (SDL_RenderClear(scene_renderer) == 0)
	{
		scene_renderer = nullptr;
	}

	SDL_FreeSurface(scene_surface);

	return ret;
}

void FirstScene::InitScene()
{
	tileset_texture = App->tex->Load("maps/tiles_first_map.png", scene_renderer);	// This texture will be used SceneToTexture(). Needed to get a single whole texture of the map.

	App->map->GetMapSize(map_width, map_height);
	App->map->GetTileOffset(x_offset, y_offset);
	
	/*App->render->camera.x = map_width * 0.5f;										// This camera position is to have the renderer render all the scene_texture.
	App->render->camera.y = 0;

	SceneToTexture();*/

	App->render->camera.x = map_width * 0.3f;										// This camera position gets the camera close to the center of the map.
	App->render->camera.y = -40;
}

void FirstScene::DrawScene()
{
	App->map->Draw();

	if (scene_texture != nullptr)
	{
		//App->render->Blit(scene_texture, -(map_width) * 0.5f, 0, NULL);
	}	
}

SDL_Texture* FirstScene::SceneToTexture()
{
	App->render->CreateSubRenderer(map_width + x_offset, map_height + y_offset, scene_surface, scene_renderer);		// Both scene_surface and scene renderer are passed by reference.

	tileset_texture = App->tex->Load("maps/tiles_first_map.png", scene_renderer);
	App->map->DrawToSubRenderer(scene_renderer, tileset_texture);

	scene_texture = SDL_CreateTextureFromSurface(App->render->renderer, scene_surface);

	return scene_texture;
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
			App->transition_manager->CreateFadeToColour(SCENES::SECOND_SCENE, 1.0f, White);
		}

		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{
			App->transition_manager->CreateSlide(SCENES::SECOND_SCENE, 1.0f, true, false, White);
		}

		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		{
			App->transition_manager->CreateWipe(SCENES::SECOND_SCENE, 1.0f, true, false, White);
		}

		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		{
			App->transition_manager->CreateAlternatingBars(SCENES::SECOND_SCENE, 1.0f, true, 5, true, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		{
			App->transition_manager->CreateExpandingBars(SCENES::SECOND_SCENE, 1.0f, true, 5, false, true);
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

		
		// --- TRANSITION WITH TEXTURE METHODS (NOT IMPLEMENTED)
		if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
		{
			if (scene_texture != nullptr)
			{
				App->transition_manager->CreateDissolve(SCENES::SECOND_SCENE, 1.0f);
			}
		}

		if (App->input->GetMouseButtonDown(SDL_BUTTON_MIDDLE) == KEY_DOWN)
		{
			iPoint mouse_pos = App->input->GetMouseToWorld();

			if (scene_texture != nullptr)
			{
				App->transition_manager->CreateZoomToTexture(SCENES::SECOND_SCENE, mouse_pos);
			}
		}
	}
}