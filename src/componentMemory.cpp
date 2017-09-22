/*
*  File: componentMemory.cpp
*
*  Description:  Implements componentMemory class
*/

#include <componentMemory.hpp>

// No params constructor method
CompMemory::CompMemory() {
}

// No params destructor method
CompMemory::~CompMemory() {
}

// Updates memory according to the time param
void CompMemory::Update(float time) {
	for(auto& t:timers)t.second.Update(time);
}

// Renders memory, obviously not necessary
void CompMemory::Render() {
}

// Returns if the component is if the 'memory' type
Component::type CompMemory::GetType() const {
	return Component::type::t_memory;
}
