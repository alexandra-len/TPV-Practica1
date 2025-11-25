#pragma once
#include "gameState.h"
#include "vector2D.h"
#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include <random>
#include <list>

constexpr const char* const JUMP_FILE = "../assets/sounds/jump.wav";

class InfoBar;
class SceneObject;
class Frog;
class HomedFrog;
struct Collision;

class PlayState : public GameState
{
public:
	using Anchor = std::list<SceneObject*>::iterator;

	// Extremo inferior del río
	static constexpr int RIVER_LOW = 200;

	// Numero de nidos
	static constexpr int NEST_NR = 5;

	// Posiciones de nidos y avispas
	static constexpr int NEST_ROW_Y = 25;
	static constexpr int NEST_FROG_Y = 22;
	static constexpr int NEST_FROG_STARTING_X = 14;
	static constexpr int NEST_FROG_DISTANCE_X = 96;

	// Tiempos de aparición de avispas
	static constexpr int WASP_MIN_DELAY = 1000;
	static constexpr int WASP_MAX_DELAY = 10000;

	static constexpr int TIME_LIMIT = 60;

private:
	std::list<SceneObject*> objects;
	std::vector<Anchor> objToDelete;
	std::vector<HomedFrog*> nests;
	Frog* player;
	InfoBar* infoBar;

	// Posiciones predefinidas para las avispas
	std::vector<Point2D<int>> waspPositions = { Point2D<int>(20,25), Point2D<int>(116,25), Point2D<int>(212,25), Point2D<int>(308,25), Point2D<int>(404,25)};

	// Generador de numeros aleatorios
	std::mt19937 randomGenerator;
	int timeUntilWasp;
	int waspDestructionTime;
	int currentTime;

	int nestsOccupied;

	int frogHP;

	int timeLimitSeconds = TIME_LIMIT;
	int remainingSeconds;
	Uint32 lastSecondTick = 0;

	SDL_AudioStream* jumpStream = nullptr;
	Uint8* jumpData = nullptr;
	Uint32 jumpDataLen = 0;
	SDL_AudioSpec jumpSpec{};

	bool deadFrog = false, nestsFull = false;

public:
	PlayState(Game* game);
	~PlayState();

	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
	
	void loadMap();
	bool checkVictory();
	void restartGame();

	void deleteObjects();
	
	
	// Comprueba si hay algún objeto colocado en ese rectángulo
	Collision checkCollision(const SDL_FRect& rect) const;

	int getRandomRange(int, int);

	void deleteAfter(PlayState::Anchor iterator) {
		objToDelete.push_back(iterator);
	};

	// Suma 1 al sumador de nidos ocupados
	void occupyNest() {
		nestsOccupied++;
	}

	// Configura la variable de vidas totales de la rana
	void setHP(int lives) {
		frogHP = lives;
	}

	int getHP() const {
		return frogHP;
	}

	void frogDeath() {
		deadFrog = true;
	}

	void resetTimer();

	void playJumpSound();

	int getRemainingSeconds() const {
		return remainingSeconds;
	}
};

