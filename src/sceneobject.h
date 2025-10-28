#pragma once
#include "gameobject.h"
class SceneObject : public GameObject
{
	Point2D<int> position;
	int width;
	int height;
	Texture* texture;

public:
	SceneObject(Game* g, Texture* t, Point2D<int> p) : GameObject(g), texture(t), position(p) {}
	void render() override {
		
	}

};

