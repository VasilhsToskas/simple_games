#pragma once
#include "player1.h"
#include "player2.h"

class Game 
{
	typedef enum{ STATUS_START,STATUS_GAME,STATUS_END} status_t;
	Player1 * player1 = nullptr;
	bool players_initialized = false;
	Player2* player2 = nullptr;
	int status=STATUS_START;
	void updateStartScreen();
	void updateGameScreen();
	void updateEndScreen();
	void drawStartScreen();
	void drawGameScreen();
	void drawEndScreen();
	int kills1 = 0;
	int kills2 = 0;
	float exact_time_game_started;
public:
	void update();
	void draw();
	void init();
	Game();
	~Game();

};