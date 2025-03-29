#include "../include/Game.h"

Game :: Game(SDL_Renderer* renderer, Player* player, Monster* MonstersOop, 	Mix_Music* buttonMusic, Mix_Music* gameOverMusic,
			BulletProcessing* bulletProcessor, CollisionDetection* collisionDetection,
		 	ImageProcessing* imageProcessor, UIManager* UI, MapManager* Map) 
		 	
    : running(true), isPlaying(false), isPause(false), isDead(false), isSetting(false),
      renderer(renderer), buttonMusic(buttonMusic), gameOverMusic(gameOverMusic),
      player(player), 
      MonstersOop(MonstersOop),
      bulletProcessor(bulletProcessor),
      collisionDetection(collisionDetection),
      imageProcessor(imageProcessor),
	  UI(UI),
	  Map(Map) 
    {
}

	
void Game::HandleEvents() {
    SDL_Event event;
    int mouseX, mouseY;  
    SDL_GetMouseState(&mouseX, &mouseY);  //lấy tọa độ của chuột

//	std :: cout << mouseX << " " << mouseY << std :: endl ;
	
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        
        // Kiểm tra sự kiện nhấn chuột
		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		    // Nếu chưa chơi
		    if (!isPlaying) {
		        if (isMouseInside(btnPlay, mouseX, mouseY)) {
		            std::cout << "Play button clicked! Starting game..." << std::endl;
		            Mix_PlayMusic(buttonMusic, 0);
		            isPlaying = true;
		        } else if (isMouseInside(btnExit, mouseX, mouseY)) {
		            std::cout << "Exit button clicked! Exiting game..." << std::endl;
		            Mix_PlayMusic(buttonMusic, 0);Mix_PlayMusic(buttonMusic, 0);
		            running = false;
		        } else if (isMouseInside(btnSetting, mouseX, mouseY)) {
		            std::cout << "Setting button clicked!" << std::endl;
		            Mix_PlayMusic(buttonMusic, 0);
		            isSetting = true;
		        }
		    } 
		    // Nếu đang chơi
		    else {
		        if (isMouseInside(btnPause, mouseX, mouseY)) {
		        	Mix_PlayMusic(buttonMusic, 0);
		            isPause = true;
		        }
		    }
		
		    // Nếu đang tạm dừng
		    if (isPause) {
		        if (isMouseInside(btnResume, mouseX, mouseY)) {
		        	Mix_PlayMusic(buttonMusic, 0);
		            isPause = false;
		        } else if (isMouseInside(btnQuitPause, mouseX, mouseY)) {
		        	Mix_PlayMusic(buttonMusic, 0);
		            isPause = false;
		            isPlaying = false;
		            player->Reset();
		            MonstersOop->Reset();
		            bulletProcessor->Reset();
		        }
		    }
		
		    // Nếu đang trong Setting
		    if (isSetting && isMouseInside(btnQuitSetting, mouseX, mouseY)) {
		    	Mix_PlayMusic(buttonMusic, 0);
		        isSetting = false;
		    }
		
		    // Nếu đã thua
		    if (isDead && isMouseInside(btnQuitGameOver, mouseX, mouseY)) {
		    	Mix_PlayMusic(buttonMusic, 0);
		        player->Reset();
		        MonstersOop->Reset();
		        bulletProcessor->Reset();
		        isPlaying = false;
		        isDead = false;
		    }
		}
		
		if(isPlaying) {
			imageProcessor->HandleInput(event) ;
			bulletProcessor->ShotByPlayer(event) ;
		}
	}
}


void Game::Update() {
	if(player->hp <= 0) isDead = true ; //nếu hết  máu
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY) ;

    player->UpdateAngleWeapon(mouseX, mouseY) ; 
    player->UpdateAnglePlayer() ;
    player->UpdatePosition(mouseX, mouseY, MonstersOop) ;
    player->UpdatePower() ;

    MonstersOop->spawnMonster() ;
    MonstersOop->updateAngleTank() ;
    MonstersOop->moveMonster() ;
    MonstersOop->attackPlayer() ;

    bulletProcessor->ShotByMonster() ;
    bulletProcessor->UpdatePositionBulletPlayer() ;
    bulletProcessor->UpdatePositionBulletMonster() ;

    collisionDetection->BulletPlayerAndMonster() ;
    collisionDetection->BulletMonsterAndPlayer() ;
	collisionDetection->BulletMonsterAndWall() ;
	collisionDetection->BulletPlayerAndWall() ;
	
    imageProcessor->UpdateAnimationTank(FRAME_TANK_DELAY, 2) ;
    imageProcessor->UpdateAnimationWeapon(FRAME_WEAPON_DELAY, 8) ;
    imageProcessor->UpdateAnimationBullet(FRAME_WEAPON_DELAY, 4) ;
    imageProcessor->UpdateAnimationMonster(FRAME_TANK_DELAY, FRAME_WEAPON_DELAY, 2, 8) ;
}

void Game::RenderGame() {
	Map->RenderMap() ;
	
    imageProcessor->RenderTank() ;
    imageProcessor->RenderWeapon() ;
    imageProcessor->RenderBulletPlayer() ;
    imageProcessor->RenderMonster() ;
    imageProcessor->RenderBulletMonster() ;
    UI->RenderHP() ;
    UI->RenderEXP() ;
    UI->RenderScores() ;
    UI->RenderButtonPause() ;
}

void Game :: RenderBackGround() {
	UI->RenderBGR() ;	
}

void Game :: RenderMenu() {
	UI->RenderTable() ;
}

void Game::Run() {
	bool gameOverMusicPlayed = false;
    while (running) {
        HandleEvents() ;
        if(isPlaying && !isPause && !isDead) {
        	Update() ;
        	SDL_RenderClear(renderer) ;
        	RenderGame() ;
        	SDL_RenderPresent(renderer) ; 
		} else if(isPause && !isDead) {
			UI->RenderPauseMenu() ;
			SDL_RenderPresent(renderer);
		} else if(isDead) {	
			if(!gameOverMusicPlayed) {
				Mix_PlayMusic(gameOverMusic, 0);
				gameOverMusicPlayed = true ;
			}
			SDL_RenderClear(renderer) ;
			UI->RenderGameOver() ;
			SDL_RenderPresent(renderer);
		} else if(!isSetting) {
			SDL_RenderClear(renderer) ;
			RenderBackGround() ;
			RenderMenu() ;
			SDL_RenderPresent(renderer) ; 
		}  else {
			SDL_RenderClear(renderer) ;
			UI->RenderSetting() ;
			SDL_RenderPresent(renderer) ; 
		}

        SDL_Delay(16) ; // Giữ tốc độ khung hình ổn định
    }
}



