/*!
 *  @file File componentText.cpp
 *  @brief Implementation of the class of text components present in the game
 *
 *  The class implemented here provides to the game the messeges elements
 *
 *  Auxiliary documentation
 *  @sa componentText.hpp
 *
 *  @warning All variables are initialized
 */


#include <game.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <componentText.hpp>
//#include <inputManager.hpp>

//! Functions to be called by the methods in order to perform actions

void textPosition(){
	Vec2 p = pos + GO(entity)->Box().corner();
	txt.SetPos(p);

	if (GO(entity)->anchored) {
		txt.Render();
	}
	else {
		txt.Render(CAMERA);
	}
}


//! A constructor.
    /*!
    This is a constructor method of componentText class
    */
CompText::CompText(const Text &t, Hotspot h, Vec2 p):txt{t},pos{p}{
	txt.set_hotspot(h);
}

//! A constructor.
    /*!
    This is a another constructor method of componentText class
		with overload
    */
CompText::CompText(string text, int size, SDL_Color c, Hotspot h, Vec2 p):txt{text, size, c},pos{p}{
	txt.set_hotspot(h);
}

//! A destructor.
    /*!
      This is a destructor method of componentText class
    */
CompText::~CompText() {
	// Method body its empty
}

/*!
	@fn void CompMovement::Update(float time)
	@brief Method that update element movement
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/
void CompText::update(float time) {
	UNUSED(time);
}

/*!
	@fn void CompText::render()
	@brief Method that render the text messege
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompText::render() {
	textPosition()
}

/*!
	@fn Component::type CompText::get_type()const
	@brief Method that sets the text messege
	@return the type of the text messege
	@warning Method that requires review of comment
*/
Component::type CompText::get_type()const{
	return Component::type::t_text;
}
