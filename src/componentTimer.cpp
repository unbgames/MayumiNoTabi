#include <componentTimer.hpp>
//#include <compLib.hpp>
#include <gameObject.hpp>
//#include <camera.hpp>
//#include <inputManager.hpp>


CompTimer::CompTimer(float l):limit{l}{}
CompTimer::~CompTimer() {}


void CompTimer::update(float time) {
	t.update(time);
	if (t.Get()>limit) {
		GO(entity)->dead=true;
	}
}


void CompTimer::render() {}


void CompTimer::own(GameObject* go) {
	entity=go->uid;
}


Component::type CompTimer::get_type() const{
	return Component::type::t_timer;
}


