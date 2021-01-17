#include "player2.h"
#include "graphics.h"
#include "game.h"


void Player2::update()
{
	//player's movement
	if ( graphics::getKeyState(graphics::SCANCODE_LEFT))
	{
		pos_x -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if ( graphics::getKeyState(graphics::SCANCODE_RIGHT))
	{
		pos_x += speed * graphics::getDeltaTime() / 10.0f;
	}
	if ( graphics::getKeyState(graphics::SCANCODE_UP))
	{
		pos_y -= speed * graphics::getDeltaTime() / 10.0f;
	}
	if ( graphics::getKeyState(graphics::SCANCODE_DOWN))
	{
		pos_y += speed * graphics::getDeltaTime() / 10.0f;
	}


	//bullet's movement

	if (graphics::getKeyState(graphics::SCANCODE_KP_ENTER) && !bullet_exists)
	{
		graphics::playSound(std::string(ASSET_PATH) + "blast.mp3", 0.5f, false);
		bullet_exists = true;
		bpos_x = pos_x;
		bpos_y = pos_y - 30;

		bullet_drawn = true;
	}
	if (bullet_exists)
	{
		bpos_x -= 7;

	}
	if (bullet_exists && bpos_x < 10)
	{
		bpos_x = 0, bpos_y = 0;
		bullet_drawn = false;
		bullet_exists = false;
		dealtdamage = false;
	}
	//stay inside canvas (and inside player's boundaries)
	//if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH)pos_x = CANVAS_WIDTH;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;
	if (pos_x < CANVAS_WIDTH-200) pos_x = CANVAS_WIDTH - 200;


}

Player2::Player2(const Game& mygame)
	:GameObject(mygame)
{

}




void Player2::draw()
{

	graphics::Brush br;


	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);
	br.texture = std::string(ASSET_PATH) + "ship2.png";
	br.outline_opacity = 0.0f;
	//draw ship
	graphics::setOrientation(+90.f);
	graphics::drawRect(pos_x, pos_y, 60, 60, br);
	graphics::setOrientation(0.f);


	//draw healthbar
	if (hp == 4) { br.texture = std::string(ASSET_PATH) + "4_4healthbar.png"; graphics::drawRect(CANVAS_WIDTH - 100, CANVAS_HEIGHT - 20, 100, 100, br); }
	else if (hp == 3) { br.texture = std::string(ASSET_PATH) + "3_4healthbar.png"; graphics::drawRect(CANVAS_WIDTH - 100, CANVAS_HEIGHT - 20, 100, 100, br); }
	else if (hp == 2) { br.texture = std::string(ASSET_PATH) + "2_4healthbar.png"; graphics::drawRect(CANVAS_WIDTH - 100, CANVAS_HEIGHT - 20, 100, 100, br); }
	else if (hp == 1) { br.texture = std::string(ASSET_PATH) + "1_4healthbar.png"; graphics::drawRect(CANVAS_WIDTH - 100, CANVAS_HEIGHT - 20, 100, 100, br); }
	else if (hp == 4) { br.texture = std::string(ASSET_PATH) + "0_4healthbar.png"; graphics::drawRect(CANVAS_WIDTH - 100, CANVAS_HEIGHT - 20, 100, 100, br); }

	//draw ship fuel
	br.texture = "";
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f + glow * 0.7f;
	br.fill_color[2] = 0.0f;
	br.fill_secondary_color[0] = 0.3f;
	br.fill_secondary_color[1] = 0.1f;
	br.fill_secondary_color[2] = 0.0f;
	br.fill_opacity = 1.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;


	graphics::drawDisk(pos_x+35, pos_y, 20, br);






	//draw bullet
	if (!dealtdamage) {
		glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 10);
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 0.5f + glow * 0.7f;
		br.fill_color[2] = 0.0f;
		br.fill_secondary_color[0] = 0.3f;
		br.fill_secondary_color[1] = 0.1f;
		br.fill_secondary_color[2] = 0.0f;
		br.fill_opacity = 1.0f;
		br.fill_secondary_opacity = 0.0f;
		br.gradient = true;
		if (bullet_exists && !(bpos_y < 10)) {
			graphics::drawDisk(bpos_x-15, bpos_y+30, 10, br);
		}
	}


}


void Player2::init() {}


