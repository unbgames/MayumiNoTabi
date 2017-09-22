/*
 *  File: componentAnimationController.cpp
 *
 *  Description:  Implements CompAnimControl class
 */

#include <componentAnimationController.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <game.hpp>
//#include <inputManager.hpp>

// Constructor method for CompAnimControl
// Recieves a file name and a CompCollider object as params
CompAnimControl::CompAnimControl(string file, CompCollider* coll) {
	// TODO: variable declaration
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

// Destructor method for CompAnimControl
CompAnimControl::~CompAnimControl() {

}

// Changes current animation
// Recieves the name of the animaton and a boolean value
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

// Returns current animation object
CompAnim& CompAnimControl::GetCur() {
	return *animations[cur];
}

// Returns current animation's name as a constant
const string& CompAnimControl::GetCurName()const {
	return cur;
}

// TODO: evaluate the necessity of the method below
// Returns current animation's name
string& CompAnimControl::GetCurName() {
	return cur;
}

// Updates the animation according to time
// Recieves time as a param in float format
void CompAnimControl::Update(float time) {

  // Checks if current animation is in the 'library'
	if (animations.count(cur)) {
		GetCur().Update(time);

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

// Renders current animation
void CompAnimControl::Render() {

  // TODO: else (do nothing)
  // Tries to find the current animation on animations vector, render if found
  if (animations.count(cur)) {
    GetCur().Render();
  }
}

// Sets ownage of animation to a Game Object
void CompAnimControl::Own(GameObject *go) {
	entity = go->uid;

	for (auto &anim:animations) {
		anim.second->Own(go);
	}

	GetCur().Own(go);
}

// Method for rendering player's death animation
// Recieves a float param that defines time
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

// Returns type of component (or animation) as a constant
Component::type CompAnimControl::GetType()const {
	return Component::type::t_animation_control;
}
