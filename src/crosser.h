#pragma once

#include "sceneobject.h"

class Crosser : public SceneObject
{
public: 
	Crosser() {};
	Crosser(Game* g, Texture* t, Point2D<int> p, Vector2D<float> s) : SceneObject(g, t, p), speed(s) {
		// La velocidad ajustada al frame rate
		speed = Vector2D<float>(s.getX() / Game::FRAME_RATE, s.getY() / Game::FRAME_RATE);
		windowWidth = Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN - width;
	}

	Crosser(Game* g, std::istream& input, int textureNr) : SceneObject(g) {
		int textureNr, x, y;
		float s;
		input >> x >> y >> s >> textureNr;

		position = Point2D<int>(x, y);
		speed = Vector2D<float>(s / Game::FRAME_RATE, 0);
		texture = game->getTexture((Game::TextureName)(textureNr));

		windowWidth = Game::WINDOW_WIDTH + Game::WINDOW_WIDTH_MARGIN - width;
	}

	void update() override {
		// vehicle:
		//	disappearBorder = window_width + window_margin - width
		//  appearBorder = - width

		// log
		//	disappearBOrder = window width + margin
		//	appearBorder = -window margin
		if (speed.getX() > 0 && position.getX() > disappearBorderRight)
		{
			position = Point2D<int>(appearBorderRight, position.getY());
		}
		
		// vehicle:
		//	disappearBorder = - margin
		//	apparborder = window width

		// log:
		//	disappear border = - (margin + width)
		//	appaer border = window width + window margin - width
		else if (speed.getX() < 0 && position.getX() < disappearBorderLeft)
		{
			position = Point2D<int>(appearBorderLeft, position.getY());
		}
		else {
			position = Point2D<int>(round(position.getX() + speed.getX()), position.getY());
		}
	}

protected:
	Vector2D<float> speed;
	int disappearBorderRight, appearBorderRight, disappearBorderLeft, appearBorderLeft, windowWidth;

};

