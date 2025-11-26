#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include <random>
#include <list>
#include "texture.h"
#include "gameStateMachine.h"

// Constantes
constexpr const char* const WINDOW_TITLE = "Frogger 1.0";

constexpr const char* const MAP_FILE = "../assets/maps/Original.txt";


/**
 * Clase principal del juego.
 */
class Game : public GameStateMachine
{

public:

	// Se actualiza el juego cada tantos milisegundos
	static constexpr int FRAME_RATE = 30;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;
	static constexpr int WINDOW_WIDTH_MARGIN = 150;

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

		MENU_BACKGROUND,

		AVISPADO,
		CONTINUAR,
		ELEGIR,
		GAME_OVER,
		GANADO,
		LEFT,
		RIGHT,
		ORGINIAL,
		PRACTICA1,
		REINICIAR,
		SALIR,
		TRIVIAL,
		VELOZ,
		VOLVER,

		NUM_TEXTURES
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	std::array<Texture*, NUM_TEXTURES> textures;

	bool exit = false;


public:
	Game(); // Constructor
	~Game(); // Destructor

	using GameStateMachine::pushState;
	using GameStateMachine::replaceState;
	using GameStateMachine::popState;

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;
	SDL_Renderer* getRenderer() {
		return renderer;
	}

	// Ejecuta el bucle principal del juego
	void run();
};

// Implementacion inline de getTexture
inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
