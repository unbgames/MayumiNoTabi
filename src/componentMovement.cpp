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


void CompMovement::Update(float time) {
	UNUSED(time);
	GO(entity)->pos+=move;
	if (mType==moveType::t_bullet)GO(entity)->rotation=speed.angle();
}
void CompMovement::Render() {}
Component::type CompMovement::GetType()const{
	return Component::type::t_movement;
}
