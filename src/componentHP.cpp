/*
*  File: componentHP.cpp
*
*  Description:  Implements componentHP class
*/

#include <componentHP.hpp>
#include <componentMemory.hpp>
#include <componentAI.hpp>
#include <gameObject.hpp>
#include <game.hpp>
#include <camera.hpp>

CompHP::CompHP(int tot,bool showHP,bool showDMG,float dmgCD)
   :total{tot},current{tot},showHP{showHP},showDMG{showDMG},cooldown{dmgCD}{}

CompHP::CompHP(int tot,int cur,bool showHP,bool showDMG,float dmgCD)
   :total{tot},current{cur},showHP{showHP},showDMG{showDMG},cooldown{dmgCD}{}

// No params constructor method
CompHP::~CompHP() {
}

// Updates the player HP value based on the damage inflicted, has current damage inflicted as param
void CompHP::Damage(int dmg) {
	// Verifies if current damage value bigger than the current value
	if(dmgCoolDown.Get()>cooldown){
		dmgCoolDown.Restart();
		current-=dmg;
		//TODO: Renderizes damage value
		if(showDMG){
		}
		// Checks if element has 'memory' type and increases 'hit' value
		if(GO(entity)->HasComponent(Component::type::t_memory))COMPMEMORYp(GO(entity))->ints["hit"]++;
	}
}

// Updates HP value according to time param
void CompHP::Update(float time) {
	// Verifies if element is in the 'dead' state
	// TODO: Refactorate decision structures
	if(current<=0)GO(entity)->dead=true;
	dmgCoolDown.Update(time);
}

// Renders on screen the HP value
void CompHP::Render() {
	// Shows HP on screen if it's set player and bigget than zero
	// TODO: Refactorate decision structures
	if(SETTINGS.showHP && showHP && current>0){
		Rect box{0,-GO(entity)->Box().w/5.0f - GO(entity)->Box().w/10.0f,GO(entity)->Box().w,GO(entity)->Box().w/5.0f};
		box+=GO(entity)->Box().corner();

		box = box.renderBox();

		SDL_SetRenderDrawColor(GAMERENDER, 0, 0, 0, 255);
		SDL_Rect rect=box.sdlRect();
		SDL_RenderDrawRect(GAMERENDER,&rect);

		SDL_SetRenderDrawColor(GAMERENDER, 255, 0, 0, 255);
		rect.w*=current;
		rect.w/=total;
		rect.x++;
		rect.y++;
		rect.w-=2;
		rect.h-=2;
		SDL_RenderFillRect(GAMERENDER,&rect);
	}
}

// Returns if the component is if the 'HP' type
Component::type CompHP::GetType()const{
	return Component::type::t_hp;
}
