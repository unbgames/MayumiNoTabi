/*!
 *  \file File componentTimer.cpp
 *  \brief Implementation of the class of game time
 *
 *  The class implemented here provides to the game the time limit
 *
 *  \sa componentTimer.hpp
 */


#include <>
//#include <compLib.hpp>
#include <gameObject.hpp>
//#include <camera.hpp>
//#include <inputManager.hpp>

//! A constructor.
    /*!
    This is a constructor method of componentTimer class
    */
CompTimer::CompTimer(float l):limit{l}{}

//! A destructor.
    /*!
      This is a destructor method of componentText class
    */

CompTimer::~CompTimer() {}

/*!
	@fn CompTimer::Update(float time)
	@brief Method that update the game time
	and check the time limit
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/


void CompTimer::Update(float time) {
	t.Update(time);
	if (t.Get()>limit) {
		GO(entity)->dead=true;
	}
}

/*!
	@fn void CompTimer::Render()
	@brief Method that render the game time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/


void CompTimer::Render() {}

/*!
	@fn void CompTimer::Own(GameObject* go)
	@brief Method that monitor the game element
	@param GameObject* go
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/


void CompTimer::Own(GameObject* go) {
	entity=go->uid;
}

/*!
	@fn void CompMovement::Update(float time)
	@brief Method that sets the game time
	@return The method return the current time
	@warning Method that requires review of comment
*/


Component::type CompTimer::GetType() const{
	return Component::type::t_timer;
}
