#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include <random>
#include <list>
#include "vector2D.h"
#include "texture.h"

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";
constexpr const char* const MAP_FILE = "../assets/maps/turtles.txt";
constexpr const char* const JUMP_FILE = "../assets/sounds/jump.wav";

// Estructura que representa una colisión
struct Collision
{
	enum Type {
		NONE,
		ENEMY,
		PLATFORM,
		HOME
	};

	Type type;
	Vector2D<float> speed;
};

// Declaraciones anticipadas
class Texture;
class InfoBar;
class SceneObject;
class Frog;
class HomedFrog;

/**
 * Clase principal del juego.
 */
class Game
{
	

public:
	using Anchor = std::list<SceneObject*>::iterator;

	// Se actualiza el juego cada tantos milisegundos
	static constexpr int FRAME_RATE = 30;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;
	static constexpr int WINDOW_WIDTH_MARGIN = 150;
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

	enum TextureName
	{
		FROG = 0,
		BACKGROUND,
		VEHICLE1,
		VEHICLE2,
		VEHICLE3,
		VEHICLE4,
		VEHICLE5,
		LOG1,
		LOG2,
		WASP,
		TURTLES,
		NUM_TEXTURES
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	std::array<Texture*, NUM_TEXTURES> textures;

	std::list<SceneObject*> objects;
	std::vector<Anchor> objToDelete;
	std::vector<HomedFrog*> nests;
	Frog* player;
	InfoBar* infoBar;

	// Posiciones predefinidas para las avispas
	std::vector<Point2D<int>> waspPositions = {Point2D<int>(20,25), Point2D<int>(116,25), Point2D<int>(212,25), Point2D<int>(308,25), Point2D<int>(404,25), };

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

	void render() const;
	void update();
	void deleteObjects();
	void handleEvents();
	void loadMap();
	bool checkVictory();
	void restartGame();

	bool deadFrog = false, nestsFull = false, exit = false;


public:
	Game(); // Constructor
	~Game(); // Destructor

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();

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

	SDL_Renderer* getRenderer() {
		return renderer;
	}

	void resetTimer();

	void playJumpSound();

	int getRemainingSeconds() const {
		return remainingSeconds;
	}
};

// Implementacion inline de getTexture
inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
