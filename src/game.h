#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include "vector2D.h"
#include "wasp.h"
#include <random>

struct Collision
{
	enum Type {
		NONE,
		ENEMY,
		PLATFORM
	};

	Type type;
	Vector2D<float> speed;
};

// Declaraciones anticipadas
class Texture;
class Log;
class Vehicle;

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
	static constexpr int RIVER_LOW = 210;

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
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;

	Log* logShort ;
	Log* logLong ;
	Vehicle* vehicleTest;

	std::vector<Log*> logs;
	std::vector<Vehicle*> vehicles;

	std::mt19937 randomGenerator;

	void render() const;
	void update();
	void handleEvents();

	bool exit;

	// Elemento del juego
	// TODO: añadir atributos para los objetos del juego

public:
	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();

	// Comprueba si hay algún objeto colocado en ese rectángulo
	bool checkCollision(const SDL_FRect& rect) const;

	int getRandomRange(int, int);
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
