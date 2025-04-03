#include "../include/UIManager.h"


UIManager :: UIManager(SDL_Renderer* renderer, Player* player, Monster* MonstersOop, TTF_Font* font, Boss* boss) 
	: renderer(renderer), player(player), MonstersOop(MonstersOop), font(font), notiBoss(false), boss(boss),
	message(""), notiBox(false), startTimeBoss(0)

	{
}

void UIManager :: loadTexture() {
	background = IMG_LoadTexture(renderer, "assets/BGR/background.png") ;
	if(!background) std :: cout << "Fail to load texture: assets/BGR/background\n" << SDL_GetError() << std :: endl;
		else std :: cout << "Loaded: assets/BGR/background" << std :: endl;
		
		
	table = IMG_LoadTexture(renderer, "assets/Table/table.png") ;	
	if(!table) std :: cout << "Fail to load texture: assets/Table/table.png\n" << SDL_GetError() << std :: endl;
		else std :: cout << "Loaded: assets/Table/table.png" << std :: endl;
		
	menuPause = IMG_LoadTexture(renderer, "assets/Table/menuPause.png") ;	
	if(!menuPause) std :: cout << "Fail to load texture: assets/Table/menuPause.png\n" << SDL_GetError() << std :: endl;
		else std :: cout << "Loaded: assets/Table/menuPause.png" << std :: endl;
			
	buttonPause = IMG_LoadTexture(renderer, "assets/Table/buttonPause.png") ;	
	if(!menuPause) std :: cout << "Fail to load texture: assets/Table/buttonPause.png\n" << SDL_GetError() << std :: endl;
		else std :: cout << "Loaded: assets/Table/buttonPausePause.png" << std :: endl;
		
	pause_Resume = IMG_LoadTexture(renderer, "assets/Table/pause_resume.png") ;	
	if(!pause_Resume) std :: cout << "Fail to load texture: assets/Table/pause_resume.png\n" << SDL_GetError() << std :: endl;
		else std :: cout << "Loaded: assets/Table/pause_resume.png" << std :: endl;
	
	pause_Quit = IMG_LoadTexture(renderer, "assets/Table/pause_quit.png") ;	
	if(!pause_Quit) std :: cout << "Fail to load texture: assets/Table/pause_quit.png\n" << SDL_GetError() << std :: endl;
		else std :: cout << "Loaded: assets/Table/pause_quit.png" << std :: endl;
		
		
	gameOver = IMG_LoadTexture(renderer, "assets/BGR/gameOver.png") ;	
	if(!gameOver) std :: cout << "Fail to load texture: assets/BGR/gameOver.png\n" << SDL_GetError() << std :: endl;
		else std :: cout << "Loaded: assets/BGR/gameOver.png" << std :: endl;
		

	win = IMG_LoadTexture(renderer, "assets/BGR/win.png") ;	
	if(!win) std :: cout << "Fail to load texture: assets/BGR/win.png\n" << SDL_GetError() << std :: endl;
		else std :: cout << "Loaded: assets/BGR/win.png" << std :: endl;
		
	setting = IMG_LoadTexture(renderer, "assets/Setting/setting.png") ;	
	if(!setting) std :: cout << "Fail to load texture: assets/Setting/setting.png\n" << SDL_GetError() << std :: endl;
		else std :: cout << "Loaded: assets/Setting/setting.png" << std :: endl;
		
		
	soundNone = IMG_LoadTexture(renderer, "assets/Setting/soundNone.png");
	if(!soundNone) std :: cout << "Fail to load texture: assets/Setting/soundNone.png\n" << SDL_GetError() << std :: endl;
	else std :: cout << "Loaded: assets/Setting/soundNone.png" << std :: endl;
	
	soundOne = IMG_LoadTexture(renderer, "assets/Setting/soundOne.png");
	if(!soundOne) std :: cout << "Fail to load texture: assets/Setting/soundOne.png\n" << SDL_GetError() << std :: endl;
	else std :: cout << "Loaded: assets/Setting/soundOne.png" << std :: endl;
	
	for(int i=0 ; i<6 ; i++) {
		char filePath[50] ;
		sprintf(filePath, "assets/HP/hp%d.png", i) ;
		SDL_Texture* texture = IMG_LoadTexture(renderer, filePath) ;
		if(!texture) printf("Fail to load texture: %s\n", filePath) ;
			else {
				printf("Loaded: %s\n", filePath) ;
				framesHP.push_back(texture) ;
			}
			
			 
		sprintf(filePath, "assets/EXP/exp%d.png", i) ;
		texture = IMG_LoadTexture(renderer, filePath) ;
		if(!texture) printf("Fail to load texture: %s\n", filePath) ;
			else {
				printf("Loaded: %s\n", filePath) ;
				framesEXP.push_back(texture) ;
			}
	}
}

void UIManager :: RenderBGR() {
	SDL_RenderCopy(renderer, background, NULL, NULL) ;
}

void UIManager :: RenderTable() {
	SDL_Rect tableRect ;
	tableRect.w = 384 ;
	tableRect.h = 384 ;
	tableRect.x = (SCREEN_WIDTH - 384) / 2; 
    tableRect.y = (SCREEN_HEIGHT - 384) / 2;
    SDL_RenderCopy(renderer, table, NULL, &tableRect) ;
}

void UIManager :: RenderPauseMenu() {
    SDL_RenderCopy(renderer, pause_Resume, NULL, &btnResume) ;
    SDL_RenderCopy(renderer, pause_Quit, NULL, &btnQuitPause) ;
}


void UIManager::RenderHP() {
    // 🔥 Vẽ thanh máu của người chơi
    int hp = player->hp;
    int hpMax = player->maxHp;

    int barWidth = 32;  // Độ rộng tối đa của thanh máu
    int barHeight = 6;  // Độ cao của thanh máu
    int filledWidth = (hp * barWidth) / hpMax; // Độ rộng theo % máu còn lại

    SDL_Rect barBackground = { player->x + 15, player->y - 15, barWidth, barHeight };
    SDL_Rect barFill = { player->x + 15, player->y - 15, filledWidth, barHeight };

    // Vẽ nền thanh máu (màu đen)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &barBackground);

    // Vẽ phần máu còn lại (màu đỏ)
    SDL_SetRenderDrawColor(renderer, 217, 15, 30, 255);
    SDL_RenderFillRect(renderer, &barFill);

    // 🔥 Chọn danh sách quái phù hợp theo bản đồ hiện tại
    if(player->currentMap != 1) {
	    std::vector<Monsters>* currentMonsters = nullptr;
	    switch (player->currentMap) {
	        case 0: currentMonsters = &MonstersOop->m0monsters; break;
	        case 2: currentMonsters = &MonstersOop->m2monsters; break;
	        case 3: currentMonsters = &MonstersOop->m3monsters; break;
	        default: return;
	    }
	
	    // 🔥 Vẽ thanh máu cho từng quái vật trong danh sách hiện tại
	    for (auto& monster : *currentMonsters) {
	        int filledWidth = (monster.hp * barWidth) / monster.maxHp;
	
	        SDL_Rect barBackground = { monster.x + 15, monster.y - 8, barWidth, barHeight };
	        SDL_Rect barFill = { monster.x + 15, monster.y - 8, filledWidth, barHeight };
	
	        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	        SDL_RenderFillRect(renderer, &barBackground);
	
	        SDL_SetRenderDrawColor(renderer, 217, 15, 30, 255);
	        SDL_RenderFillRect(renderer, &barFill);
	    }
	}
	
	if(player->currentMap == 1) {
		int hp = boss->hp;
	    int hpMax = boss->maxHp;
	
	    int barWidth = 64;  // Độ rộng tối đa của thanh máu
	    int barHeight = 10;  // Độ cao của thanh máu
	    int filledWidth = (hp * barWidth) / hpMax; // Độ rộng theo % máu còn lại
	
	    SDL_Rect barBackground = { boss->x + 32, boss->y - 15, barWidth, barHeight };
	    SDL_Rect barFill = { boss->x + 32, boss->y - 15, filledWidth, barHeight };
	
	    // Vẽ nền thanh máu (màu đen)
	    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	    SDL_RenderFillRect(renderer, &barBackground);
	
	    // Vẽ phần máu còn lại (màu đỏ)
	    SDL_SetRenderDrawColor(renderer, 217, 15, 30, 255);
	    SDL_RenderFillRect(renderer, &barFill);
	}
    // 🔥 Reset màu vẽ sau khi hoàn tất
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


void UIManager::HandleInput(SDL_Event event) {
    if(event.type == SDL_MOUSEBUTTONDOWN )  {

		if(event.button.button == SDL_BUTTON_LEFT) {
			int mouseX, mouseY ;
			SDL_GetMouseState(&mouseX, &mouseY) ;
		} 
	}
}



void UIManager :: RenderEXP() {

    int exp = player->exp;
    int expMax = player->maxExpLevel;

    int barWidth = 32;  // Độ rộng tối đa của thanh EXP
    int barHeight = 6;   // Độ cao của thanh
    int filledWidth = (exp * barWidth) / expMax; // Độ rộng theo % EXP

    SDL_Rect barBackground = { player->x + 15, player->y - 8, barWidth, barHeight };  // Vị trí trên màn hình
    SDL_Rect barFill = { player->x + 15, player->y - 8, filledWidth, barHeight };

    // Vẽ nền thanh EXP (màu đen)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &barBackground);

    // Vẽ thanh EXP (màu xanh dương)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &barFill);

    // Reset màu vẽ
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

}

void UIManager::RenderScores() {

	// Màu chữ
	SDL_Color textColor; 
	if(player->currentMap != 1) textColor = {255, 255, 0, 255}; 
		else textColor = {255, 0, 0, 255};

	// Tạo chuỗi hiển thị điểm số
	std::string scoreText = "Score: " + std::to_string(player->scores);
	std::string highScoreText = "HighScore: " + std::to_string(player->highScore);
	std::string hpText = "Hp: " + std::to_string(player->hp) + "/" + std::to_string(player->maxHp);
	std::string levelText = "Level: " + std::to_string(player->level);
	std::string isKeyBoss = "Boss Key: " + std::string(player->keyBoss ? "True" : "False");

	
	// Tạo Surface chứa chữ
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
	SDL_Surface* highScoreSurface = TTF_RenderText_Solid(font, highScoreText.c_str(), textColor);
	SDL_Surface* hpSurface = TTF_RenderText_Solid(font, hpText.c_str(), textColor);
	SDL_Surface* levelSurface = TTF_RenderText_Solid(font, levelText.c_str(), textColor);
	SDL_Surface* keySurface = TTF_RenderText_Solid(font, isKeyBoss.c_str(), textColor);
	
	if (!scoreSurface || !highScoreSurface || !hpSurface || !levelSurface || !keySurface) {

	    printf("Lỗi tạo Surface! SDL_ttf Error: %s\n", TTF_GetError());
	    return;
	}
	
	// Tạo Texture từ Surface
	SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

	SDL_Texture* highScoreTexture = SDL_CreateTextureFromSurface(renderer, highScoreSurface);
	SDL_Texture* hpTexture = SDL_CreateTextureFromSurface(renderer, hpSurface);
	SDL_Texture* levelTexture = SDL_CreateTextureFromSurface(renderer, levelSurface);
	SDL_Texture* keyBossTexture = SDL_CreateTextureFromSurface(renderer, keySurface);
	
	int scoreW = scoreSurface->w, scoreH = scoreSurface->h;
	int highScoreW = highScoreSurface->w, highScoreH = highScoreSurface->h;
	int hpW = hpSurface->w, hpH = hpSurface->h;
	int levelW = levelSurface->w, levelH = levelSurface->h;
	int keyW = keySurface->w, keyH = keySurface->h;
	
	// Giải phóng surface
	SDL_FreeSurface(scoreSurface); 
	SDL_FreeSurface(highScoreSurface);
	SDL_FreeSurface(hpSurface);
	SDL_FreeSurface(levelSurface);
	SDL_FreeSurface(keySurface);
	
	if (!scoreTexture || !highScoreTexture || !hpTexture || !levelTexture || !keyBossTexture) {

	    printf("Lỗi tạo Texture! SDL_ttf Error: %s\n", TTF_GetError());
	    return;
	}
	
	// Định vị trí trên màn hình (góc trên bên trái)

	SDL_Rect scoreRect = {10, 10, scoreW / 2, scoreH / 2};
	SDL_Rect highScoreRect = {10, 40, highScoreW / 2, highScoreH / 2};
	SDL_Rect hpRect = {10, 70, hpW / 2, hpH / 2};
	SDL_Rect levelRect = {10, 100, levelW / 2, levelH / 2};
	SDL_Rect keyBossRect = {10, 130, keyW / 2, keyH / 2};
	
	// Vẽ text lên màn hình
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
	SDL_RenderCopy(renderer, highScoreTexture, NULL, &highScoreRect);
	SDL_RenderCopy(renderer, hpTexture, NULL, &hpRect);
	SDL_RenderCopy(renderer, levelTexture, NULL, &levelRect);
	SDL_RenderCopy(renderer, keyBossTexture, NULL, &keyBossRect);
	
	// Giải phóng Texture khi không cần nữa
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(highScoreTexture);
	SDL_DestroyTexture(hpTexture);
	SDL_DestroyTexture(levelTexture);
	SDL_DestroyTexture(keyBossTexture);
}

void UIManager ::  RenderButtonPause() {
	SDL_Rect btnPause = {970, 0, 60, 60} ;
	SDL_RenderCopy(renderer, buttonPause, NULL, &btnPause);
}

void UIManager :: RenderGameOver() {
	SDL_RenderCopy(renderer, gameOver, NULL, NULL);

	// Màu chữ (đen)
	SDL_Color textColor = {0, 0, 0, 255};
	
    // Tạo chuỗi hiển thị điểm số
    std::string scoreText = "Score: " + std::to_string(player->scores);
	
    // Tạo Surface chứa chữ
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
//    SDL_Surface* scoreMaxSurface = TTF_RenderText_Solid(font, scoreMaxText.c_str(), textColor);
    

    // Tạo Texture từ Surface
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

    
     // Giải phóng surface
    SDL_FreeSurface(scoreSurface); 
//	SDL_FreeSurface(scoreMaxSurface);
	
    if (!scoreTexture) {
        printf("Lỗi tạo Texture! SDL_ttf Error: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    // Định vị trí điểm số trên màn hình 
    SDL_Rect scoreRect = {460, 285, scoreSurface->w, scoreSurface->h};
//	SDL_Rect scoreMaxRect = {460, 255, scoreMaxSurface->w, scoreMaxSurface->h};
	
    // Render điểm số lên màn hình
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);

 	
    // Giải phóng bộ nhớ
    SDL_DestroyTexture(scoreTexture);

	
	SDL_RenderCopy(renderer, pause_Quit, NULL, &btnQuitGameOver) ;
}

void UIManager :: RenderSetting() {
	SDL_RenderCopy(renderer, setting, NULL, NULL) ;
}

void UIManager::RenderNotificationBoss() {
    if (player->currentMap == 1 && !notiBoss) {
        // Kiểm tra xem font có hợp lệ không
        if (font == nullptr) {
            std::cerr << "Error: Font could not be loaded!" << std::endl;
            return;
        }

        // Tạo màu sắc chữ (màu đỏ)
        SDL_Color textColor = {255, 0, 0, 255};

        // Tạo surface chứa văn bản thông báo
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Boss: [Lai Thai Duc] has appeared!", textColor);

        if (textSurface == nullptr) {
            std::cerr << "Error: Unable to create text surface!" << std::endl;
            return;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if (textTexture == nullptr) {
            std::cerr << "Error: Unable to create texture from surface!" << std::endl;
            SDL_FreeSurface(textSurface); 
            return;
        }

        // Vị trí hiển thị văn bản
        SDL_Rect textRect = {SCREEN_WIDTH / 2 - textSurface->w / 2, 100, textSurface->w, textSurface->h};

        // Lưu lại thời gian bắt đầu khi hiển thị thông báo, nếu chưa lưu
        if(startTimeBoss == 0) startTimeBoss = SDL_GetTicks() ;

        // Khoảng thời gian để chữ biến mất (2 giây)
        Uint32 currentTime = SDL_GetTicks();
        Uint32 duration = 2000;

        if (currentTime - startTimeBoss < duration) {
            // Tính toán độ alpha từ 255 đến 0
            float alpha = 255 - (255 * (currentTime - startTimeBoss) / duration);
            SDL_SetTextureAlphaMod(textTexture, static_cast<Uint8>(alpha));

            // Vẽ chữ lên màn hình
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        } else {
            // Nếu hết thời gian, không vẽ nữa
            notiBoss = true;
        }

        // Giải phóng tài nguyên
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void UIManager::RenderNotificationWhenCollectBox() {
	if(notiBox) { //nếu nhặt được hộp
     // Kiểm tra xem font có hợp lệ không
        if (font == nullptr) {
            std::cerr << "Error: Font could not be loaded!" << std::endl;
            return;
        }

        // Tạo màu sắc chữ (màu đỏ)
        SDL_Color textColor = {255, 0, 0, 255};

        // Tạo surface chứa văn bản thông báo
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, message, textColor);

        if (textSurface == nullptr) {
            std::cerr << "Error: Unable to create text surface!" << std::endl;
            return;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if (textTexture == nullptr) {
            std::cerr << "Error: Unable to create texture from surface!" << std::endl;
            SDL_FreeSurface(textSurface); 
            return;
        }

        // Vị trí hiển thị văn bản
        SDL_Rect textRect = {SCREEN_WIDTH / 2 - textSurface->w / 2, 100, textSurface->w, textSurface->h};

        // Lưu lại thời gian bắt đầu khi hiển thị thông báo, nếu chưa lưu

        // Khoảng thời gian để chữ biến mất (2 giây)
        Uint32 currentTime = SDL_GetTicks();
        Uint32 duration = 3000;

        if (currentTime - startTime < duration) {
            // Tính toán độ alpha từ 255 đến 0
            float alpha = 255 - (255 * (currentTime - startTime) / duration);
            SDL_SetTextureAlphaMod(textTexture, static_cast<Uint8>(alpha));

            // Vẽ chữ lên màn hình
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        } else {
            // Nếu hết thời gian, không vẽ nữa
            notiBox = false ;
        }

        // Giải phóng tài nguyên
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

void UIManager :: RenderWin() {
	SDL_RenderCopy(renderer, win, NULL, NULL);
	SDL_RenderCopy(renderer, pause_Quit, NULL, &btnQuitGameOver) ;
}

void UIManager :: RenderSound() {
	if(sound) SDL_RenderCopy(renderer, soundOne, NULL, &btnSound) ;
		else SDL_RenderCopy(renderer, soundNone, NULL, &btnSound) ;
} 

 
