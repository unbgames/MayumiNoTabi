#include <componentText.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <game.hpp>
//#include <inputManager.hpp>

CompText::CompText(const Text &t,Hotspot h,Vec2 p):txt{t},pos{p}{
	txt.set_hotspot(h);
}
CompText::CompText(string text,int size,SDL_Color c,Hotspot h,Vec2 p):txt{text,size,c},pos{p}{
	txt.set_hotspot(h);
}
CompText::~CompText() {}


void CompText::update(float time) {
	UNUSED(time);
}
void CompText::render() {
	Vec2 p = pos + GO(entity)->Box().corner();
	txt.set_box_positionos(p);

	if (GO(entity)->anchored) txt.render();
	else txt.render(CAMERA);
}
Component::type CompText::get_type()const{
	return Component::type::t_text;
}
