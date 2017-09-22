/*!
 *  \file File componentStaticRender.cpp
 *  \brief Implementation of the class of static components in the game
 *
 *  The class implemented here provides to the game the position of the static elements
 *
 *
 *  Auxiliary documentation
 *  \sa componentStaticRender.hpp
 */

#include <componentStaticRender.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <game.hpp>
//#include <inputManager.hpp>


//! A constructor.
    /*!
    This is a constructor method of componentStaticRender class
    */

CompStaticRender::CompStaticRender(const Sprite &s,const Vec2 &p, const bool cs):sp{s},pos{p}, camScaling{cs}{}

//! A destructor.
    /*!
      This is a destructor method of componentStaticRender class
    */

CompStaticRender::~CompStaticRender() {}

/*!
	@fn CompStaticRender::Update(float time)
	@brief Method that update the current time of Sprite apparition
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompStaticRender::Update(float time) {
	sp.Update(time);
}

/*!
	@fn CompStaticRender::Render()
	@brief Method that render a static element
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompStaticRender::Render() {
	Vec2 p = pos;
	p = GO(entity)->Box().corner() + p.rotate(GO(entity)->rotation);
	sp.SetFlipH(GO(entity)->flipped);
	if (camScaling) sp.Render((p-CAMERA)*CAMERAZOOM,GO(entity)->rotation, CAMERAZOOM);
	else sp.Render(p,GO(entity)->rotation, 1);
}

/*!
	@fn Component::type CompStaticRender::GetType()const
	@brief Method that render the type element movement
	@return The method returns the type of movement of the static element
	@warning Method that requires review of comment
*/

Component::type CompStaticRender::GetType()const{
	return Component::type::t_static_render;
}
