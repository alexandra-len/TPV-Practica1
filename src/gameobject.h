#pragma once

class GameState;

class GameObject
{
protected:
	GameState* gameS;

	GameObject(GameState* gS);

public:
	virtual ~GameObject() = default;

	virtual void render() const = 0;
	virtual void update() = 0;
};
