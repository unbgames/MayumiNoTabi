/*!
 *  \file File componentMovement.cpp
 *  \brief Implementation of the class of component movements present in the game
 *
 *  The class implemented here provides to the game the speed and type
 *  of movement that a given element can perform
 *
 *  \sa componentMovement.h
 */

#include <componentMovement.hpp>
#include <gameObject.hpp>
#include <game.hpp>
//#include <camera.hpp>
//#include <inputManager.hpp>

//! A constructor.
    /*!
    This is a constructor method os componentMovement class
    */
CompMovement::CompMovement(const Vec2& s,moveType t):mType{t},speed{s}{}
//! A destructor.
    /*!
      This is a destructor method os componentMovement class
    */
CompMovement::~CompMovement() {}


/*!
	@fn void CompMovement::Update(float time)
	@brief Method that update element movement
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompMovement::Update(float time) {
	UNUSED(time);
	GO(entity)->pos+=move;
	if (mType==moveType::t_bullet)GO(entity)->rotation=speed.angle();
}

/*!
	@fn void CompMovement::Render()
	@brief Method that render the new element movement
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompMovement::Render() {}

/*!
	@fn Component::type CompMovement::GetType()const
	@brief Method that sets the type of movement
	@return Component class object
	@warning Method that requires review of comment
*/

Component::type CompMovement::GetType()const{
	return Component::type::t_movement;
}
