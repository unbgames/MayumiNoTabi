/*!
 *  \file File camera.cpp
 *  \brief Implementation of Camera class
 *
 *  The class implemented here defines the game's camera logic
 *
 *  \sa camera.hpp
 */

#include <camera.hpp>

#include <common.hpp>

#include <game.hpp>
#include <gameObject.hpp>
#include <inputManager.hpp>

// Macros declaration
#define CAMERA_SPEED 500	// unit:
#define MAX_ZOOM 1.0f		 	// unit:
#define MIN_ZOOM 0.2f			// unit:

// uint is actually the short for unsigned int
uint Camera::focus = 0;

Vec2 Camera::pos;
Vec2 Camera::speed;
Vec2 Camera::sz{100,50};

float Camera::zoom = 1.0f;

bool Camera::lock = false;
bool Camera::following = false;


/*!
  @fn       void Camera::Follow(uint newFocus)
  @brief    Method that defines the camera's focus to follow
  @param    uint newFocus
  @return   void
  @warning  none
*/

void Camera::Follow(uint newFocus) { // Range: bigger than 0
  following = true;
  focus = newFocus;
}

/*!
  @fn       void Camera::Unfollow()
  @brief    Method that defines the camera's focus not to follow
  @param    none
  @return   void
  @warning  none
*/

void Camera::Unfollow() {
  following = false;
}

/*!
  @fn       uint CompTimer::GetFocus()
  @brief    Method that returns the camera's focus value
  @param    none
  @return   unsigned int focus value
  @warning  none
*/

uint Camera::GetFocus() {
  return focus;
}


/*!
  @fn       void Camera::Update(float time)
  @brief    Updates the camera
  @param    float time
  @return   void
  @warning  TODO in decision structure
*/

void Camera::Update(float time) {
  Vec2 center = pos + (WINSIZE/2/zoom);

  // Zooms in if z key is pressed
  if (INPUT.IsKeyDown(KEY(z))) {
    zoom += 0.5 * time;
    zoom = min(zoom,MAX_ZOOM);

    //cout<<"zoom: "<<zoom<<endl;
  }

  // Zooms out if x key is pressed
  if (INPUT.IsKeyDown(KEY(x))) {
    zoom -= 0.5 * time;
    zoom = max(zoom,MIN_ZOOM);

    //cout<<"zoom: "<<zoom<<endl;
  }

  // Centers screen
  CenterTo(center);

  // TODO: add else(do nothing)
  // Defines camera position in either follow or static or do nothing
  if (following) {
    CenterTo(GO(focus)->Box().center());
  }
  else if (!lock) {
    speed = Vec2(0,0);

    // defines camera speed according to the arrow key that has been pressed.
    // (left)
    if (INPUT.IsKeyDown(KEY_LEFT)) {
      speed.x -= CAMERA_SPEED;
    }

    // defines camera speed according to the arrow key that has been pressed.
    // (right)
    if (INPUT.IsKeyDown(KEY_RIGHT)){
      speed.x += CAMERA_SPEED;
    }

    // defines camera speed according to the arrow key that has been pressed.
    // (up)
    if (INPUT.IsKeyDown(KEY_UP)) {
      speed.y -= CAMERA_SPEED;
    }

    // defines camera speed according to the arrow key that has been pressed.
    // (down)
    if (INPUT.IsKeyDown(KEY_DOWN)) {
      speed.y += CAMERA_SPEED;
    }

    // TODO: math refactoring
    speed /= zoom;
    speed *= time;
    pos += speed;

    // if (speed != Vec2(0,0)) {
    // 	cout << "camera x= " << pos.x << "\t y= " << pos.y << endl;
    // }
  }
}

/*!
  @fn       void Camera::CenterTo(const Vec2& v)
  @brief    Centers camera to a pre-stablished position
  @param    const Vec2& v
  @return   void
  @warning  TODO: some math must be simplified
*/

void Camera::CenterTo(const Vec2& v) {
  Vec2 target = v - (WINSIZE/2/zoom); // TODO: break down math

  pos.x = max(pos.x, target.x - sz.x);
  pos.x = min(pos.x, target.x + sz.x);

  pos.y = max(pos.y, target.y - sz.y);
  pos.y = min(pos.y, target.y + sz.y);
}

/*!
  @fn       Vec2 Camera::RenderPos(const Vec2& v)
  @brief    Renders camera's position
  @param    const Vec2& v
  @return   Rendered camera position
  @warning  TODO: fix return to no longer be an math expression
*/

Vec2 Camera::RenderPos(const Vec2& v) {
  return (v - CAMERA) * CAMERAZOOM;
}

/*!
  @fn       float Camera::RenderPosX(const float& x)
  @brief    Method that renders x axis position
  @param    const float& x
  @return   Rendered position on x axis for camera
  @warning  TODO: fix return to no longer be an math expression
*/

float Camera::RenderPosX(const float& x) {
  return (x - CAMERA.x) * CAMERAZOOM;
}

/*!
  @fn       float Camera::RenderPosY(const float& y)
  @brief    Method that renders y axis position
  @param    const float& y
  @return   Rendered position on y axis for camera
  @warning  TODO: fix return to no longer be an math expression
*/

float Camera::RenderPosY(const float& y) {
  return (y - CAMERA.y) * CAMERAZOOM;
}
