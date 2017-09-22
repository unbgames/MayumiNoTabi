/*
*  File: componentGravity.cpp
*
*  Description:  Implements CompGravity class
*/

#include <componentGravity.hpp>
#include <componentMovement.hpp>
#include <gameObject.hpp>
#include <game.hpp>

// Constructor Method for component collider
// Takes a floating value as a param to represent gravity

CompGravity::CompGravity(float g):gravity{g} {
}
// No params constructor method
CompGravity::~CompGravity() {
}

// Updates the current gravity value according the 'time' param
void CompGravity::Update(float time) {
	// Verifies if element has a type that characterizes movement in Y axis
	if(GO(entity)->HasComponent(Component::type::t_movement)) {
		COMPMOVEp(GO(entity))->speed.y+=gravity*time;
	}
}

// Renders gravity on screen, obviously not needed
void CompGravity::Render() {
}

// Returns if the component is if the 'gravity' type
Component::type CompGravity::GetType() const {
	return Component::type::t_gravity;
}
