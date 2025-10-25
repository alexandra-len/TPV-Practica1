#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include <random>
#include "vector2D.h"

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
class Log;
class Vehicle;
class Wasp;
class Frog;
class HomedFrog;

/**
 * Clase principal del juego.
 */
class Game
{
public:
	// Se actualiza el juego cada tantos milisegundos
	static constexpr int FRAME_RATE = 30;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;
	static constexpr int WINDOW_WIDTH_MARGIN = 150;
	// Extremo inferior del río
	static constexpr int RIVER_LOW = 200;

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
		NUM_TEXTURES
	};

private:
	SDL_Window* window;
	
	std::array<Texture*, NUM_TEXTURES> textures;

	Frog* player;

	std::vector<Log*> logs;
	std::vector<Vehicle*> vehicles;
	std::vector<Wasp*> wasps; 
	std::vector<HomedFrog*> nests;

	std::vector<Point2D<int>> waspPositions = {Point2D<int>(20,25), Point2D<int>(116,25), Point2D<int>(212,25), Point2D<int>(308,25), Point2D<int>(404,25), };

	std::mt19937 randomGenerator;
	int timeUntilWasp;
	int waspDestructionTime;
	int currentTime;


	void render() const;
	void update();
	void handleEvents();

	bool exit;

public:
	SDL_Renderer* renderer;
	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();

	// Comprueba si hay algún objeto colocado en ese rectángulo
	Collision checkCollision(const SDL_FRect& rect) const;

	int getRandomRange(int, int);
	
	// Pone exit a true, cierra el juego
	void exitGame();

	void handleNestCollision(Collision col, HomedFrog* f) const;
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
