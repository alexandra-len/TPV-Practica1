#pragma once

class GameState;

class GameObject
{
protected:
	GameState* gameS;

	GameObject() {
		gameS = nullptr;
	};

	GameObject(GameState* gS);

public:
	virtual ~GameObject() {}

	virtual void render() const = 0;
	virtual void update() = 0;
};
