/*!
 *  \file File componentAnimation.cpp
 *  \brief Implementation of CompAnim class
 *
 *  This file has the implementation of CompAnim class
 *
 *  \sa componentAnimation.hpp
 */

#include <componentAnimation.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <complib.hpp>
#include <game.hpp>
#include <stateStage.hpp>
#include <txtFuncs.hpp>
// #include <inputManager.hpp>

//! A constructor.
  /*!
  This is a constructor method of CompAnim class
  */

// Constructor method with no params
CompAnim::CompAnim() {

}

//! A constructor.
  /*!
   This is a constructor method of CompAnim class
  */

CompAnim::CompAnim(string filename, CompCollider* temporary_collider) {
  assert(filename != "");
  assert(temporary_collider != NULL);

  string name = "";
  string img_file = "";
  string function_name = "";
  string animFile = "";
  string type = "";

  int f_count = 0;
  int f_counter_x = 0;
  int f_counter_y = 0;
  int collider_counter = 0;
  int function_counter = 0;

  float f_timex_axis = 0f;
  float y_axis = 0f;
  float width = 0f;
  float height = 0f;
  float r = 0f;

	ifstream in(ANIMATION_PATH + filename + ".txt");

	// Treats possible file opening error
	if (!in.is_open()) {
		cerr << "Erro ao abrir arquivo de animação '" << filename << "'" << endl;
	}
	else {
		in >> img_file >> f_count >> f_counter_x >> f_counter_y >> f_time;

		sp.Open(img_file, f_counter_x, f_counter_y, f_time, f_count);

		colliders.resize(f_count, nullptr);

		FOR(i, f_count) {
			in >> collider_counter;

			if (collider_counter) {
				colliders[i] = new CompCollider{};
				colliders[i]->entity = entity;

				FOR(j, collider_counter) {
					//TODO: use rotation
					//TODO: different collider types for each coll
					in >> x_axis >> y_axis >> width >> height >> r;

          colliders[i]->colls.emplace_back(entity, 
                                           temporary_collider->colls[0].cType,
                                           Rect{x_axis, y_axis, width, height});

					colliders[i]->colls[j].useDefault = temporary_collider->colls[0].useDefault;
					colliders[i]->colls[j].active = temporary_collider->colls[0].active;
				}
      }
      else {
        // Do nothing
      }

			in >> function_counter;

			FOR(funcI, funcCount) {
				in >> function_name;

				if (txtFuncsF.count(function_name)) {
					frameFunc[i].push_back(txtFuncsF[function_name](in));
        }
        else {
          // Do nothing
        }
			}
		}

		in.close();
	}

	// Changes called value to false if frameFunc has no elements in it
	if (frameFunc.count(0)) {
		called = false;
  }
  else {
    // Do nothing
  }
}

//! A destructor.
  /*!
  This is a destructor method of CompAnim class
  */

CompAnim::~CompAnim() {
  // Iterates through coliders
  assert(colliders != NULL);

	FOR(i, colliders.size()) {

		// Ignores deletion if current collider equals current frame
		if (i == GetCurFrame()) {
			continue;
    }
    else {
      // Do nothing
    }

		delete colliders[i];
	}
}

/*!
	@fn       int CompAnim::get_frame_count()const
	@brief    Returns current frame count as a integer
	@param    none
	@return   int value of frame count
	@warning  none
*/

int CompAnim::get_frame_count()const {
	return sp.get_frame_count();
}

/*!
	@fn       int CompAnim::get_current_frame()const
	@brief    Returns current frame as a integer
	@param    none
	@return   int with the number of the current frame
	@warning  none
*/

int CompAnim::get_current_frame()const {
	return sp.get_current_frame();
}

/*!
	@fn       void CompAnim::set_current_frame(int frame, bool force)
	@brief    Sets the current frame
	@param    int frame, bool force
	@return   void
	@warning  none
*/

void CompAnim::set_current_frame(int frame,		// range: unknown
      													 bool force) {// true to force current frame

	// Set frame as current if it isn't already
	if (frame != get_current_frame()) {
		sp.SetFrame(frame);

		for (auto &foo:frameFunc[frame]) {
			foo(GO(entity));
		}

		called = true;
		force = true;
  }
  else {
    // Do nothing
  }

	// Sets current frame by force
	set_current_frame_by_force(frame, force);
}

/*!
	@fn       void CompAnim::set_current_frame_by_force(int frame, bool force)
	@brief    Sets the current frame by force
	@param    int frame, bool force
	@return   void
	@warning  none
*/

void CompAnim::set_current_frame_by_force(int frame,
                                          bool force) {
  // Sets current frame by force
  if (force == true) {

    // proceeds if frame exists or sets as null
    if (colliders[frame] != nullptr) {
      GO(entity)->SetComponent(Component::type::t_collider, colliders[frame]);
    }
    else if (GO(entity)->HasComponent(Component::type::t_collider)) {
      GO(entity)->components[Component::type::t_collider] = nullptr;
    }
    else {
      // Do nothing
    }
  }
  else {
    // Do nothing
  }
}

/*!
	@fn       bool CompAnim::Looped()const
	@brief    Returns if the animation is looped (true) or not (false)
	@param    none
	@return   bool velue defining if animation is looped or not
	@warning  none
*/

bool CompAnim::Looped()const {
	return sp.Looped();
}

/*!
	@fn       void CompAnim::Update(float time)
	@brief    Updates the animation
	@param    float time
	@return   void
	@warning  none
*/

void CompAnim::Update(float time) {
	int frame1 = get_current_frame(); //!< Used later for comparrison with next frame
  int frame2 = get_current_frame(); //!< Assigns the new frame to this variable for
                                    //!< comparing with the previous one

	// Checks if the animation has not been called and calls it
  checks_animation_call(frame1);

	sp.Update(time);

  set_new_frame(frame1, frame2);
}

/*!
	@fn       void CompAnim::checks_animation_call(int frame)
	@brief    checks if the animation has been called
	@param    int frame
	@return   void
	@warning  none
*/

void CompAnim::checks_animation_call(int frame) {
  assert(frame > 0);

  if (!called) {

    // Iterates through frame
    for (auto &foo : frameFunc[frame]) {
      foo(GO(entity));
    }

    called = true;
  }
  else {
    // Do nothing
  }
}

/*!
	@fn       void CompAnim::compare_frames(int frame1, int frame2)
	@brief    compares the frames
	@param    int frame1, int frame2
	@return   bool
	@warning  none
*/

bool CompAnim::compare_frames(int frame1, int frame2) {
  assert(frame1 < 0 or frame2 < 0);

  if (frame1 != frame2) {
    return true;
  }
  else {
    return false;
  }
}

/*!
	@fn       void CompAnim::set_new_frame(int frame1, int frame2)
	@brief    sets the new frame if it is not already set
	@param    int frame1, int frame2
	@return   void
	@warning  none
*/

void set_new_frame(int frame1, int frame2) {
  assert(frame1 < 0 or frame2 < 0);

  // Checks if current frames is the same as the next one, if they're not the
  // next frame is set
  if (compare_frames(frame1, frame2)) {
    called = false;
    set_current_frame(frame2, true);
  }
  else {
    // Do nothing
  }
}

/*!
	@fn       void CompAnim::Render()
	@brief    Renders current animation
	@param    none
	@return   void
	@warning  none
*/

void CompAnim::Render() {

  Vec2 pos = GO(entity)->FullBox().corner().renderPos(); //!< Used to save the
                                                         //!< position to render

  assert(pos != NULL);

  sp.SetFlipH(GO(entity)->flipped);
	sp.Render(pos, GO(entity)->rotation, Camera::zoom);
}

/*!
	@fn       void CompAnim::own(GameObject* go)
	@brief    Sets ownage of a animation to a game object
	@param    GameObject* go
	@return   void
	@warning  none
*/

void CompAnim::own(GameObject* go) {
  assert(go != NULL);

	entity = go->uid;

	// Iterates through the colliders and defines its ownage if they're not null
	for (CompCollider *coll:colliders) {
		if (coll != nullptr) {
			coll->own(go);
    }
    else {
      // Do nothing
    }
	}

  int frame = get_current_frame();

  set_current_frame(frame, true);
}

/*!
	@fn       Component::type CompAnim::GetType()const
	@brief    Returns type of the animation as a constant value
	@param    none
	@return   Component::type type of the animation
	@warning  none
*/

Component::type CompAnim::GetType()const {
	return Component::type::t_animation;
}
