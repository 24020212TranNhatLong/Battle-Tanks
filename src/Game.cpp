#include "../include/Game.h"


Game :: Game(SDL_Renderer* renderer, Player* player, Monster* MonstersOop, 	Mix_Chunk* buttonMusic, Mix_Chunk* gameOverMusic, Mix_Music* backgroundMusic,
			BulletProcessing* bulletProcessor, CollisionDetection* collisionDetection,
		 	ImageProcessing* imageProcessor, UIManager* UI, MapManager* Map, Item* itemProcessor, Boss* boss) 
		 	
    : running(true), isPlaying(false), isPause(false), isDead(false), isSetting(false), isWin(false), isWaitting(true),
      renderer(renderer), buttonMusic(buttonMusic), gameOverMusic(gameOverMusic), backgroundMusic(backgroundMusic),
      player(player), 
      MonstersOop(MonstersOop),
      bulletProcessor(bulletProcessor),
      collisionDetection(collisionDetection),
      imageProcessor(imageProcessor),
	  UI(UI),
	  Map(Map),
	  itemProcessor(itemProcessor),
	  boss(boss)
    {
}

	
void Game::HandleEvents() {
    SDL_Event event;
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);  //lấy tọa độ của chuột

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
//                    Mix_VolumeChunk(buttonMusic, MIX_MAX_VOLUME / 2);
                    Mix_PlayChannel(-1, buttonMusic, 0);
                    isPlaying = true;
                } else if (isMouseInside(btnExit, mouseX, mouseY)) {
                    std::cout << "Exit button clicked! Exiting game..." << std::endl;
//                    Mix_VolumeChunk(buttonMusic, MIX_MAX_VOLUME / 2);
                    Mix_PlayChannel(-1, buttonMusic, 0);
                    running = false;
                } else if (isMouseInside(btnSetting, mouseX, mouseY)) {
                    std::cout << "Setting button clicked!" << std::endl;
//                    Mix_VolumeChunk(buttonMusic, MIX_MAX_VOLUME / 2);
                    Mix_PlayChannel(-1, buttonMusic, 0);
                    isSetting = true;
                }
            } 
            // Nếu đang chơi
            else {
                if (isMouseInside(btnPause, mouseX, mouseY)) {
//                    Mix_VolumeChunk(buttonMusic, MIX_MAX_VOLUME / 2);
                    Mix_PlayChannel(-1, buttonMusic, 0);
                    isPause = true;
                }
                if (isMouseInside(btnSound, mouseX, mouseY)) {
                    // Bật/tắt âm thanh
                    if (sound) {
                        sound = false;
                        Mix_VolumeChunk(buttonMusic, 0); // Tắt âm thanh buttonMusic
                        Mix_VolumeChunk(gameOverMusic, 0); // Tắt âm thanh gameOverMusic
                        Mix_VolumeMusic(0); // Tắt nhạc nền
                    } else {
                        sound = true;
                        Mix_VolumeChunk(buttonMusic, 50); // Bật âm thanh buttonMusic
                        Mix_VolumeChunk(gameOverMusic, 50); // Bật âm thanh gameOverMusic
                        Mix_VolumeMusic(50); // Bật nhạc nền
                    }
                    UI->RenderSound();  // Cập nhật lại UI sau khi thay đổi trạng thái âm thanh
                }
            }

            // Nếu đang tạm dừng
            if (isPause) {
                if (isMouseInside(btnResume, mouseX, mouseY)) {
//                    Mix_VolumeChunk(buttonMusic, MIX_MAX_VOLUME / 2);
                    Mix_PlayChannel(-1, buttonMusic, 0);
                    isPause = false;
                } else if (isMouseInside(btnQuitPause, mouseX, mouseY)) {
//                    Mix_VolumeChunk(buttonMusic, MIX_MAX_VOLUME / 2);
                    Mix_PlayChannel(-1, buttonMusic, 0);
                    isPause = false;
                    isPlaying = false;
                    player->Reset();
                    MonstersOop->Reset();
                    bulletProcessor->Reset();
                }
            }

            // Nếu đang trong Setting
            if (isSetting && isMouseInside(btnQuitSetting, mouseX, mouseY)) {
//                Mix_VolumeChunk(buttonMusic, MIX_MAX_VOLUME / 2);
                Mix_PlayChannel(-1, buttonMusic, 0);
                isSetting = false;
            }

            // Nếu đã thua
            if (isDead && isMouseInside(btnQuitGameOver, mouseX, mouseY)) {
//                Mix_VolumeChunk(buttonMusic, MIX_MAX_VOLUME / 2);
                Mix_PlayChannel(-1, buttonMusic, 0);
                player->Reset();
                MonstersOop->Reset();
                bulletProcessor->Reset();
                boss->Reset();
                isPlaying = false;
                isDead = false;
            }

            // Nếu đã thắng
            if (isWin && isMouseInside(btnQuitGameOver, mouseX, mouseY)) {
//                Mix_VolumeChunk(buttonMusic, MIX_MAX_VOLUME / 2);
                Mix_PlayChannel(-1, buttonMusic, 0);
                player->Reset();
                MonstersOop->Reset();
                bulletProcessor->Reset();
                boss->Reset();
                isPlaying = false;
                isWin = false;
            }
        }

        // Xử lý các sự kiện trong khi chơi
        if (isPlaying) {
            imageProcessor->HandleInput(event);
            bulletProcessor->ShotByPlayer(event);
        }
    }
}



void Game::UpdateMusic() {
    if (!isPlaying) { 
        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(backgroundMusic, -1);  // Phát nhạc menu khi chưa chơi
        }
    } else Mix_HaltMusic();  // Dừng nhạc menu khi vào game
}



void Game::Update() {
//	std :: cout << "isWaitting: " << isWaitting << " " << "isSetting: " << isSetting << " isPlaying: " << isPlaying << " isPause: " << isPause << " isWin: " << isWin << std :: endl ; 
	if(player->hp <= 0) isDead = true ; //nếu hết  máu
	else if(boss->hp <= 0) isWin = true ;
	

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY) ;

    player->UpdateAngleWeapon(mouseX, mouseY) ; 
    player->UpdateAnglePlayer() ;

    player->UpdatePosition(mouseX, mouseY, MonstersOop, boss, UI) ;
    player->UpdatePower() ;
	player->UpdateMap(bulletProcessor) ;
	MonstersOop->spawnMonster() ;
	MonstersOop->updateAngleTank() ;
	MonstersOop->moveMonster() ;
	MonstersOop->attackPlayer() ;
	
	boss->move() ;
	boss->updateAngle() ;
	
    bulletProcessor->UpdatePositionBulletPlayer() ;
	bulletProcessor->ShotByMonster() ;
	bulletProcessor->UpdatePositionBulletMonster() ;
	
	bulletProcessor->ShotByBoss() ;
	bulletProcessor->UpdatePositionBulletBoss() ;
	
    collisionDetection->BulletPlayerAndMonster() ;
	collisionDetection->BulletPlayerAndWall() ;
	collisionDetection->BulletMonsterAndPlayer() ;
	collisionDetection->BulletMonsterAndWall() ;
	collisionDetection->PlayerAndHp() ;
	collisionDetection->PlayerAndExp() ;
	collisionDetection->PlayerAndBox() ;
	collisionDetection->BulletBossAndPlayer() ;
	collisionDetection->BulletPlayerAndBoss() ;

	itemProcessor->updateAnimation() ;

	
    imageProcessor->UpdateAnimationTank(FRAME_TANK_DELAY, 2) ;
    imageProcessor->UpdateAnimationWeapon(FRAME_WEAPON_DELAY, 8) ;
    imageProcessor->UpdateAnimationBullet(FRAME_WEAPON_DELAY, 4) ;
    imageProcessor->UpdateAnimationMonster(FRAME_TANK_DELAY, FRAME_WEAPON_DELAY, 2, 8) ;

    imageProcessor->UpdateAnimationBodyBoss() ;
    imageProcessor->UpdateAnimationWeaponBoss() ;
    imageProcessor->UpdateAnimationBulletBoss() ;

}

void Game::RenderGame() {
	Map->RenderMap() ;


	itemProcessor->RenderHp() ;
	itemProcessor->RenderExp() ;
	itemProcessor->RenderBox() ;

	
    imageProcessor->RenderTank() ;
    imageProcessor->RenderWeapon() ;
    imageProcessor->RenderBulletPlayer() ;

    

	imageProcessor->RenderMonster() ;
	imageProcessor->RenderBulletMonster() ;

	imageProcessor->RenderBodyBoss() ;
	imageProcessor->RenderWeaponBoss() ;
    imageProcessor->RenderBulletBoss() ;

    UI->RenderHP() ;
    UI->RenderEXP() ;
    UI->RenderScores() ;
    UI->RenderButtonPause() ;
	UI->RenderSound() ;
    UI->RenderNotificationBoss() ;
    UI->RenderNotificationWhenCollectBox() ;

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

        UpdateMusic() ;
        if(isPlaying && !isPause && !isDead && !isWin) {

        	Update() ;
        	SDL_RenderClear(renderer) ;
        	RenderGame() ;
        	SDL_RenderPresent(renderer) ; 

		} else if(isPause && !isDead && !isWin) {
			UI->RenderPauseMenu() ;
			SDL_RenderPresent(renderer);
		} else if(isDead && !isWin) {	
			if(!gameOverMusicPlayed) {
				Mix_PlayChannel(-1, gameOverMusic, 0);

				gameOverMusicPlayed = true ;
			}
			SDL_RenderClear(renderer) ;
			UI->RenderGameOver() ;
			SDL_RenderPresent(renderer);

		} else if(isWin) {
			SDL_RenderClear(renderer) ; 
			UI->RenderWin() ;
			SDL_RenderPresent(renderer) ;

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


        SDL_Delay(10) ; // Giữ tốc độ khung hình ổn định

    }
}



