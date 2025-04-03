#include "../include/BulletProcessing.h" 
BulletProcessing :: BulletProcessing(Player* player, Monster* MonsterOop, Mix_Chunk* shotSound, Boss* boss)  
	: player(player), MonsterOop(MonsterOop), shotSound(shotSound), boss(boss)
	{
}

//*************** Player ***************//

void BulletProcessing :: ShotByPlayer(SDL_Event event) {
    if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		const int gunLength = 35;  // Điều chỉnh tùy theo súng dài hay ngắn
		Uint32 currentTime = SDL_GetTicks() ; //lấy thời gian
		if(currentTime - player->lastTimeShot >= player->speedShot) {  //kiểm tra xem đã bắn được chưa
			player->isAttacking = true ;
			
			// Tọa độ trung tâm xe tăng
			int centerX = player->x + sizePlayerX / 2;
			int centerY = player->y + sizePlayerY / 2;
			
			// Tọa độ đầu nòng súng
			int bulletStartX = centerX + gunLength * sin(player->angleWeapon * PI / 180) - 3 ;
			int bulletStartY = centerY - gunLength * cos(player->angleWeapon * PI / 180) - 3 ;
			
			// Tạo viên đạn tại đầu nòng súng
			bulletsPlayer.push_back({bulletStartX , bulletStartY , player->angleWeapon, 5 + player->level, player->dame});
			Mix_PlayChannel(-1, shotSound, 0);  // Phát âm thanh trên một kênh trống
	//		printf("Bullet shot from (%d, %d) at angle %f\n", bulletStartX, bulletStartY, player->angleWeapon);
			player->lastTimeShot = currentTime ;
		}	
	}
}

void BulletProcessing :: UpdatePositionBulletPlayer() {
//	printf("Number of bullets: %lu\n", bulletsPlayer.size());
	for(size_t i=0 ; i < bulletsPlayer.size() ; i++) {
		bulletsPlayer[i].Update() ;
	}
}

// **************** Monster ****************//

void BulletProcessing::ShotByMonster() {
	//map 1 thì không có quái
	if(player->currentMap == 1) return ;
	
    const int gunLength = 35; // Độ dài súng
    std::vector<Monsters>* currentMonster = nullptr;

    // Lấy danh sách quái của map hiện tại
    switch (player->currentMap) {
        case 0: currentMonster = &MonsterOop->m0monsters; break;
        case 2: currentMonster = &MonsterOop->m2monsters; break;
        case 3: currentMonster = &MonsterOop->m3monsters; break;
    }

    Uint32 currentTimeAttack = SDL_GetTicks(); // Lấy thời gian hiện tại

    // Duyệt từng quái vật trong map hiện tại
    for (auto& monster : *currentMonster) {
        if (monster.isAttacking && currentTimeAttack >= monster.lastTimeAttack + monster.speedShot) { 
            // Chỉ bắn nếu quái đang tấn công và đã đủ thời gian bắn tiếp

            int centerX = monster.x + sizePlayerX / 2;
            int centerY = monster.y + sizePlayerY / 2;

            // Tọa độ đầu nòng súng
            int bulletStartX = centerX + gunLength * sin(monster.angleWeapon * PI / 180) - 3;
            int bulletStartY = centerY - gunLength * cos(monster.angleWeapon * PI / 180) - 3;

            // Tạo viên đạn tại đầu nòng súng
            bulletsMonster.push_back({bulletStartX, bulletStartY, monster.angleWeapon, 5 + player->level, monster.dame});
            if(sound) Mix_VolumeChunk(shotSound, 50) ;	
            	else Mix_VolumeChunk(shotSound, 0) ;
            Mix_PlayChannel(-1, shotSound, 0);  // Phát âm thanh trên một kênh trống

            monster.isShotting = true; // Đánh dấu là quái đã bắn

            monster.lastTimeAttack = currentTimeAttack; // Cập nhật thời điểm bắn lần cuối
        }
    }
}



void BulletProcessing :: UpdatePositionBulletMonster() {
	//map 1 không có quái
	if(player->currentMap == 1) return ;
	
//	std :: cout << bulletsMonster.size() << std :: endl;
	for(size_t i=0 ; i < bulletsMonster.size() ; i++) bulletsMonster[i].Update() ;
}

void BulletProcessing :: Reset() {
	bulletsMonster.clear() ; //xóa hết đạn của quái vật
	bulletsPlayer.clear() ; //xóa hết đạn của người chơi
	bulletsBoss.clear() ; //xóa hết đạn của boss
}

// **************** Monster ****************//
void BulletProcessing::ShotByBoss() {
	if(player->currentMap == 1) {
		const int gunLength = 40;
		Uint32 currentTime = SDL_GetTicks() ;
			if(currentTime >= boss->lastTimeShot + boss->speedShot) {
			int centerX = boss->x + sizeBodyBossX / 2;
	        int centerY = boss->y + sizeBodyBossY / 2;
	
	        // Tọa độ đầu nòng súng
	        int bulletStartX = centerX + gunLength * sin(boss->angleWeapon * PI / 180) - 3;
	        int bulletStartY = centerY - gunLength * cos(boss->angleWeapon * PI / 180) - 3;
	
	        // Tạo viên đạn tại đầu nòng súng
	        bulletsBoss.push_back({bulletStartX, bulletStartY, boss->angleWeapon, boss->speedBullet, boss->dame});
	        
	        if(sound) Mix_VolumeChunk(shotSound, 50) ;	
            	else Mix_VolumeChunk(shotSound, 0) ;
            	
	        Mix_PlayChannel(-1, shotSound, 0);  // Phát âm thanh trên một kênh trống
			boss->isShot = true ;
	        boss->lastTimeShot = currentTime; // Cập nhật thời điểm bắn lần cuối
	    }
	}
} 

void BulletProcessing :: UpdatePositionBulletBoss() {
	if(player->currentMap == 1) {
		for(size_t i=0 ; i < bulletsBoss.size() ; i++) bulletsBoss[i].Update() ;
	}
}
