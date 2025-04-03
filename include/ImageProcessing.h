#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>
#include <unordered_map>
#include <vector>
#include "BulletProcessing.h"
#include "Player.h"
#include <iostream>
#include "Constants.h"
#include "Monster.h"
#include "Boss.h"

enum typeTanks {
	REDTANK
};

enum typeWeapons {
	WEAPONRED1,
	WEAPONRED2
};

enum typeBullets {
	BULLET1,
	BULLET2,
	BULLET3
};

class ImageProcessing {
public :
	//construct
	ImageProcessing(SDL_Renderer* renderer, Player* player, BulletProcessing* bullet, Monster* Monsters, Boss* boss) ;
	
	//load texture 
	void LoadTexture();
	
	//handle input
	void HandleInput(SDL_Event event) ;
	
	//update animation
	void UpdateAnimationTank(const int Frame_Delay, const int Frame_Count) ;
	void UpdateAnimationWeapon(const int Frame_Delay, const int Frame_Count) ;
	void UpdateAnimationBullet(const int Frame_Delay, const int Frame_Count) ;
	void UpdateAnimationMonster(const int Frame_Tank_Delay, const int Frame_Weapon_Delay, const int Frame_Tank_Count, const int Frame_Weapon_Count) ;
	void UpdateAnimationBodyBoss() ;
	void UpdateAnimationWeaponBoss() ;
	void UpdateAnimationBulletBoss() ;
	
	//render
	void RenderTank() ;
	void RenderWeapon() ;
	void RenderBulletPlayer() ;
	void RenderBulletMonster() ;
	void RenderMonster() ;
	void RenderBodyBoss() ;
	void RenderWeaponBoss() ;
	void RenderBulletBoss() ;
		//update type
	void UpdateTypeWeapon() ;
	void UpdateTypeTank() ;
	
	Uint32 lastFrameTankTime, lastFrameWeaponTime, lastFrameBulletTime, lastFrameMonsterTankTime, lastFrameMonsterWeaponTime,
	 	lastFrameBossBulletTime,lastFrameBossBodyTime, lastFrameBossWeaponTime ;
	typeTanks typeTank ;
	typeWeapons typeWeapon ;
	typeBullets typeBullet ;
	
	int currentFrameTank, currentFrameWeapon, currentFrameBullet, currentFrameMonsterTank,
	 currentFrameBossBody, currentFrameBossWeapon, currentFrameBossBullet ;
private :
	SDL_Renderer* renderer;
	std :: unordered_map<typeTanks, std :: vector<SDL_Texture*>> framesTank; //chứa frame của Tank
	std :: unordered_map<typeWeapons, std :: vector<SDL_Texture*>> framesWeapon; //chứa frame của weapon
	std :: unordered_map<typeBullets, std :: vector<SDL_Texture*>> framesBullet; //chứa frame của bullet
	std :: vector<SDL_Texture*> framesBodyBoss ; //frame body boss
	std :: vector<SDL_Texture*> framesWeaponBoss ; //frame weapon boss
	Player* player;
	Monster* MonstersOop ;
	BulletProcessing* bullet ;
	Boss* boss ;
};


#endif