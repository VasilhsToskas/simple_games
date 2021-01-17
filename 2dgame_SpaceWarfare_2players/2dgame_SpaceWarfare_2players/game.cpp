#include "game.h"
#include "graphics.h"
#include "config.h"
#include "stdlib.h"



void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_SPACE)) 
	{
		status = STATUS_GAME;
	}
}

void Game::updateGameScreen()
{
	if (!players_initialized && graphics::getGlobalTime() > 1000)
	{
		exact_time_game_started = graphics::getGlobalTime();
		player1 = new Player1(*this);
		player2 = new Player2(*this);
		players_initialized = true;
	}


	if (player1 && player2) {
		//check if player2 bullet hit player1 and act acorrdingly (remove one health from his healthbar or end the game if he died)
		player1->update();
		if (player2->dealtdamage == false && player2->bpos_x < player1->pos_x + 40 && player2->bpos_x > player1->pos_x - 40 && player2->bpos_y < player1->pos_y + 20 && player2->bpos_y > player1->pos_y - 60)
		{
			graphics::playSound(std::string(ASSET_PATH) + "grenade.mp3", 0.5f, false);
			player1->hp -= 1;
			player2->dealtdamage = true;
			if (player1->hp == 0 ) {
				kills2++;
				if (kills1 == 2 || kills2 == 2) {
					status = STATUS_END;
				}
			}
		}
		//check if player1 bullet hit player2 and act acorrdingly (remove one health from his healthbar or end the game if he died)
		player2->update();
		if (player1->dealtdamage == false && player1->bpos_x < player2->pos_x + 40 && player1->bpos_x > player2->pos_x - 40 && player1->bpos_y < player2->pos_y + 20 && player1->bpos_y > player2->pos_y - 60)
		{
			graphics::playSound(std::string(ASSET_PATH) + "grenade.mp3", 0.5f, false);
			player2->hp --;
			player1->dealtdamage = true;
			if (player2->hp == 0 ) {
				kills1++;
				if (kills1 == 2 || kills2 == 2) {
					status = STATUS_END;
				}
			}
		}



	}
	



	//delete players , in order to reset if the user plays again
	if (player1 && (player1->hp==0 || player2->hp == 0)) {
		players_initialized = false;
		player1 = nullptr;
		player2 = nullptr;
		
	}

}

//screen shown when the player dies
void Game::updateEndScreen()
{
	
	if (graphics::getKeyState(graphics::SCANCODE_Y))
	{
		status = STATUS_GAME;
	}
	else if (graphics::getKeyState(graphics::SCANCODE_N)) 
	{
		status = STATUS_START;
	}
}


//screen shown before the game starts (instructions)
void Game::drawStartScreen()
{
	graphics::Brush br;
	char info[100];
	sprintf_s(info, "PLAYER 1 USES AWSD KEYS TO MOVE AND SPACE TO SHOOT");
	graphics::drawText(CANVAS_WIDTH / 2 - 450, CANVAS_HEIGHT / 2 - 50, 30, info, br);
	sprintf_s(info, "PLAYER 2 USES ARROW KEYS TO MOVE AND ENTER TO SHOOT");
	graphics::drawText(CANVAS_WIDTH / 2 - 450, CANVAS_HEIGHT / 2 , 30, info, br);


	sprintf_s(info, "BEST OF 3");
	graphics::drawText(CANVAS_WIDTH / 2 - 120, CANVAS_HEIGHT / 2 +50, 50, info, br);


	sprintf_s(info, "PRESS SPACE TO CONTINUE");
	graphics::drawText(CANVAS_WIDTH / 2 - 200, CANVAS_HEIGHT / 2 +100, 30, info, br);

}

void Game::drawGameScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "space.png";
	br.outline_opacity = 0.0f;

	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT , br);

	//draw player
	if (player1)
		player1->draw();
	if (player2)
		player2->draw();
	//UI info layer
	if (player1 && player2)
	{
		char info[40];
		sprintf_s(info, "Time:(%.1f)", graphics::getGlobalTime()/ 1000- (exact_time_game_started/1000));
		graphics::drawText(30, 30, 20, info, br);
		br.fill_opacity = 0.1f;
		sprintf_s(info, "%d", kills1);
		graphics::drawText(CANVAS_WIDTH / 2 - 150, 100, 100, info, br);
		sprintf_s(info, "%d", kills2);
		graphics::drawText(CANVAS_WIDTH/2 + 50, 100, 100, info, br);
	}
}

void Game::drawEndScreen()
{
	graphics::Brush br;
	char info[40];
	sprintf_s(info, "%d-%d",kills1,kills2);
	graphics::drawText(CANVAS_WIDTH / 2-100, CANVAS_HEIGHT / 2, 100, info, br);
	if (kills1>kills2) {
		sprintf_s(info, "PLAYER 1 WON");
		graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT / 2 + 50, 40, info, br);
	}
	else {
		sprintf_s(info, "PLAYER 2 WON");
		graphics::drawText(CANVAS_WIDTH / 2 - 150, CANVAS_HEIGHT / 2 + 50, 40, info, br);
	}

	sprintf_s(info, "DO YOU WANT TO PLAY AGAIN ? (Y/N)");
	graphics::drawText(CANVAS_WIDTH / 2-380, CANVAS_HEIGHT / 2 + 200, 40, info, br);
}

void Game::update()
{
	if (status == STATUS_GAME) {
		updateGameScreen();
	}
	else if (status == STATUS_START){
		updateStartScreen();
	}
	else if(status == STATUS_END){
		updateEndScreen(); 
	}
}

void Game::draw()
{
	if (status == STATUS_GAME) {
		drawGameScreen();
	}
	else if (status == STATUS_START) {
		drawStartScreen();
	}
	else if (status == STATUS_END) {
		drawEndScreen();
	}
	
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "font.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "DragonCastle.mp3",0.3f,true,10000);

}

Game::Game()
{
}

Game::~Game()
{
	if (player1)
	{
		delete player1; 
	}
	if (player2)
	{
		delete player2;
	}
}
