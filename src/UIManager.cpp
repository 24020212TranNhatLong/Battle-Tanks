#include "../include/UIManager.h"

UIManager :: UIManager(SDL_Renderer* renderer, Player* player, Monster* MonstersOop, TTF_Font* font) 
	: renderer(renderer), player(player), MonstersOop(MonstersOop), font(font) 
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
		
		
	setting = IMG_LoadTexture(renderer, "assets/Setting/setting.png") ;	
	if(!setting) std :: cout << "Fail to load texture: assets/Setting/setting.png\n" << SDL_GetError() << std :: endl;
		else std :: cout << "Loaded: assets/Setting/setting.png" << std :: endl;
		
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

void UIManager :: RenderHP() {
//ve thanh mau cua player

	int hp = player->hp;
    int hpMax = player->maxHp;

    int barWidth = 32;  // Độ rộng tối đa của thanh EXP
    int barHeight = 6;   // Độ cao của thanh
    int filledWidth = (hp * barWidth) / hpMax; // Độ rộng theo % EXP

    SDL_Rect barBackground = { player->x + 15, player->y - 15, barWidth, barHeight };  // Vị trí trên màn hình
    SDL_Rect barFill = { player->x + 15, player->y - 15, filledWidth, barHeight };  //Vị trí trên màn hình

    // Vẽ nền thanh EXP (màu đen)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &barBackground);

    // Vẽ thanh EXP (màu xanh dương)
    SDL_SetRenderDrawColor(renderer, 217, 15, 30, 255);
    SDL_RenderFillRect(renderer, &barFill);

    // Reset màu vẽ
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	

//vẽ thanh máu của quái
	for(auto& monster : MonstersOop->monsters) {
		int hp = monster.hp;
	    int hpMax = monster.maxHp;
	
	    int barWidth = 32;  // Độ rộng tối đa của thanh EXP
	    int barHeight = 6;   // Độ cao của thanh
	    int filledWidth = (hp * barWidth) / hpMax; // Độ rộng theo % EXP
	
	    SDL_Rect barBackground = { monster.x + 15, monster.y - 8, barWidth, barHeight };  // Vị trí trên màn hình
	    SDL_Rect barFill = { monster.x + 15, monster.y - 8, filledWidth, barHeight }; //Vị trí trên màn hình
	
	    // Vẽ nền thanh EXP (màu đen)
	    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	    SDL_RenderFillRect(renderer, &barBackground);
	
	    // Vẽ thanh EXP (màu xanh dương)
	    SDL_SetRenderDrawColor(renderer, 217, 15, 30, 255);
	    SDL_RenderFillRect(renderer, &barFill);
	
	    // Reset màu vẽ
	    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
}

void UIManager :: HandleInput(SDL_Event event) {
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
	// Màu chữ (trắng)
	SDL_Color textColor = {255, 255, 255, 255};
	
	// Tạo chuỗi hiển thị điểm số
	std::string scoreText = "Score: " + std::to_string(player->scores);
	std::string hpText = "Hp: " + std::to_string(player->hp) + "/" + std::to_string(player->maxHp);
	std::string levelText = "Level: " + std::to_string(player->level);
	
	// Tạo Surface chứa chữ
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
	SDL_Surface* hpSurface = TTF_RenderText_Solid(font, hpText.c_str(), textColor);
	SDL_Surface* levelSurface = TTF_RenderText_Solid(font, levelText.c_str(), textColor);
	
	if (!scoreSurface || !hpSurface || !levelSurface) {
	    printf("Lỗi tạo Surface! SDL_ttf Error: %s\n", TTF_GetError());
	    return;
	}
	
	// Tạo Texture từ Surface
	SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
	SDL_Texture* hpTexture = SDL_CreateTextureFromSurface(renderer, hpSurface);
	SDL_Texture* levelTexture = SDL_CreateTextureFromSurface(renderer, levelSurface);
	
	// Giải phóng surface
	SDL_FreeSurface(scoreSurface); 
	SDL_FreeSurface(hpSurface);
	SDL_FreeSurface(levelSurface);
	
	if (!scoreTexture || !hpTexture || !levelTexture) {
	    printf("Lỗi tạo Texture! SDL_ttf Error: %s\n", TTF_GetError());
	    return;
	}
	
	// Định vị trí trên màn hình (góc trên bên trái)
	SDL_Rect scoreRect = {10, 10, scoreSurface->w/2, scoreSurface->h/2};
	SDL_Rect hpRect = {10, 40, hpSurface->w/2, hpSurface->h/2};
	SDL_Rect levelRect = {10, 70, levelSurface->w/2, levelSurface->h/2};
	
	// Vẽ text lên màn hình
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
	SDL_RenderCopy(renderer, hpTexture, NULL, &hpRect);
	SDL_RenderCopy(renderer, levelTexture, NULL, &levelRect);
	
	// Giải phóng Texture khi không cần nữa
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(hpTexture);
	SDL_DestroyTexture(levelTexture);
}

void UIManager ::  RenderButtonPause() {
	SDL_Rect btnPause = {970, 0, 60, 60} ;
	SDL_RenderCopy(renderer, buttonPause, NULL, &btnPause);
}

void UIManager :: RenderGameOver() {
	SDL_RenderCopy(renderer, gameOver, NULL, NULL);

	// Màu chữ (đen)
	SDL_Color textColor = {0, 0, 0, 255};
	
//	// Kiểm tra nếu file chưa tồn tại, tạo file với giá trị mặc định
//	std::string filePath = "scoreMax.txt";
//	if (!std::ifstream(filePath)) {
//	    writeFile(filePath, 0);
//	}
//	
//	// Ghi điểm vào file nếu cao hơn điểm tối đa
//	writeFile(filePath, player->scores);
//	
//	// Đọc lại điểm cao nhất
//	int scoreMax = readFile(filePath);

	
    // Tạo chuỗi hiển thị điểm số
    std::string scoreText = "Score: " + std::to_string(player->scores);
//	std::string scoreMaxText = "Score Max: " + std::to_string(scoreMax);
	
    // Tạo Surface chứa chữ
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
//    SDL_Surface* scoreMaxSurface = TTF_RenderText_Solid(font, scoreMaxText.c_str(), textColor);
    
//    if (!scoreSurface || !scoreMaxSurface) {
//        printf("Lỗi tạo Surface! SDL_ttf Error: %s\n", TTF_GetError());
//        TTF_CloseFont(font);
//        return;
//    }

    // Tạo Texture từ Surface
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
//    SDL_Texture* scoreMaxTexture = SDL_CreateTextureFromSurface(renderer, scoreMaxSurface);
    
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
// 	SDL_RenderCopy(renderer, scoreMaxTexture, NULL, &scoreMaxRect);
 	
    // Giải phóng bộ nhớ
    SDL_DestroyTexture(scoreTexture);
//	SDL_DestroyTexture(scoreMaxTexture);
	
	SDL_RenderCopy(renderer, pause_Quit, NULL, &btnQuitGameOver) ;
}

void UIManager :: RenderSetting() {
	SDL_RenderCopy(renderer, setting, NULL, NULL) ;
}

