#include <tileMap.hpp>

#include <camera.hpp>
#include <componentCollider.hpp>
#include <componentStaticRender.hpp>
#include <game.hpp>
#include <gameObject.hpp>
#include <tileSet.hpp>

TileMap::TileMap(int width, int height, TileSet* tile_set) : tileSet{tile_set},map_width{width},map_height{height},map_depth{1} {
	tile_matrix.reserve(map_width*map_height);
	FOR(height_counter, map_height)
		FOR(width_counter, map_width)
			at(width_counter, height_counter, 0) = EMPTY_TILE;
}
TileMap::TileMap(TileSet* tile_set):tileSet{tile_set}{
}

void TileMap::load(ifstream& input_file) {
	string line;

	getline(input_file,line);
	sscanf(line.c_str()," %d,%d,%d",&map_width,&map_height,&map_depth);

	tile_matrix.clear();
	tile_matrix.reserve(map_width*map_height*map_depth);

	int t;
	FOR(d,map_depth) {
		FOR(h,map_height) {
			FOR(w,map_width) {
				input_file >> t;
				input_file.ignore(1);
				at(w,h,d) = t-1;
			}
		}
	}
}
void TileMap::save(stringstream& output_file) {
	output_file<<map_width<<","<<map_height<<","<<map_depth<<endl<<endl;

	FOR(depth_counter,map_depth) {
		FOR(height_counter,map_height) {
			FOR(width_counter,map_width) {
				output_file<<at(width_counter,height_counter,depth_counter)+1<<",\t";
			}
			output_file<<endl;
		}
		output_file<<endl;
	}
}

void TileMap::set_tile_set(TileSet* tile_set) {
	this.tile_set = tile_set;
}

int& TileMap::at(int position_x,int position_y,int position_z) {
	return tile_matrix[position_x+(position_y*map_width)+(position_z*map_width*map_height)];
}
int TileMap::at(int position_x,int position_y,int position_z) const{
	return tile_matrix[position_x+(position_y*map_width)+(position_z*map_width*map_height)];
}

void TileMap::render_layer(int layer,int position_x ,int position_y) {
	int width=tile_set->get_width();
	int height=tile_set->get_height();
	int tile;
	int firstX=0,firstY=0,lastX=map_width,lastY=map_height;

	if (position_x<CAMERA.x)
		firstX = (CAMERA.x-position_x)/width;
	if (position_y<CAMERA.y)
		firstY = (CAMERA.y-position_y)/height;
	Vec2 mapCorner = Vec2(position_x+(map_width*width),position_y+(map_height*height));
	Vec2 cameraCorner = CAMERA+(WINSIZE/CAMERAZOOM);
	if (mapCorner.x>cameraCorner.x)
		lastX -= (mapCorner.x-cameraCorner.x)/width;
	if (mapCorner.y>cameraCorner.y)
		lastY -= (mapCorner.y-cameraCorner.y)/height;

	for (int y_counter=firstY;y_counter<=lastY;y_counter++) {
		for (int x_counter=firstX;x_counter<=lastX;x_counter++) {
			tile = at(x_counter, y_counter, layer);
			if (tile != EMPTY_TILE)
				tile_set->render(tile, RENDERPOSX(position_x+(x_counter*width)), RENDERPOSY(position_y+(y_counter*height)), CAMERAZOOM);
		}
	}
}
void TileMap::render(Vec2 position) {
	FOR(depth_counter,map_depth) {
		RenderLayer(depth_counter,positions.x,positions.y);
	}
}

int TileMap::get_width() const{
	return map_width;
}
int TileMap::get_height() const{
	return map_height;
}
int TileMap::get_depth() const{
	return map_depth;
}

void TileMap::change_size(int new_width,int new_height) {
	vector<int> new_matrix(new_width*new_height*map_depth, EMPTY_TILE);
	int max_x = min(new_width, map_width);
	int max_y = min(new_height, map_height);

	FOR(depth_counter,map_depth)
		FOR(height_counter,maxY)
			FOR(width_counter,maxX)
				new_matrix[width_counter+(height_counter*new_width)+(depth_counter*new_width*new_height)] = at(width_counter,height_counter,depth_counter);

	map_width = new_width;
	map_height = new_height;
	tile_matrix.clear();
	tile_matrix = new_matrix;
}
