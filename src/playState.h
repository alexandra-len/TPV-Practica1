#pragma once
#include "GameState.h"
#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include <random>
#include <list>

class Texture;
class InfoBar;
class SceneObject;
class Frog;
class HomedFrog;

class PlayState : public GameState
{
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

	static constexpr int TILE_SIZE = 32;
	static constexpr int FROG_COLLISION_MARGIN = 8;
	static constexpr int LOW_MARGIN = 36;

	static constexpr int LOG1_TEXTURE_NR = 7;
	static constexpr int VEHICLE1_TEXTURE_NR = 1;

	static constexpr int TURTLE_SINK_RATE = 225;
	static constexpr int TURTLE_SINK_FRAMES = 7;
	static constexpr int TURTLE_STATIC_FRAMES = 2;

	static constexpr int VEHICLE_BACKJUMP = 0;

	static constexpr int TIME_LIMIT = 60;

private:

	std::list<SceneObject*> objects;
	std::vector<Anchor> objToDelete;
	std::vector<HomedFrog*> nests;
	Frog* player;
	InfoBar* infoBar;

	// Posiciones predefinidas para las avispas
	std::vector<Point2D<int>> waspPositions = { Point2D<int>(20,25), Point2D<int>(116,25), Point2D<int>(212,25), Point2D<int>(308,25), Point2D<int>(404,25), };

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
	PlayState(Game*game);
	~PlayState();

	void render() const override;
	void update()override;
	void deleteObjects();
	void loadMap();
	bool checkVictory();
	void restartGame();
	// Comprueba si hay algún objeto colocado en ese rectángulo
	Collision checkCollision(const SDL_FRect& rect) const;

	int getRandomRange(int, int);

	void deleteAfter(Anchor iterator) {
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

	/*SDL_Renderer* getRenderer() {
		return renderer;
	}*/

	void handleEvent(const SDL_Event& event) override;
	void resetTimer();

	void playJumpSound();

	int getRemainingSeconds() const {
		return remainingSeconds;
	}
};

