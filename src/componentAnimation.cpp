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

  // TODO: separate variable declarations and comment them all
  string name, img_file, function_name, /* animFile, unused */ type;

  int f_count, f_counter_x, f_counter_y, collider_counter, function_counter;

  float f_time, x_axis, y_axis, width, height, r;

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

          colliders[i]->colls.emplace_back(entity, temporary_collider->colls[0].cType,
                                            Rect{x_axis, y_axis, width, height});

          colliders[i]->colls[j].useDefault = temporary_collider->colls[0].useDefault;

          colliders[i]->colls[j].active = temporary_collider->colls[0].active;
        }
      }

      in >> function_counter;

      FOR(funcI, funcCount) {
        in >> function_name;

        if (txtFuncsF.count(function_name)) {
          frameFunc[i].push_back(txtFuncsF[function_name](in));
        }
      }
    }

    in.close();
  }

  // Changes called value to false if frameFunc has no elements in it
  if (frameFunc.count(0)) {
    called = false
  };
}

//! A destructor.
  /*!
  This is a destructor method of CompAnim class
  */

CompAnim::~CompAnim() {
  // Iterates through coliders
  FOR(i, colliders.size()) {

    // Ignores deletion if current collider equals current frame
    if (i == get_current_frame()) {
      continue;
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
  @fn       void CompAnim::set_current_frame(int frame_number, bool force)
  @brief    Sets the current frame
  @param    int frame_number, bool force
  @return   void
  @warning  TOD: some of the decision structure must be rewritten
*/

void CompAnim::set_current_frame(int frame_number,		// range: unknown
                                 bool force) {// true to force current frame

  // Set frame as current if it isn't already
  if (frame_number != get_current_frame()) {
    sp.set_frame(frame);

    for (auto &foo:frameFunc[frame]) {
      foo(GO(entity));
    }

    called = true;
    force = true;
  }

  // TODO: else (do nothing)
  // Sets current frame by force
  if (force) {

    // proceeds if frame exists or sets as null
    if (colliders[frame] != nullptr) {
      GO(entity)->SetComponent(Component::type::t_collider,colliders[frame]);
    }
    else if (GO(entity)->HasComponent(Component::type::t_collider)) {
      GO(entity)->components[Component::type::t_collider] = nullptr;
    }
  }
}

/*!
  @fn       bool CompAnim::is_looped()const
  @brief    Returns if the animation is looped (true) or not (false)
  @param    none
  @return   bool velue defining if animation is looped or not
  @warning  none
*/

bool CompAnim::is_looped()const {
  return sp.is_looped();
}

/*!
  @fn       void CompAnim::update(float time)
  @brief    Updates the animation
  @param    float time
  @return   void
  @warning  none
*/

void CompAnim::update(float time) {
  int current_frame = get_current_frame(); //!< Used later for comparrison

  // Checks if the animation has not been called and calls it
  if (!called) {

    // Iterates through frame
    for (auto &foo:frameFunc[current_frame]) {
      foo(GO(entity));
    }

    called = true;
  }

  sp.update(time);

  int new_frame = get_current_frame(); //!< Assigns the new frame to this
                              //!< variable for comparing with the previous one

  // Checks if current frames is the same as the next one, if they're not the
  // next frame is set
  if (current_frame != new_frame) {
    called = false;
    set_current_frame(new_frame, true);
  }
}

/*!
  @fn       void CompAnim::render()
  @brief    Renders current animation
  @param    none
  @return   void
  @warning  none
*/

void CompAnim::render() {

  Vec2 pos = GO(entity)->FullBox().corner().renderPos(); //!< Used to save the
                                                         //!< position to render

  sp.SetFlipH(GO(entity)->flipped);
  sp.render(pos, GO(entity)->rotation, Camera::zoom);
}

/*!
  @fn       void CompAnim::own(GameObject* game_object)
  @brief    Sets ownage of a animation to a game object
  @param    GameObject* game_object
  @return   void
  @warning  none
*/

void CompAnim::own(GameObject* game_object) {
  entity = game_object->uid;

  // Iterates through the colliders and defines its ownage if they're not null
  for (CompCollider *coll:colliders) {
    if (coll != nullptr) {
      coll->own(game_object);
    }
  }

  int frame = get_current_frame();

  set_current_frame(frame, true);
}

/*!
  @fn       Component::type CompAnim::get_type()const
  @brief    Returns type of the animation as a constant value
  @param    none
  @return   Component::type type of the animation
  @warning  none
*/

Component::type CompAnim::get_type()const {
  return Component::type::t_animation;
}
