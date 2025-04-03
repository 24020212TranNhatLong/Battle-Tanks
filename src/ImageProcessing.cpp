#include "../include/imageProcessing.h"

ImageProcessing :: ImageProcessing(SDL_Renderer* renderer, Player* player, BulletProcessing* bullet, Monster* MonstersOop, Boss* boss) 
	: renderer(renderer), player(player), bullet(bullet), MonstersOop(MonstersOop), boss(boss),
	lastFrameTankTime(0), lastFrameWeaponTime(0), lastFrameBulletTime(0), lastFrameMonsterTankTime(0), lastFrameMonsterWeaponTime(0), lastFrameBossBulletTime(0),
	lastFrameBossBodyTime(0), lastFrameBossWeaponTime(0),
	currentFrameTank(0), currentFrameWeapon(0), currentFrameBullet(0), currentFrameMonsterTank(0), currentFrameBossBody(0), currentFrameBossWeapon(0), currentFrameBossBullet(0),
	typeWeapon(WEAPONRED1), typeTank(REDTANK), typeBullet(BULLET1)
	{
}

//void ImageProcessing :: UpdateTypeWeapon() {
//	if(player->level == 1) typeWeapon = WEAPONRED1 ;
//	if(player->level == 2) typeWeapon = WEAPONRED2 ;
//}

void ImageProcessing::LoadTexture() {
    for (int i = 1; i <= 11; i++) {
        char filePath[50];
		//load frame tank
        if (i <= 2) {
            sprintf(filePath, "assets/RedTank/body/redtank%d.png", i);
            SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
            if (!texture) {
                printf("Failed to load texture: %s, Error: %s\n", filePath, SDL_GetError());
            } else {
                framesTank[REDTANK].push_back(texture);
                printf("Loaded: %s\n", filePath);
            }
        }

		//load frame weapon
        if (i <= 8) {
            sprintf(filePath, "assets/RedTank/weapons1/weaponsRed%d.png", i);
            SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
            if (!texture) {
                printf("Failed to load texture: %s, Error: %s\n", filePath, SDL_GetError());
            } else {
                framesWeapon[WEAPONRED1].push_back(texture);
                printf("Loaded: %s\n", filePath);
            }

            sprintf(filePath, "assets/RedTank/weapons2/weapon2Red%d.png", i);
            texture = IMG_LoadTexture(renderer, filePath);
            if (!texture) {
                printf("Failed to load texture: %s, Error: %s\n", filePath, SDL_GetError());
            } else {
                framesWeapon[WEAPONRED2].push_back(texture);
                printf("Loaded: %s\n", filePath);
            }
    	}
    	
    	//load frame bullet
    	if (i <= 4) {
		    sprintf(filePath, "assets/Bullet/bullet1-%d.png", i);
		    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
		    if (!texture) {
		        printf("Failed to load bullet texture: %s, Error: %s\n", filePath, SDL_GetError());
		    } else {
		        framesBullet[BULLET1].push_back(texture);
		        printf("Loaded: %s\n", filePath);
		    }
		}
		
		//load frame body boss
		if(i <= 2) {
			sprintf(filePath, "assets/Boss/body/body%d.png", i);
		    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
		    if (!texture) {
		        printf("Failed to load bullet texture: %s, Error: %s\n", filePath, SDL_GetError());
		    } else {
		        framesBodyBoss.push_back(texture);
		        printf("Loaded: %s\n", filePath);
		    }
		}
		
		//load frame weapon boss
		if(i <= 11) {
			sprintf(filePath, "assets/Boss/weapon/weapon%d.png", i);
		    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
		    if (!texture) {
		        printf("Failed to load bullet texture: %s, Error: %s\n", filePath, SDL_GetError());
		    } else {
		        framesWeaponBoss.push_back(texture);
		        printf("Loaded: %s\n", filePath);
		    }
		}
		
		//load frame bullet boss
		if (i <= 6) {
		    sprintf(filePath, "assets/Boss/bullet/bullet%d.png", i);
		    SDL_Texture* texture = IMG_LoadTexture(renderer, filePath);
		    if (!texture) {
		        printf("Failed to load bullet texture: %s, Error: %s\n", filePath, SDL_GetError());
		    } else {
		        framesBullet[BULLET3].push_back(texture);
		        printf("Loaded: %s\n", filePath);
		    }
		}
	}
}


void ImageProcessing :: HandleInput(SDL_Event event) {
	if(event.type == SDL_KEYDOWN) { //su kien nhan phim
		switch(event.key.keysym.sym) {
			case SDLK_w : //nhan phim w
			case SDLK_UP :
				if(!player->isMovingDown) player->isMovingUp = true ; //di chuyen len phia truoc
				break ;
			case SDLK_s : //nhan phim s
			case SDLK_DOWN :
				if(!player->isMovingUp) player->isMovingDown = true ; //di chuyen xuong phia sau
				break ;
			case SDLK_a :
			case SDLK_LEFT :
				if(!player->isMovingRight) player->isMovingLeft = true ; //di chuyen sang trai
				break ; 
			case SDLK_d :
			case SDLK_RIGHT :
				if(!player->isMovingLeft) player->isMovingRight = true ; //di chuyen sang phai
				break ;	
		}
	} else {
		if(event.type == SDL_KEYUP) {
			switch(event.key.keysym.sym) {
				case SDLK_w :
				case SDLK_UP :
					player->isMovingUp = false ; 
					break ;
				case SDLK_s :
				case SDLK_DOWN :
					player->isMovingDown = false ;
					break ;
				case SDLK_a :
				case SDLK_LEFT :
					player->isMovingLeft = false ;
					break ;
				case SDLK_d :
				case SDLK_RIGHT :
					player->isMovingRight = false ;
					break ;
			}
		}
	}
	
//	if(event.type == SDL_MOUSEBUTTONDOWN) {
//		if(event.button.button == SDL_BUTTON_LEFT) {
//			player->isAttacking = true ;
//		} 
//	}
}


	

void ImageProcessing :: UpdateAnimationTank(const int Frame_Delay, const int Frame_Count) {
	Uint32 currentFrameTankTime = SDL_GetTicks() ; //đếm thời gian
	if(player->isMovingUp || player->isMovingDown) {  
		if(currentFrameTankTime > lastFrameTankTime + Frame_Delay) {
			currentFrameTank = (currentFrameTank + 1) % Frame_Count ; //cộng thêm 1 vào thứ tự frame hiện tại, chỉ lấy trong phạm vi frame_count
			lastFrameTankTime = currentFrameTankTime ; //update thời gian lần cuối cập nhật
		}
	}
}



void ImageProcessing::RenderTank() {
	//debug
    if (framesTank.find(typeTank) == framesTank.end() || framesTank[typeTank].empty()) {
        printf("Error: No textures found for type %d\n", typeTank);
        return;
    }

	//debug
    if (currentFrameTank >= framesTank[typeTank].size()) {
        printf("Error: currentFrameTank %d out of range (max: %lu)\n", currentFrameTank, framesTank[typeTank].size());
        return;
    }

	//debug
    if (!framesTank[typeTank][currentFrameTank]) {
        printf("Error: Texture at frames[%d][%d] is nullptr\n", typeTank, currentFrameTank);
        return;
    }
    
	SDL_Point center = { sizePlayerX / 2, sizePlayerY / 2 }; //diem xoay
    SDL_Rect destRect = {player->x, player->y, sizePlayerX, sizePlayerY} ; //kich thuoc
	SDL_RenderCopyEx(renderer, framesTank[typeTank][currentFrameTank], NULL, &destRect, player->anglePlayer, &center, SDL_FLIP_NONE);
	
}


//*************** Weapon ***************//

void ImageProcessing :: UpdateAnimationWeapon(const int Frame_Delay, const int Frame_Count) {
	if(player->isAttacking) {
		Uint32 currentFrameWeaponTime = SDL_GetTicks() ;
		
		if(currentFrameWeaponTime > lastFrameWeaponTime + Frame_Delay) {
			currentFrameWeapon = (currentFrameWeapon + 1) % Frame_Count ;
			lastFrameWeaponTime = currentFrameWeaponTime ;
		}
		if(currentFrameWeapon == 0) {
		player->isAttacking = false ;
		}
	} 
}

void ImageProcessing :: RenderWeapon() {
	//debug
	 if (framesWeapon.find(typeWeapon) == framesWeapon.end() || framesWeapon[typeWeapon].empty()) {
        printf("Error: No textures found for type %d\n", typeWeapon);
        return;
    }

	//debug
    if (currentFrameWeapon >= framesWeapon[typeWeapon].size()) {
        printf("Error: currentFrameTank %d out of range (max: %lu)\n", currentFrameWeapon, framesWeapon[typeWeapon].size());
        return;
    }

	//debug
    if (!framesWeapon[typeWeapon][currentFrameWeapon]) {
        printf("Error: Texture at frames[%d][%d] is nullptr\n", typeWeapon, currentFrameWeapon);
        return;
    }
    
	SDL_Rect weaRect = {player->x, player->y , sizeWeaponX, sizeWeaponY} ; //kich thuoc
	SDL_Point center = {sizeWeaponX/2, sizeWeaponY/2} ; //diem xoay
	SDL_RenderCopyEx(renderer, framesWeapon[typeWeapon][currentFrameWeapon], NULL, &weaRect, player->angleWeapon, &center, SDL_FLIP_NONE);
}


//*************** Bullet ***************//

void ImageProcessing :: UpdateAnimationBullet(const int Frame_Delay, const int Frame_Count) {
	Uint32 currentFrameBulletTime = SDL_GetTicks() ;
	
	if(currentFrameBulletTime > lastFrameBulletTime + Frame_Delay) {
		currentFrameBullet = (currentFrameBullet + 1) % Frame_Count ;
		lastFrameBulletTime = currentFrameBulletTime ;
	}
} 


void ImageProcessing :: RenderBulletPlayer() {
	for(size_t i = 0 ; i < bullet->bulletsPlayer.size() ; i++) {
		SDL_Rect bulPlayerRect = {bullet->bulletsPlayer[i].x, bullet->bulletsPlayer[i].y, 8, 8} ; //kich thuoc
		SDL_RenderCopyEx(renderer, framesBullet[typeBullet][currentFrameBullet], NULL, &bulPlayerRect, bullet->bulletsPlayer[i].angle, NULL, SDL_FLIP_NONE);
	}
}

void ImageProcessing :: RenderBulletMonster() {
	//map 1 không có quái
	if(player->currentMap == 1) return ;
	for(size_t i = 0 ; i < bullet->bulletsMonster.size() ; i++) {
		SDL_Rect bulMonsterRect = {bullet->bulletsMonster[i].x, bullet->bulletsMonster[i].y, 8, 8} ; //kich thuoc
		SDL_RenderCopyEx(renderer, framesBullet[typeBullet][currentFrameBullet], NULL, &bulMonsterRect, bullet->bulletsMonster[i].angle, NULL, SDL_FLIP_NONE);
	}
}

// **************** Monster ****************//

void ImageProcessing::UpdateAnimationMonster(
    const int Frame_Tank_Delay, 
    const int Frame_Weapon_Delay, 
    const int Frame_Tank_Count, 
    const int Frame_Weapon_Count
) {
	//map 1 không có quái
	if(player->currentMap == 1) return ;
	
    Uint32 currentTime = SDL_GetTicks();

    // 🔥 Cập nhật animation thân quái vật (nếu đủ thời gian)
    if (currentTime > lastFrameMonsterTankTime + Frame_Tank_Delay) {
        currentFrameMonsterTank = (currentFrameMonsterTank + 1) % Frame_Tank_Count;
        lastFrameMonsterTankTime = currentTime;
    }

    // 🔥 Lấy danh sách quái vật theo map
    std::vector<Monsters>* currentMonsters = nullptr;
    switch (player->currentMap) {
        case 0: currentMonsters = &MonstersOop->m0monsters; break;
        case 2: currentMonsters = &MonstersOop->m2monsters; break;
        case 3: currentMonsters = &MonstersOop->m3monsters; break;
        default: return;
    }

    // 🔥 Cập nhật animation vũ khí của quái vật
    for (auto &monster : *currentMonsters) {
        if (monster.isShotting) {
            if (currentTime > monster.lastFrameWeaponTime + Frame_Weapon_Delay) {
                monster.currentFrameWeapon = (monster.currentFrameWeapon + 1) % Frame_Weapon_Count;
                monster.lastFrameWeaponTime = currentTime;
            }

            // Nếu animation vũ khí đạt frame cuối, reset trạng thái
            if (monster.currentFrameWeapon == Frame_Weapon_Count - 1) {
                monster.isShotting = false;
                monster.currentFrameWeapon = 0;
            }
        }
    }
}



void ImageProcessing::RenderMonster() {
	//map 1 không có quái
	if(player->currentMap == 1) return ;
    // 🔥 Chọn danh sách quái vật đúng theo map
    std::vector<Monsters>* currentMonsters = nullptr;
    switch (player->currentMap) {
        case 0: currentMonsters = &MonstersOop->m0monsters; break;
        case 2: currentMonsters = &MonstersOop->m2monsters; break;
        case 3: currentMonsters = &MonstersOop->m3monsters; break;
        default: return;
    }

    // 🔥 Lặp qua danh sách quái vật hiện tại
    for (auto& monster : *currentMonsters) {
        SDL_Rect monsterTankRect = { monster.x, monster.y, sizePlayerX, sizePlayerY };
        SDL_Rect monsterWeaponRect = { monster.x, monster.y, sizeWeaponX, sizeWeaponY };
        SDL_Point center = { sizeWeaponX / 2, sizeWeaponY / 2 };

        SDL_RenderCopyEx(renderer, framesTank[typeTank][currentFrameMonsterTank], NULL, &monsterTankRect, monster.angleTank, &center, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, framesWeapon[typeWeapon][monster.currentFrameWeapon], NULL, &monsterWeaponRect, monster.angleWeapon, &center, SDL_FLIP_NONE);
    }
}


// **************** Boss ****************//
void ImageProcessing :: UpdateAnimationBodyBoss() {
	if(player->currentMap == 1) {
		Uint32 currentFrameTankTime = SDL_GetTicks() ; //đếm thời gian
		if(currentFrameTankTime > lastFrameTankTime + FRAME_TANK_DELAY) {
			currentFrameBossBody = (currentFrameBossBody + 1) % FRAME_COUNT_BODYBOSS ; //cộng thêm 1 vào thứ tự frame hiện tại, chỉ lấy trong phạm vi frame_count
			lastFrameBossBodyTime = currentFrameTankTime ; //update thời gian lần cuối cập nhật
		}
	}
}

void ImageProcessing::UpdateAnimationWeaponBoss() {
    if (player->currentMap == 1) {
        Uint32 currentTime = SDL_GetTicks(); // Đếm thời gian hiện tại
        
        // Kiểm tra nếu thời gian hiện tại vượt quá thời gian cập nhật gần nhất + khoảng delay
        if (currentTime > lastFrameBossWeaponTime + FRAME_TANK_DELAY) {
            currentFrameBossWeapon = (currentFrameBossWeapon + 1) % FRAME_COUNT_WEAPONBOSS; // Cập nhật frame
            lastFrameBossWeaponTime = currentTime; // Cập nhật thời gian frame cuối
        }
    }
}

void ImageProcessing::UpdateAnimationBulletBoss() {
	if (player->currentMap == 1) {
        Uint32 currentTime = SDL_GetTicks(); // Đếm thời gian hiện tại
        
        // Kiểm tra nếu thời gian hiện tại vượt quá thời gian cập nhật gần nhất + khoảng delay
        if (currentTime > lastFrameBossBulletTime + FRAME_BULLET_DELAY) {
            currentFrameBossBullet= (currentFrameBossBullet + 1) % FRAME_COUNT_BULLETBOSS; // Cập nhật frame
            lastFrameBossBulletTime = currentTime; // Cập nhật thời gian frame cuối
        }
    }
}

void ImageProcessing::RenderBodyBoss() {
	if(player->currentMap == 1) {
		SDL_Point center = { sizeBodyBossX / 2, sizeBodyBossY / 2 }; //diem xoay
	    SDL_Rect destRect = {boss->x, boss->y, sizeBodyBossX, sizeBodyBossY} ; //kich thuoc
		SDL_RenderCopyEx(renderer, framesBodyBoss[currentFrameBossBody], NULL, &destRect, boss->angleBody, &center, SDL_FLIP_NONE);
	}
}

void ImageProcessing::RenderWeaponBoss() {
	if(player->currentMap == 1) {
		SDL_Point center = { sizeBodyBossX / 2, sizeBodyBossY / 2 }; //diem xoay
	    SDL_Rect destRect = {boss->x, boss->y, sizeBodyBossX, sizeBodyBossY} ; //kich thuoc
		SDL_RenderCopyEx(renderer, framesWeaponBoss[currentFrameBossWeapon], NULL, &destRect, boss->angleWeapon, &center, SDL_FLIP_NONE);
	}
}

void ImageProcessing :: RenderBulletBoss() {
	if(player->currentMap == 1) {
		for(size_t i = 0 ; i < bullet->bulletsBoss.size() ; i++) {
			SDL_Rect bulBossRect = {bullet->bulletsBoss[i].x, bullet->bulletsBoss[i].y, sizeBulletBossX, sizeBulletBossY} ; //kich thuoc
			SDL_RenderCopyEx(renderer, framesBullet[BULLET3][currentFrameBossBullet], NULL, &bulBossRect, bullet->bulletsBoss[i].angle, NULL, SDL_FLIP_NONE);
		}
	}
}
