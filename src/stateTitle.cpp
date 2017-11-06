#include <stateTitle.hpp>

#include <camera.hpp>
#include <complib.hpp>
#include <game.hpp>
#include <inputManager.hpp>
#include <stateStage.hpp>
#include <stateEditor.hpp>

#define BACKGROUND "img/tela-inicio2.png"
#define INSTRUCTION_TEXT "IDJ-Projeto\n\nPress [Space] to continue\n[E] Level Editor\n"

StateTitle::StateTitle():State::State(),bg{Sprite(BACKGROUND)},bt1{"img/botao-editor.png",2},bt2{"img/botao-inicio.png",2}{
	LoadAssets();
	
	bg.StretchToFit(WINSIZE);
}
StateTitle::~StateTitle() {}

void StateTitle::LoadAssets() {}
void StateTitle::LoadGUI() {}

void StateTitle::Begin() {
	//Create gameObjects here
	GameObject* text = new GameObject{Rect{(WINSIZE.x/2),(WINSIZE.y/2),0,0}};
	text->AddComponent(new CompText{INSTRUCTION_TEXT,36,SDL_COLOR_WHITE,Hotspot::CENTER});
	AddObject(text->uid);
}

void StateTitle::update(float time) {
	if (INPUT.get_quit_requested() || INPUT.key_pressed(KEY_ESC)) quit_requested=true;

	if (INPUT.key_pressed(KEY_SPACE)) {
		bt2.set_frame(1);
		GAMEINST.Push(new StateStage{"level_0"});
	}
	if (INPUT.key_pressed(KEY(e))) {
		bt1.set_frame(1);
		GAMEINST.Push(new StateEditor{});
	}
	UpdateArray(time);
}
void StateTitle::render() {
	bg.render(0,0);
	bt1.render(500,300);
	bt2.render(100,300);
	// RenderArray();
}

void StateTitle::Pause() {}
void StateTitle::Resume() {
	CAMERA.x=CAMERA.y=0;
}
