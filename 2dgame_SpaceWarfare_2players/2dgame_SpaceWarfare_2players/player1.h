#pragma once
#include "gameobject.h"
#include "config.h"
class Player1 : public GameObject
{
	float speed = 10.0f; //fps
	bool bullet_exists = false; //secures that the spaceship cant shoot before the last bullet it shooted dissapears (hits the player or gets out of the boundaries)
	bool bullet_drawn = false;
public:
	float bpos_x = 0, bpos_y = 0; //bullet position
	float pos_x = 50, pos_y = CANVAS_HEIGHT/2;
	int hp = 4;
	bool 	dealtdamage = false; //secures that one bullet can cause damage to the enemy only one time 
	Player1(const class Game& mygame);
	void update() override;
	void draw() override;
	void init() override;
	void shoot() {}

};