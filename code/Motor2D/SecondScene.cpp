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

	App->tex->UnLoad(scene_texture);
	App->tex->UnLoad(tileset_texture);

	if (SDL_RenderClear(scene_renderer) == 0)
	{
		scene_renderer = nullptr;
	}

	SDL_DestroyTexture(scene_texture);
	SDL_FreeSurface(scene_surface);

	return ret;
}

void SecondScene::InitScene()
{
	App->map->GetMapSize(map_width, map_height);
	App->map->GetTileOffset(x_offset, y_offset);

	/*App->render->camera.x = map_width * 0.5f;												// This camera position is to have the renderer render all the scene_texture.
	App->render->camera.y = 0;

	SceneToTexture();*/

	App->render->camera.x = map_width * 0.3f;												// This camera position gets the camera close to the center of the map.
	App->render->camera.y = -40;
}

void SecondScene::DrawScene()
{
	App->map->Draw();

	if (scene_texture != nullptr)
	{
		//App->render->Blit(scene_texture, -(map_width) * 0.5f, 0, NULL);
	}
}

SDL_Texture* SecondScene::SceneToTexture()
{
	App->render->CreateSubRenderer(map_width + x_offset, map_height + y_offset, scene_surface, scene_renderer);		// Both scene_surface and scene renderer are passed by reference.

	tileset_texture = App->tex->Load("maps/isometric_grass_and_water.png", scene_renderer);
	App->map->DrawToSubRenderer(scene_renderer, tileset_texture);

	scene_texture = SDL_CreateTextureFromSurface(App->render->renderer, scene_surface);

	return scene_texture;
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
			App->transition_manager->CreateFadeToColour(SCENES::FIRST_SCENE);
		}

		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{
			App->transition_manager->CreateSlide(SCENES::FIRST_SCENE, 0.5f, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		{
			App->transition_manager->CreateWipe(SCENES::FIRST_SCENE, 0.5f, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		{
			App->transition_manager->CreateAlternatingBars(SCENES::FIRST_SCENE, 0.5f, true);
		}

		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		{
			App->transition_manager->CreateExpandingBars(SCENES::FIRST_SCENE, 0.5f, true);
		}

		if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
		{
			iPoint mouse_pos = App->input->GetMouseToWorld();

			App->transition_manager->CreateZoomToMouse(SCENES::FIRST_SCENE, mouse_pos, 0.5f, true);
		}

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			iPoint mouse_pos = App->input->GetMouseToWorld();

			App->transition_manager->CreateCameraToMouse(mouse_pos, 0.5f, false);
		}

		
		// --- TRANSITION WITH TEXTURE METHODS (NOT IMPLEMENTED)
		if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
		{
			if (scene_texture != nullptr)
			{
				App->transition_manager->CreateDissolve(SCENES::FIRST_SCENE, 1.0f);
			}
		}

		if (App->input->GetMouseButtonDown(SDL_BUTTON_MIDDLE) == KEY_DOWN)
		{
			iPoint mouse_pos = App->input->GetMouseToWorld();

			if (scene_texture != nullptr)
			{
				App->transition_manager->CreateZoomToTexture(SCENES::FIRST_SCENE, mouse_pos);
			}
		}
	}
}