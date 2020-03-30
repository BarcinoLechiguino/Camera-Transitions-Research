#ifndef __MAP_H__
#define __MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2Point.h"
#include "Module.h"

// ----------------------------------------------------
struct Properties
{
	struct Property
	{
		std::string	name;
		int			value;
	};

	~Properties()
	{
		std::list<Property*>::iterator item = list.begin();

		while(item != list.end())
		{
			RELEASE((*item));
			++item;
		}

		list.clear();
	}

	int Get(const char* name, int default_value = 0) const;

	std::list<Property*>	list;
};

// ----------------------------------------------------
struct MapLayer
{
	std::string	name;
	int			width;
	int			height;
	uint*		data;
	Properties	properties;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	inline uint Get(int x, int y) const
	{
		return data[(y*width) + x];
	}
};

// ----------------------------------------------------
struct TileSet
{
	SDL_Rect GetTileRect(int id) const;

	std::string			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int						width;
	int						height;
	int						tile_width;
	int						tile_height;
	SDL_Color				background_color;
	MapTypes				type;
	std::list<TileSet*>		tilesets;
	std::list<MapLayer*>	layers;
};

// ----------------------------------------------------
class Map : public Module
{
public:

	Map();

	// Destructor
	virtual ~Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw(/*SDL_Renderer* renderer = App->render->renderer*/);

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);


	void DrawToSubRenderer(SDL_Renderer* sub_renderer, SDL_Texture* tileset_texture);				// Will draw the map into a Sub-Renderer. Needed to make a texture from the scene.
																									// Only accepts one tileset texture.

	void GetMapSize(int& w, int& h) const;
	void GetTileOffset(int& w, int& h) const;

	iPoint MapToWorld(int x, int y) const;
	iPoint WorldToMap(int x, int y) const;

	TileSet* GetTilesetFromTileId(int id) const;

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadProperties(pugi::xml_node& node, Properties& properties);

	//TileSet* GetTilesetFromTileId(int id) const;

public:

	MapData data;

private:

	pugi::xml_document	map_file;
	std::string			folder;
	bool				map_loaded;
};

#endif // __MAP_H__