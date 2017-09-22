/*
 *  File: componentAI.cpp
 *
 *  Description:  Implements CompAI class
 */

#include <componentAI.hpp>
#include <game.hpp>

//#include <camera.hpp>
//#include <inputManager.hpp>

// TODO: Refactorate
// Constructor
// Recieves a aiFunc type param composed value and executes it
CompAI::CompAI(aiFunc func):foo{func} { // aiFunc=function<void(CompAI*,float)>;

}

// Destructor method
CompAI::~CompAI() {

}

// Updates the component ai based on the param
// Recieves a float number as a param that represents time
void CompAI::Update(float time) {
	foo(this,time);
}

// Renders component ai
void CompAI::Render() {

}

// Method that picks a component type and returns it
Component::type CompAI::GetType()const {
	return Component::type::t_ai;
}
