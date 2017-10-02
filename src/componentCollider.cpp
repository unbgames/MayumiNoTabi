/*
*  File: componentCollider.cpp
*
*  Description:  Implements CompCollider class
*/

#include <componentCollider.hpp>
#include <componentMovement.hpp>
#include <gameObject.hpp>
#include <game.hpp>

/*!
  *  @fn CompCollider::CompCollider()
  *  @brief No params constructor method
*/

CompCollider::CompCollider() {
}

/*!
  * @fn CompCollider::CompCollider(collType type,const Rect &rectangle)
  * @brief Constructor Method for component collider
  * @param Generic component type and positioning values
*/

CompCollider::CompCollider(collType type,const Rect &rectangle) {
	colls.emplace_back(entity,type,rectangle);
}

/*!
  * @fn CompCollider::CompCollider(collType type,const Vec2 &p,const Vec2 &sz)
  * @brief Constructor Method for component collider
  * @param Generic component, positioning values for 3D elements
*/

CompCollider::CompCollider(collType type,const Vec2 &position,const Vec2 &sz) {
	colls.emplace_back(entity,type,position,sz);
}

/*!
  * @fn CompCollider::CollisionCheck(CompCollider *otherComponent)
  * @brief Checks if components has suffered an collision
  * @param An collidable component
*/

void CompCollider::CollisionCheck(CompCollider *otherComponent) {
	//! TODO: simplify decision structure
	//! Verifies if the the element is in the 'dead' state
	if(GO(entity)->dead || GO(otherComponent->entity)->dead)return;

	//! If the element is 'dead' it checks checks if the collision are enabled
	//! TODO: simplify repetition structure
	for(Coll &collA:colls)for(Coll &collB:otherComponent->colls)collA.CollisionCheck(collB);
}

/*!
  * @fn void CompCollider::Update(float currentTime)
	* @brief Verifies if an collision has happened
  * @param float time
*/

void CompCollider::Update(float currentTime) {

	UNUSED(currentTime);
	//! Iterates throughout the collisons to update its range of verification
	for(Coll &coll:colls) {
		if(coll.active) {
			int lowerRange = coll.Box().x-10; //!< Creates variable that sets the lower range of the game box
			int upperRange = coll.Box().x2()+10; //!< Creates variable that sets the upper range of the game box
			set<uint> ent = GAMESTATE.GetEntitiesInRange(lowerRange,upperRange);
			//! Iterates throughout the screen elements to check if there has been collisions
			FOR(uint go:ent) {
			//! Checks if the object in analysis is an collidable component
				if(go != entity && GO(go)->HasComponent(Component::type::t_collider)) {
					CollisionCheck(COMPCOLLIDERp(GO(go)));
				}
			}
		}
	}
}

/*!
* @fn CompCollider::Render()
* @brief Render graphics in order to display collisions
* @param No params
*/

void CompCollider::Render() {
	if(SETTINGS.showCollision)
		//! Iterates throughout the Collision objects in order to update the rendering
		for(Coll coll:colls){
			//! TODO: Refactorate decision structures
			if     (coll.cType==CompCollider::collType::t_player) SET_COLOR4(255,0,0,100);
			else if (coll.cType==CompCollider::collType::t_monster)SET_COLOR4(0,255,0,100);
			else if (coll.cType==CompCollider::collType::t_bullet) SET_COLOR4(0,0,255,100);
			else if (coll.cType==CompCollider::collType::t_ground) SET_COLOR4(255,255,0,100);
			else SET_COLOR4(255,255,255,100);
			SDL_Rect rectangle = (coll.Box().renderBox().sdlRect()); //!< Creates an rectangle entity to be fulfilled
			FILL_RECT(&rectangle);
		}
};

/*!
  * @fn CompCollider::Own()
	* @brief Verifies if an Object has an collision associated to it
	* @param GameObject *object
*/

void CompCollider::Own(GameObject *object) {
	entity = object->uid; //! uid is equivalent to UserID
  //! Verifies if the element is empty or not
	if(object != nullptr) {
		//! Verifies the size of the collisions
		if(colls.size()) {
			Rect rectangle{};
			//! Verifies if the element size is equal to the collisions size
			for(Coll coll:colls)rectangle = rectangle.sum(Rect{coll.position,coll.size});
			object->curPos = rectangle.corner(); //!< Updates the value of the current position of the object
			object->curSize = rectangle.size(); //!< Updates the value of the current size of the object
		}
		else { //! If collision has no size it gives 'zero' values to it
			object->curPos = Vec2{}; //!< Updates the value of the current position of the object
			object->curSize = Vec2{0.0f,0.0f}; //!< Updates the value of the current size of the object
		}
	}
}

/*!
  * @fn CompCollider::Die()
	* @brief Checks if the component has died in the game, has time of death as a param
	* @param float time
*/

bool CompCollider::Die(float time) {
	UNUSED(time);
  //! Checks if the component has a type associated to it
	if(GO(entity)->HasComponent(Component::type::t_animation))return true;
	if(GO(entity)->HasComponent(Component::type::t_animation_control))return true;
	return false;
}

/*!
  * @fn Component::type CompCollider::GetType()
	* @brief Returns the component assigned type
  * @param No params
*/

Component::type CompCollider::GetType() const {
	return Component::type::t_collider;
}

/*!
	* @fn CompCollider::Coll::Coll(const uint &e,collType type,const Rect &r)
	* @brief TODO : Comment this structure
	* @param const uint &e,collType type,const Rect &r
*/

CompCollider::Coll::Coll(const uint &e,collType type,const Rect &rectangle): //! uint is equivalent to unsigned int
	entity{e},pos{rectangle.corner()},size{rectangle.size()},cType{t} {
	}

/*!
  * @fn CompCollider::Coll::Coll(const uint &e,collType type,const Vec2 &p,const Vec2 &sz)
	* @brief TODO : Comment this structure
  * @param const uint &e,collType type,const Vec2 &p,const Vec2 &sz
*/

CompCollider::Coll::Coll(const uint &e,collType type,const Vec2 &position,const Vec2 &sz):
	entity{e},pos{position},size{sz},cType{type} {
	}

/*!
  * @fn CompCollider::Coll::Box()
	* @brief TODO : Comment this structure
  * @param No param
*/

Rect CompCollider::Coll::Box() const {
	Rect rectangle = GO(entity)->Box(pos,size);
	return rectangle;
}

/*!
	* @fn CompCollider::Coll::CollisionCheck(const CompCollider::Coll &other)
	* @brief Checks if components has suffered an collision, generic type of element as a param
	* @param CompCollider::Coll &otherComponent
*/

void CompCollider::Coll::CollisionCheck(const CompCollider::Coll &otherComponent) {
	//! Verifies the collision type and if is whether
	//! TODO: Refactorate decision structures
	if(useDefault.count(other.cType))useDefault[other.cType](*this,otherComponent);
	else if(useDefault.count(collType::t_any))useDefault[collType::t_any](*this,otherComponent);
	else if(GO(entity)->HasComponent(Component::type::t_movement)) {

		CompMovement *compMove = COMPMOVEp(GO(entity));

		Vec2 &speed=compMove->speed;
		Vec2 &totMove=compMove->move;
		Vec2 move;

		//! TODO : Comment this structure
		if(totMove == Vec2{}) return;

		move.x = Collides(otherComponent,{totMove.x,0.0f},move).x;

		//! Verifies if object in x axis has collided
		if(move.x != totMove.x) {
			speed.x=0.0f;
		}

		move.y = Collides(otherComponent,{0.0f,totMove.y},move).y;

		//! Verifies if object in y axis has collided
		if(move.y != totMove.y) {
			speed.y=0.0f;
		}
		totMove=move;
	}
}

/*!
	* @fn CompCollider::Coll::Collides(const Coll &otherComponent,const Vec2 &move,const Vec2 &moved)
	* @brief Defines an collision field range, has generic elements and 'rangeable' screen spaces params
	* @param Coll &other,const Vec2 &move,const Vec2 &moved
*/

Vec2 CompCollider::Coll::Collides(const Coll &otherComponent,const Vec2 &move,const Vec2 &moved) const {
	const int precision = 100;
	Rect rectangle = Box()+moved; //!< Updates the current value of the rectangle
	Rect anotherRectangle = otherComponent.Box(); //!< Updates the value of another rectangle
	Vec2 moveSafe,move100=move/precision,moveTry;

	//! Iterates throughout the 'rangeable' variables to identify collision
	for(counter,precision+1) {
		moveTry = move100*counter;
		//! Checks if a collision has happened
		//! TODO: Refactorate decision structure
		if((rectangle+moveTry).collides(box2))return moveSafe;
		moveSafe = moveTry;
	}
	return move;
}
