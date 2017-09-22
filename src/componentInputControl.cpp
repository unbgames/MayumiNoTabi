/*
*  File: componentInputControl.cpp
*
*  Description:  Implements componentInputControl class
*/

#include <componentInputControl.hpp>
#include <game.hpp>

CompInputControl::CompInputControl(function<void(GameObject*,float)> f):func{f} {
}

// No params constructor method
CompInputControl::~CompInputControl() {
}

// Updates input control according to the time param
void CompInputControl::Update(float time) {
	func(GO(entity),time);
}

// Renders input control, obviously not necessary
void CompInputControl::Render() {
}

// Returns if the component is if the 'input control' type
Component::type CompInputControl::GetType()const{
	return Component::type::t_input_control;
}
