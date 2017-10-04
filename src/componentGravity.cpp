#include <componentGravity.hpp>
#include <componentMovement.hpp>
#include <gameObject.hpp>
#include <game.hpp>
//#include <camera.hpp>
//#include <inputManager.hpp>

CompGravity::CompGravity(float g):gravity{g}{}
CompGravity::~CompGravity() {}


void CompGravity::update(float time) {
	if (GO(entity)->HasComponent(Component::type::t_movement)) {
		COMPMOVEp(GO(entity))->speed.y+=gravity*time;
	}
}
void CompGravity::render() {}
Component::type CompGravity::get_type() const{
	return Component::type::t_gravity;
}
