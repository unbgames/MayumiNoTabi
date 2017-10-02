#include <componentMemory.hpp>
//#include <compLib.hpp>
//#include <game.hpp>
//#include <camera.hpp>
//#include <inputManager.hpp>


CompMemory::CompMemory() {}
CompMemory::~CompMemory() {}

void CompMemory::update(float time) {
	for (auto& t:timers)t.second.update(time);
}
void CompMemory::render() {}
Component::type CompMemory::get_type() const{
	return Component::type::t_memory;
}
