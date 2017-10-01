#include <componentMovement.hpp>
#include <gameObject.hpp>
#include <game.hpp>

CompMovement::CompMovement(const Vec2& s,moveType t):mType{t},speed{s}{}
CompMovement::~CompMovement() {}

/*!
  * @fn void CompMovement::Update(float time)
  * @brief Checks if has occurred a movement update
  * @param float time
*/

void CompMovement::Update(float time) {
	UNUSED(time);
	GO(entity)->pos+=move;
	if (mType==moveType::t_bullet)GO(entity)->rotation=speed.angle();
}

/*!
* @fn void CompMovement::Render()
* @brief Renderizes on screen the component movement
* @param No params
*/

void CompMovement::Render() {

}

/*!
* @fn Component::type CompMovement::GetType()const
* @briefs Obtain the type of movement of the component
* @return Component::type::t_movement
* @param No params
*/

Component::type CompMovement::GetType()const{
	return Component::type::t_movement;
}
