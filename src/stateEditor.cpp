#include <stateEditor.hpp>

#include <common.hpp>

#include <camera.hpp>
#include <complib.hpp>
#include <game.hpp>
#include <resources.hpp>

#define HELP_TEXT "Press [H] for help"
#define HELP_TEXT_OPEN \
"S - Save\n\
G - Toggle grid\n\
LMB - Place tile\n\
RMB - Erase tile\n\
A - Previous tile\n\
D - Next tile\n\
C - Show Collision \n\
ARROW KEYS, MMB - Move Camera\n\
Z - Zoom In\n\
X - Zoom Out"

#define MIN_LVL_WIDTH (int)ceil(WINSIZE.x/64)
#define MIN_LVL_HEIGHT (int)ceil(WINSIZE.y/64)
#define MAX_LVL_SIZE 2000

#define EDITOR_BG_COLOR 127,127,127,255
#define GRID_COLOR 255,255,255,63
#define LEVEL_BORDER_COLOR 255,255,255,255
#define TILE_CURSOR_COLOR 255,255,0,255
#define COLLISION_COLOR 255,0,0,255

//TODO: Remove placeholder index
#define COLLISION_BLOCK 0

enum Action{
	NONE,
	NEW_LEVEL,
	LOAD_LEVEL,
	SAVE_LEVEL,
	RESIZE_LEVEL,
	SHOW_GRID,
	SHOW_COLLISION,
	EXIT_EDITOR,
	EXIT_GAME
};

enum Window{
	MAIN_WINDOW,
	RESIZE_WINDOW,
	UNSAVED_CHANGES_WINDOW
};

StateEditor::StateEditor():helpText{HELP_TEXT,16},statusText{"test",16}{
	LoadAssets();
}

StateEditor::~StateEditor() {}

void StateEditor::LoadAssets() {}

void StateEditor::Begin() {
	LoadGUI();
  
	level.load_level_from_file(fileName);
	level.load_level_objects(false);

	CAMERA = {-100, -100};
	CAMERAZOOM = 1.0f;
	SETTINGS.showHP = false;
	SETTINGS.showCollision = false;

	helpText.set_box_position(0,0);
	statusText.set_box_position(WINSIZE-Vec2(0,0));
	statusText.set_alignment(Text::Align::RIGHT);
	statusText.set_hotspot(Hotspot::BOTTOM_RIGHT);
}

void StateEditor::update(float time) {
	Camera::update(time);
	gui.update_gui_elements();
	if (INPUT.get_quit_requested() || gui.gui_button_was_clicked(EXIT_GAME)) {
		quit_requested = true;
		Exit();
	}

	auto window = gui.get_gui_selected_window_ID();
	if (window == MAIN_WINDOW) {
		//Close Editor
		if (INPUT.key_pressed(KEY_ESC) || gui.gui_button_was_clicked(EXIT_EDITOR)) {
			popRequested = true;
			Exit();
		}

		int tileCount = level.level_tile_set.GetTileCount();
    
		//Select next tile
		if (INPUT.key_pressed(KEY(a))) tileIndex = (tileIndex + tileCount-1)%tileCount;
		//Select previous tile
		if (INPUT.key_pressed(KEY(d))) tileIndex = (tileIndex + 1)%tileCount;

		//Place a tile
		if (INPUT.mouse_button_is_down(MBUTTON_LEFT)) {
			Vec2 cursor = GetCurrentTile();
			Rect canvas(0, 0, level.level_tile_map.GetWidth()-1, level.level_tile_map.GetHeight()-1);
			if (canvas.contains(cursor)) {
				if (showCollision) {
					level.collisionLayer[(cursor.y*level.level_tile_map.GetWidth())+cursor.x] = COLLISION_BLOCK;
				}
				else{
					level.level_tile_map.At(cursor.x, cursor.y, 0) = tileIndex;
				}
			}
		}
		//Erase a tile
		if (INPUT.mouse_button_is_down(MBUTTON_RIGHT)) {
			Vec2 cursor = GetCurrentTile();
			Rect canvas(0, 0, level.level_tile_map.GetWidth()-1, level.level_tile_map.GetHeight()-1);
			if (canvas.contains(cursor)) {
				if (showCollision) {
					level.collisionLayer[(cursor.y*level.level_tile_map.GetWidth())+cursor.x] = EMPTY_TILE;
				}
				else{
					level.level_tile_map.At(cursor.x, cursor.y, 0) = -1;
				}
			}
		}


		//Toggle grid
		if (INPUT.key_pressed(KEY(g)) || gui.gui_button_was_pressed(SHOW_GRID)) showGrid = (!showGrid);
		//Toggle instructions menu
		if (INPUT.key_pressed(KEY(h))) {
			showHelp = (!showHelp);
			if (showHelp) helpText.set_text(HELP_TEXT);
			else helpText.Set_text(HELP_TEXT_OPEN);
		}
		//Toggle collision boxes
		if (INPUT.key_pressed(KEY(c)) || gui.gui_button_was_clicked(SHOW_COLLISION)) showCollision = (!showCollision);

		//Save level
		if (INPUT.key_pressed(KEY(s)) || gui.gui_button_was_clicked(SAVE_LEVEL)) SaveLevel();
    
		//Resize level
		if (gui.gui_button_was_clicked(Action::RESIZE_LEVEL)) {
			CreateWindow(RESIZE_LEVEL);
		}

		//Pan view
		if (INPUT.mouse_button_pressed(MBUTTON_MIDDLE)) {
			clickPos = INPUT.get_mouse_position();
			camPos = CAMERA;
			CAMERALOCK = true;
		}
		else if (INPUT.mouse_button_is_down(MBUTTON_MIDDLE)) {
			CAMERA = camPos - ((INPUT.get_mouse_position()-clickPos)/CAMERAZOOM);
		}
		if (INPUT.mouse_button_released(MBUTTON_MIDDLE)) {
			CAMERALOCK = false;
		}
	}
	else if (window==RESIZE_WINDOW) {
		if (gui.gui_button_was_clicked(GUI_CONFIRM))
			ResizeLevel();
	}
	else if (window==UNSAVED_CHANGES_WINDOW) {
		if (gui.gui_button_was_clicked(GUI_CLOSE)) {
			popRequested = false;
			quit_requested = false;
		}
		else if (gui.gui_button_was_clicked(GUI_CONFIRM)) {
			SaveLevel();
			closeFlag = true;
		}
		else if (gui.gui_button_was_clicked(GUI_DENY)) {
			closeFlag = true;
		}
	}

	//UpdateArray(time);
	statusText.Set_text("Mouse:("+to_string(INPUT.get_mouse_positionX())+","+to_string(INPUT.get_mouse_positionY())+")  Zoom:"+convert_float_to_str(100*CAMERAZOOM)+"%");
}
void StateEditor::render() {
	RenderBackground();

	//Tirei background daqui
	//level.background.render(RENDERPOSX(0), RENDERPOSY(0), 0, CAMERAZOOM);
	level.level_tile_map.render();
  
	RenderArray();
	if (showGrid) RenderGrid(gridWidth, gridHeight);
	RenderBorder();
	if (showCollision) RenderCollision();
	RenderCursor();

	gui.render_gui_elements();
	//helpText.render();
	statusText.render();
}

void StateEditor::Pause() {}
void StateEditor::Resume() {}

bool StateEditor::PopRequested() {
	return (closeFlag && popRequested);
}
bool StateEditor::QuitRequested() {
	return (closeFlag && quit_requested);
}

//Editor Funtcions------------------------------------------------------------

void StateEditor::RenderBackground() {
	SET_COLOR(EDITOR_BG_COLOR);
	CLEAR_SCREEN();
}

void StateEditor::RenderGrid(int w, int h) {
	SET_COLOR(GRID_COLOR);

	if (w > 0) {
		int first = floor(CAMERA.x/w)*w;
		if (first>0) first+=w;
		int lim = CAMERA.x+(WINSIZE.x/CAMERAZOOM);
		for (int i=first;i<=lim;i+=w)
			DRAW_LINE(RENDERPOSX(i), 0, RENDERPOSX(i), WINSIZE.y);
	}
	if (h > 0) {
		int first = floor(CAMERA.y/h)*h;
		if (first>0) first+=h;
		int lim = CAMERA.y+(WINSIZE.y/CAMERAZOOM);
		for (int i=first;i<=lim;i+=h)
			DRAW_LINE(0, RENDERPOSY(i), WINSIZE.x, RENDERPOSY(i));
	}
}

void StateEditor::RenderBorder() {
	SET_COLOR(LEVEL_BORDER_COLOR);

	SDL_Rect rect;
	rect.x = RENDERPOSX(0);
	rect.y = RENDERPOSY(0);
  
	rect.w = (level.level_tile_map.GetWidth()*level.level_tile_set.GetWidth()*CAMERAZOOM);
	rect.h = (level.level_tile_map.GetHeight()*level.level_tile_set.GetHeight()*CAMERAZOOM);
	DRAW_RECT(&rect);
}

void StateEditor::RenderCursor() {
	Vec2 cursor = GetCurrentTile();

	int tileWidth = level.level_tile_set.GetWidth();
	int tileHeight = level.level_tile_set.GetHeight();
	int mapWidth = level.level_tile_map.GetWidth();
	int mapHeight = level.level_tile_map.GetHeight();

	Rect canvas(0, 0, mapWidth-1, mapHeight-1);
	if (canvas.contains(cursor)) {
		level.level_tile_set.render(tileIndex, RENDERPOSX(cursor.x*tileWidth), RENDERPOSY(cursor.y*tileHeight), CAMERAZOOM);

		SET_COLOR(TILE_CURSOR_COLOR);

		SDL_Rect rect;
		rect.x = RENDERPOSX(cursor.x*tileWidth);
		rect.y = RENDERPOSY(cursor.y*tileHeight);
		rect.w = (tileWidth*CAMERAZOOM)+1;
		rect.h = (tileHeight*CAMERAZOOM)+1;

		DRAW_RECT(&rect);
	}
}

void StateEditor::RenderCollision() {
	SET_COLOR(COLLISION_COLOR);

	int mapWidth = level.level_tile_map.GetWidth();
	int mapHeight = level.level_tile_map.GetHeight();
	int tileWidth = level.level_tile_set.GetWidth();
	int tileHeight = level.level_tile_set.GetHeight();
  
	SDL_Rect rect;
	rect.w = (tileWidth*CAMERAZOOM)+1;
	rect.h = (tileHeight*CAMERAZOOM)+1;
	FOR(y,mapHeight) {
		FOR(x,mapWidth) {
			if (level.collisionLayer[(y*mapWidth)+x] == COLLISION_BLOCK) {
				rect.x = RENDERPOSX(x*tileWidth);
				rect.y = RENDERPOSY(y*tileWidth);
				DRAW_RECT(&rect);
			}
		}
	}
}

void StateEditor::Exit() {
	Level savedLevel(fileName);
	RecomputeCollisionRectangles();

	level.save_level_objects(grouped);

	if (level == savedLevel)
		closeFlag = true;
	else
		CreateWindow(EXIT_EDITOR);
}

Vec2 StateEditor::GetCurrentTile() {
	Vec2 pos = CAMERA+(INPUT.get_mouse_position()/CAMERAZOOM);
	int tileWidth = level.level_tile_set.GetWidth();
	int tileHeight = level.level_tile_set.GetHeight();

	//if (pos.x<0) pos.x-=tileWidth;
	pos.x/=tileWidth;
	//if (pos.y<0) pos.y-=tileHeight;
	pos.y/=tileHeight;
	pos.floor();
	//cout<<"mouse "<<INPUT.get_mouse_positionX()<<" "<<INPUT.get_mouse_positionY()<<endl;
	//cout<<"tile "<<pos.x<<" "<<pos.y<<endl;
	return pos;
}

void StateEditor::SaveLevel() {
	RecomputeCollisionRectangles();
	level.save_level_objects(grouped);
	level.save_level_to_file(fileName);
}

void StateEditor::ResizeLevel() {
	int mapWidth = level.level_tile_map.GetWidth();
	int mapHeight = level.level_tile_map.GetHeight();

	level.level_tile_map.SetSize(levelWidth, levelHeight);

	vector<int> newCollisionLayer(levelWidth*levelHeight, EMPTY_TILE);
	int maxX = min(levelWidth, mapWidth);
	int maxY = min(levelHeight, mapHeight);

	FOR(y,maxY)
		FOR(x,maxX)
			newCollisionLayer[x+(y*levelWidth)] = level.collisionLayer[x+(y*mapWidth)];
	level.collisionLayer.clear();
	level.collisionLayer = newCollisionLayer;
}


void StateEditor::RecomputeCollisionRectangles() {
	TileMap &tm = level.level_tile_map;
	vector<int> &coll=level.collisionLayer;
	int mapWidth=tm.GetWidth();
	int mapHeight=tm.GetHeight();

	grouped.clear();
	grouped.resize(mapWidth*mapHeight);
	FOR(y,mapHeight) {
		FOR(x,mapWidth) {
			int ind = x+(y*mapWidth);
			grouped[ind]=make_pair(ii{x,y},ii{x,y});
		}
	}

	auto join = [this,mapWidth,mapHeight](int ind1,int ind2) {
		ii beg=min(grouped[ind1].first, grouped[ind2].first);
		ii end=max(grouped[ind1].second,grouped[ind2].second);

		int ind3=beg.first+(beg.second*mapWidth);
		int ind4=end.first+(end.second*mapWidth);

		grouped[ind1]=grouped[ind2]=grouped[ind3]=grouped[ind4]=make_pair(beg,end);
	};

	FOR(y,mapHeight) {
		FOR(x,mapWidth) {
			int ind = x+(y*mapWidth);
			if (coll[ind]==EMPTY_TILE)grouped[ind]=make_pair(ii{0,0},ii{0,0});
			else if (x+1 < mapWidth && coll[ind] == coll[1+ind]) {
				join(ind,ind+1);
			}
		}
	}

	FOR(y,mapHeight-1) {
		FOR(x,mapWidth) {
			int ind1 = x+( y   *mapWidth);
			int ind2 = x+((y+1)*mapWidth);
			if (grouped[ind1].first.first == grouped[ind2].first.first &&
				grouped[ind1].second.first == grouped[ind2].second.first) {
				join(ind1,ind2);
			}
		}
	}
}

void StateEditor::LoadGUI() {
	GUI_NEW;

	GUI_SET(menu);
	//GUI_ADD(GUI_TextButton(NEW_LEVEL, "New"));
	//GUI_ADD(GUI_TextButton(LOAD_LEVEL, "Load"));
	GUI_ADD(TextButton(SAVE_LEVEL, "Save"));
	GUI_DIV();
	GUI_ADD(TextButton(RESIZE_LEVEL, "Resize"));
	GUI_DIV();
	GUI_ADD(CheckButton(showGrid));
	GUI_ADD(Label("Show Grid", SNAP_LEFT));
	GUI_ADD(Label("Width:", SNAP_RIGHT));
	GUI_ADD(IntBox(gridWidth,2,INT_MAX,SHORT_SIZE));
	GUI_ADD(Label("px", SNAP_LEFT));
	GUI_ADD(Label("Height:", SNAP_RIGHT));
	GUI_ADD(IntBox(gridHeight,2,INT_MAX,SHORT_SIZE));
	GUI_ADD(Label("px", SNAP_LEFT));
	GUI_DIV();
	GUI_ADD(CheckButton(showCollision));
	GUI_ADD(Label("Show Collision", SNAP_LEFT));
	GUI_CREATE(HBar(GUI_GET(menu),WINSIZE.x));
}

void StateEditor::CreateWindow(uint type) {
	GUI_NEW;
	if (type==RESIZE_LEVEL) {
		levelWidth = level.level_tile_map.GetWidth();
		levelHeight = level.level_tile_map.GetHeight();

		GUI_SET(labels);
		GUI_ADD(Label("Width: "));
		GUI_ADD(Label("Height: "));

		GUI_SET(width_box);
		GUI_ADD(IntBox(levelWidth, MIN_LVL_WIDTH, MAX_LVL_SIZE));
		GUI_ADD(Label("tiles", SNAP_LEFT));

		GUI_SET(height_box);
		GUI_ADD(IntBox(levelHeight, MIN_LVL_HEIGHT, MAX_LVL_SIZE));
		GUI_ADD(Label("tiles", SNAP_LEFT));

		GUI_SET(input);
		GUI_ADD(HBar(GUI_GET(width_box)));
		GUI_ADD(HBar(GUI_GET(height_box)));

		GUI_SET(menu);
		GUI_ADD(VBar(GUI_GET(labels)));
		GUI_ADD(VBar(GUI_GET(input)));

		GUI_SET(window);
		GUI_ADD(HBar(GUI_GET(menu)));
		GUI_ADD(TextButton(GUI_CONFIRM, "Ok"));

		GUI_CREATE(Window(GUI_GET(window), RESIZE_WINDOW, "Resize Level"));
	}
	if (type==EXIT_EDITOR) {
		GUI_SET(buttons);
		GUI_ADD(TextButton(GUI_DENY,"  No  "));
		GUI_ADD(TextButton(GUI_CONFIRM,"  Yes  "));

		GUI_SET(window);
		GUI_ADD(Label(" Save changes before closing? "));
		GUI_ADD(HBar(GUI_GET(buttons)));

		GUI_CREATE(Window(GUI_GET(window), UNSAVED_CHANGES_WINDOW, "Exit Game"));
	}
}
