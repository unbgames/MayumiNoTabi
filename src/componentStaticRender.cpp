/*!
 *  @file File componentStaticRender.cpp
 *  @brief Implementation of the class of static components in the game
 *
 *  The class implemented here provides to the game the position of the static elements
 *
 *
 *  Auxiliary documentation
 *  @sa componentStaticRender.hpp
 *
 *  @warning All variables are initialized
 */

#include <game.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <componentStaticRender.hpp>
//#include <inputManager.hpp>

//! Functions to be called by the methods in order to perform actions

void camScaling(Vec2 position){

	position = GO(entity)->Box().corner() + position.rotate(GO(entity)->rotation);
	sprite.SetFlipH(GO(entity)->flipped);

	if (camScaling) {
			sprite.Render((position-CAMERA)*CAMERAZOOM,GO(entity)->rotation, CAMERAZOOM);
	}
	else {
			sprite.Render(position,GO(entity)->rotation, 1);
	}
}




//! A constructor.
    /*!
    This is a constructor method of componentStaticRender class
    */

CompStaticRender::CompStaticRender(const Sprite &sprite,
	                                 const Vec2 &position,
																	 const bool camerascaling):sprite{sprite},position{position},
																	 cameraScaling{camerascalin}{

		// Method body its empty
}

//! A destructor.
    /*!
      This is a destructor method of componentStaticRender class
    */
CompStaticRender::~CompStaticRender() {
	// Method body its empty
}

/*!
	@fn CompStaticRender::Update(float time)
	@brief Method that update the current time of Sprite apparition
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/
void CompStaticRender::update(float time) {
	sp.update(time);
}

/*!
	@fn CompStaticRender::Render()
	@brief Method that render a static element
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompStaticRender::render() {

	Vec2 position = position;
	camScaling(position);

}

/*!
	@fn Component::type CompStaticRender::get_type()const
	@brief Method that render the type element movement
	@return The method returns the type of movement of the static element
	@warning Method that requires review of comment
*/
Component::type CompStaticRender::get_type()const{
	return Component::type::t_static_render;
}
