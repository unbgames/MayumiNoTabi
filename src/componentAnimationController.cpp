/*!
 *  \file File componentAnimationController.cpp
 *  \brief Implementation of componentAnimationController class
 *
 *  The class implemented here is a controller for the animations
 *
 *  \sa componentAnimationController.hpp
 */

#include <componentAnimationController.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <game.hpp>
//#include <inputManager.hpp>

//! A constructor.
  /*!
  This is a constructor method of CompAnimControl class
  */

CompAnimControl::CompAnimControl(string file, CompCollider* coll) {
  // TODO: variable declaration indent and comment
	string name, animFile;

	ifstream in(ANIMATION_PATH + file + ".txt");

	// Checks if the animation's .txt file is already opened
	if (!in.is_open()) {
		cerr << "Erro ao abrir arquivo de grupo de animações '" << file << "'";
		cerr << endl;
	}
	else {
		in >> name >> animFile;

		animations[name] = make_unique<CompAnim>(animFile, coll);

		// TODO: fix variable value assignment
		cur = prev = name;

		while (in >> name >> animFile) {
			animations[name] = make_unique<CompAnim>(animFile,coll);
		}

		in.close();
	}
}

//! A destructor.
  /*!
  This is a destructor method of CompAnimControl class
  */

CompAnimControl::~CompAnimControl() {

}

/*!
	@fn       void CompAnimControl::ChangeCur(string anim, bool rep)
	@brief    Changes current animation
	@param    string anim, bool rep
	@return   void
	@warning  none
*/

void CompAnimControl::ChangeCur(string anim,
																bool rep) {		// repeats animation if true
	// Checks if animation has been found
	if (animations.count(anim)) {

		// TODO: add else (do nothing)
		// Checks if current animation is the one to be shown
		if (cur != anim) {

			// If true, makes the animation repeat itself
			if (repeat) {
				prev = cur;
			}

			repeat = rep;

			cur = anim;

			GetCur().SetCurFrame(0);
			GetCur().sp.looped = false;
			GetCur().Own(GO(entity));
		}
	}
	else {
		cerr << "Erro: Controle de animação nao tem animação '";
		cerr << anim;
		cerr << "' entity uid = " << entity << endl;
	}
}

/*!
	@fn       
	@brief    Returns current animation object
	@param    none
	@return   CompAnim& type animation object pointer
	@warning  none
*/

CompAnim& CompAnimControl::GetCur() {
	return *animations[cur];
}

/*!
	@fn       const string& CompAnimControl::GetCurName()const
	@brief    Returns current animation's name as a constant
	@param    none
	@return   const string with animation name
	@warning  none
*/

const string& CompAnimControl::GetCurName()const {
	return cur;
}

/*!
	@fn       string& CompAnimControl::GetCurName()
	@brief    Returns current animation's name
	@param    none
	@return   string with current animation's name
	@warning  none
*/

string& CompAnimControl::GetCurName() {
	return cur;
}

/*!
	@fn       void CompAnimControl::Update(float time)
	@brief    Updates the animation according to time
	@param    float value resembling time
	@return   void
	@warning  TODO: alternative flux in condition structures
*/

void CompAnimControl::Update(float time) {

  // TODO: else (do nothing)
  // Checks if current animation is in the 'library'
	if (animations.count(cur)) {
		GetCur().Update(time);
    
    // TODO: else (do nothing)
    // Checks if current animation is a looped type or set to repeat
		if (!repeat and GetCur().Looped()) {

      // Defines current frame as 'dead' if Mayumi dies
			if (dying) {
				cur = "dead";
			}
			else {
				GetCur().sp.looped = false;

				ChangeCur(prev);
				GetCur().Update(time);
			}
		}
	}
}

/*!
	@fn       void CompAnimControl::Render()
	@brief    Renders current animation
	@param    none
	@return   void
	@warning  TODO: alternative flux in condition structures
*/

void CompAnimControl::Render() {

  // TODO: else (do nothing)
  // Tries to find the current animation on animations vector, render if found
  if (animations.count(cur)) {
    GetCur().Render();
  }
}

/*!
	@fn       void CompAnimControl::Own(GameObject *go)
	@brief    Sets ownage of animation to a Game Object
	@param    GameObject object
	@return   void
	@warning  none
*/

void CompAnimControl::Own(GameObject *go) {
	entity = go->uid;

  for (auto &anim:animations) {
		anim.second->Own(go);
	}

	GetCur().Own(go);
}

/*!
	@fn       bool CompAnimControl::Die(float time)
	@brief    Method for rendering player's death animation
	@param    float time value
	@return   boolean value
	@warning  TODO: alternative flux in condition structures
*/

bool CompAnimControl::Die(float time) { // range: unknown
	UNUSED(time);

	// TODO: else (do nothing)
  // Checks if die animation isn't in animations
	if (!animations.count("die")) {
		return true;
	}

	// Checks if player is dying
	if (dying) {

    // TODO: else (do nothing)
    // Makes method return true if current animation isn't player's death
		if (cur != "die") {
			return true;
		}
	}
	else {
		ChangeCur("die", false);

		dying = true;
	}

	return false;
}

/*!
	@fn       Component::type CompAnimControl::GetType()const
	@brief    Returns type of component (or animation) as a constant
	@param    none
	@return   const Component::type
	@warning  none
*/
// Returns type of component (or animation) as a constant
Component::type CompAnimControl::GetType()const {
	return Component::type::t_animation_control;
}
