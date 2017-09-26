/*!
 *  \file File component.cpp
 *  \brief Implementation of Component class
 *
 *  Here is the implementation of Component's methods
 *
 *  \sa component.hpp
 */

#include <component.hpp>
#include <gameObject.hpp>

/*!
	@fn       void Component::Own(GameObject *go)
	@brief    Assigns a object as property (like a ownage thing) of a component
	@param    GameObject *go
	@return   void
	@warning  none
*/

void Component::Own(GameObject *go) {
    entity = go->uid;
}

/*!
	@fn       bool Component::Die(float time)
	@brief    Sets the death of a component
	@param    float time
	@return   boolean value
	@warning  none
*/

bool Component::Die(float time) {
    UNUSED(time);

    return true;
}
