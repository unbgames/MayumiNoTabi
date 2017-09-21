/*
 *  File: camera.cpp
 *
 *  Description:  Implements Camera class
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

// Method that defines the camera to follow
// Recieves an unsigned int new focus value with range > 0
void Camera::Follow(uint newFocus) {
	following = true;
	focus = newFocus;
}

// Method that defines the camera to unfollow
void Camera::Unfollow() {
	following=false;
}

// Method that returns the camera focus value
uint Camera::GetFocus() {
	return focus;
}

// CONTINUE HERE

// Method that updates the camera
// Recieves a float param
void Camera::Update(float time) {
	Vec2 center = pos + (WINSIZE/2/zoom);
	if (INPUT.IsKeyDown(KEY(z))) {
		zoom += 0.5*time;
		zoom = min(zoom,MAX_ZOOM);
		//cout<<"zoom: "<<zoom<<endl;
	}
	if (INPUT.IsKeyDown(KEY(x))) {
		zoom -= 0.5*time;
		zoom = max(zoom,MIN_ZOOM);
		//cout<<"zoom: "<<zoom<<endl;
	}
	CenterTo(center);

	if (following)CenterTo(GO(focus)->Box().center());
	else if (!lock) {
		speed=Vec2(0,0);
		if (INPUT.IsKeyDown(KEY_LEFT)) speed.x-=CAMERA_SPEED;
		if (INPUT.IsKeyDown(KEY_RIGHT))speed.x+=CAMERA_SPEED;
		if (INPUT.IsKeyDown(KEY_UP))   speed.y-=CAMERA_SPEED;
		if (INPUT.IsKeyDown(KEY_DOWN)) speed.y+=CAMERA_SPEED;
		speed/=zoom;
		speed*=time;
		pos+=speed;
		//if (speed != Vec2(0,0)) cout<<"camera x= "<<pos.x<<"\t y= "<<pos.y<<endl;
	}
}

void Camera::CenterTo(const Vec2& v) {
	Vec2 target = v - (WINSIZE/2/zoom);
	pos.x = max(pos.x,target.x-sz.x);
	pos.x = min(pos.x,target.x+sz.x);
	pos.y = max(pos.y,target.y-sz.y);
	pos.y = min(pos.y,target.y+sz.y);
}

Vec2 Camera::RenderPos(const Vec2& v) {
	return (v-CAMERA)*CAMERAZOOM;
}
float Camera::RenderPosX(const float& x) {
	return (x-CAMERA.x)*CAMERAZOOM;
}
float Camera::RenderPosY(const float& y) {
	return (y-CAMERA.y)*CAMERAZOOM;
}
