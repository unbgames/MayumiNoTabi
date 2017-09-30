#include <componentInputControl.hpp>
#include <game.hpp>
//#include <camera.hpp>
//#include <inputManager.hpp>

CompInputControl::CompInputControl(function<void(GameObject*,float)> f):func{f}{}
CompInputControl::~CompInputControl() {}

void CompInputControl::update(float time) {
	func(GO(entity),time);
}
void CompInputControl::render() {}
Component::type CompInputControl::get_type()const{
	return Component::type::t_input_control;
}
