/*
 *  File: component.cpp
 *
 *  Description:  Implements Component class
 */

#include <component.hpp>
#include <gameObject.hpp>

// Assigns a object as property (like a ownage) of a component
// Recieves a game object as param
void Component::Own(GameObject *go) {
	entity = go->uid;
}

// Kills a component
// Recieves a float number resembling time as a param
bool Component::Die(float time) {
	UNUSED(time);

	return true;
}
