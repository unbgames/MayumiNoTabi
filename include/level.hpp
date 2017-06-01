#ifndef LEVELHPP
#define LEVELHPP

#include <common.hpp>

#include <sprite.hpp>
#include <tileMap.hpp>
#include <tileSet.hpp>

class Level {
	string backgroundFilename;
	string tileSetFilename;

	string remaining;//TODO: remove this after adding collision
public:
	Sprite background;
	TileSet tileSet;
	TileMap tileMap;
	vector<int> collisionLayer;
	
	Level();
	Level(string file,set<unique_ptr<GameObject>>* entities=nullptr);
	~Level();
	
	void Load(string file,set<unique_ptr<GameObject>>* entities=nullptr);
	void Save(string file,vector<pair<ii,ii>> grouped);
	
};
#endif //LEVELHPP
