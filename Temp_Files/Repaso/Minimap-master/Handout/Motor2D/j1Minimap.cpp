#include "j1Minimap.h"

#include "j1App.h"
#include "j1Window.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"

#include "j1Map.h"
#include "j2Entity.h"
#include "j2EntityManager.h"

#include "p2Log.h"

#include <list>

j1Minimap::j1Minimap()
{
	name = "minimap";
}

j1Minimap::~j1Minimap() {}

bool j1Minimap::Awake(pugi::xml_node & config)
{
	minimap_width = config.attribute("width").as_int();
	minimap_height = config.attribute("height").as_int();

	return true;
}

bool j1Minimap::Start()
{
	if (App->map->active) 
	{
		// TODO 1: Initialize the variable "map_width" to obtain the width of the map in pixels
		// Initialize the variable "minimap_scale" to get the relation between the map width and
		// the minimap width (defined at config.xml and initialized in Awake())

		map_width = App->map->data.width * App->map->data.tile_width;								// Could also use map_height = App->map->data.height * App->map->data.tile_height;
		minimap_scale = minimap_width / map_width;													// Could also use minimap_height / map_height.
		
		///Uncomment the lines below once you have finished TODO 1									// Instead of just using tile_width * 0.5, minimap_scale is also added to the calculus.(?)
		x_offset = App->map->data.tile_width / 2 * minimap_scale;									// X = (x - y) * (tile_width * 0.5 * minimap_scale);
		y_offset = App->map->data.tile_height / 2 * minimap_scale;									// Y = (x + y) * (tile_height * 0.5 * minimap_scale);
		

		// TODO 2: Use the function SDL_CreateRGBSurface() to allocate a RGB surface to the variable "map_surface"
		// The last four parameters should be: 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000 in order to be totally transparent
		// You have to add the x & y offsets

		int minimap_surface_width = minimap_width + x_offset;
		int minimap_surface_height = minimap_height + y_offset;
		
		uint r = 0x00ff0000; 
		uint g = 0x0000ff00;
		uint b = 0x000000ff; 
		uint a = 0xff000000;
		
		map_surface = SDL_CreateRGBSurface(0, minimap_surface_width, minimap_surface_height, 32, r, g, b,a);

		
		// TODO 3: Use the function SDL_CreateSoftwareRenderer() to create a 2D software rendering context for a surface
		// Assign it to the variable "map_renderer"

		map_renderer = SDL_CreateSoftwareRenderer(map_surface);
		
		
		tex = App->tex->Load("maps/isometric_grass_and_water.png"/*, map_renderer*/);								//Loading tileset sprites.
	}
	
	DrawMinimap();

	// TODO 5: Use the function SDL_CreateTextureFromSurface to create a texture from an existing surface
	// Assign it to the variable "map_tex". Use the renderer from render.h
	
	minimap_tex = SDL_CreateTextureFromSurface(App->render->renderer, map_surface);

	return true;
}


bool j1Minimap::Update(float dt)
{	
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
	{
		int map_x, map_y;
		
		if (MinimapCoords(map_x, map_y))
		{
			// TODO 10: Assign to the center of the camera, the coordinates "map_x" and "map_y"
			App->render->camera.x = -(map_x - App->render->camera.w * 0.5);
			App->render->camera.y = -(map_y + App->render->camera.h * 0.5);
		}
	}

	return true;
}

bool j1Minimap::PostUpdate()
{	
	App->render->Blit(minimap_tex, 0, 0, NULL, false);
	
	MinimapBorders();
	DrawEntities();
	DrawCamera();
	
	return true;
}

bool j1Minimap::CleanUp()
{
	App->tex->UnLoad(tex);
	App->tex->UnLoad(minimap_tex);

	if (SDL_RenderClear(map_renderer) == 0)
		map_renderer = nullptr;

	SDL_DestroyTexture(minimap_tex);
	SDL_FreeSurface(map_surface);

	return true;
}

bool j1Minimap::MinimapCoords(int& map_x, int& map_y)
{
	int mouse_x, mouse_y;
	App->input->GetMousePosition(mouse_x, mouse_y);

	if (mouse_x >= 0 && mouse_x <= minimap_width &&	mouse_y >= 0 && mouse_y <= minimap_height)
	{
		// TODO 9: Assign to "map_x" and "map_y" the mouse position respect the minimap, to the
		// position that corresponds to the map
		// Take into account that it is an isometric map

		map_x = (mouse_x - minimap_width * 0.5) / minimap_scale;
		map_y = (mouse_y - minimap_height * 0.5) / minimap_scale;
	}
	else
	{
		return false;
	}

	return true;
}

void j1Minimap::DrawMinimap()
{
	std::list<MapLayer*>::const_iterator item = App->map->data.layers.cbegin();

	for (; item != App->map->data.layers.end(); item = next(item))
	{
		MapLayer* layer = *item;

		for (int y = 0; y < App->map->data.height; ++y)
		{
			for (int x = 0; x < App->map->data.width; ++x)
			{
				int tile_id = layer->Get(x, y);
				if (tile_id > 0)
				{
					TileSet* tileset = App->map->GetTilesetFromTileId(tile_id);

					SDL_Rect r = tileset->GetTileRect(tile_id);
					iPoint pos = App->map->MapToWorld(x, y);
					
					pos.x *= minimap_scale;
					pos.y *= minimap_scale;

					// TODO 4: Blit the minimap. You need to pass all the parameters until renderer included.
					// As it is an isometric map, keep in mind that x == 0 is in the middle of the map.

					App->render->Blit(tex, pos.x + minimap_width * 0.5, pos.y, &r, false, map_renderer, minimap_scale);
				}
			}
		}
	}
}

void j1Minimap::DrawCamera()
{
	// TODO 8: Fill the parameters of "map_camera"	to see in the minimap which part of the map are you seeing
	// Take into account that it is an isometric map
	// Reminder: The camera values are negative
	/// Uncomment the  line below
	
	SDL_Rect map_camera = {
		-App->render->camera.x * minimap_scale + minimap_width * 0.5, 
		-App->render->camera.y * minimap_scale, 
		App->render->camera.w * minimap_scale,
		App->render->camera.h * minimap_scale
	};
	
	/// Uncomment the line below once you have finished TODO 8
	
	App->render->DrawQuad(map_camera, 255, 255, 0, 255, false, false);
	
}

void j1Minimap::MinimapBorders()
{
	App->render->DrawLine(x_offset, minimap_height / 2 + y_offset, minimap_width / 2 + x_offset, y_offset, 255, 255, 255, 255, false);
	App->render->DrawLine(minimap_width + x_offset, minimap_height/ 2 + y_offset, minimap_width / 2 + x_offset, y_offset, 255, 255, 255, 255, false);
	App->render->DrawLine(minimap_width + x_offset, minimap_height / 2 + y_offset, minimap_width / 2 + x_offset, minimap_height + y_offset, 255, 255, 255, 255, false);
	App->render->DrawLine(x_offset, minimap_height / 2 + y_offset, minimap_width / 2 + x_offset, minimap_height + y_offset, 255, 255, 255, 255, false);
}

void j1Minimap::DrawEntities()
{
	int pos_x, pos_y;

	for (std::list<j2Entity*>::iterator item = App->entity_manager->entities.begin(); item != App->entity_manager->entities.end(); ++item) 
	{
		// TODO 6: Initialize the variables "pos_x" and "pos_y" to get the position of an entity IN the minimap
		
		pos_x = (*item)->position.x * minimap_scale + minimap_width * 0.5;
		pos_y = (*item)->position.y * minimap_scale;

		// TODO 7: Fill the missing parameters of DrawQuad() function.
		// Take into account that it is an isometric map
		// Uncomment the lines below

		if ((*item)->type == ENTITY_TYPE::ENEMY)
			App->render->DrawQuad({ pos_x, pos_y - y_offset, 4, 4 }, 255, 0, 0, 255, true, false);
		
		else if ((*item)->type == ENTITY_TYPE::PLAYER)
			App->render->DrawQuad({ pos_x, pos_y - y_offset, 4, 4 }, 0, 255, 0, 255, true, false);
	}
}


