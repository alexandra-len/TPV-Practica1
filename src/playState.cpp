#include "playState.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <format>

#include <SDL3_image/SDL_image.h>

#include "texture.h"
#include "vehicle.h"
#include "log.h"
#include "wasp.h"
#include "frog.h"
#include "homedfrog.h"
#include "infobar.h"
#include "turtlegroup.h"

#include "SDLError.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"

PlayState::PlayState(Game* game)
{

	if (!SDL_LoadWAV(JUMP_FILE, &jumpSpec, &jumpData, &jumpDataLen)) {
		throw SDLError();
	}

	// Crea audio stream basado en el formato del WAV cargado
	jumpStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &jumpSpec, nullptr, nullptr);
	if (!jumpStream) {
		SDL_free(jumpData);
		throw SDLError();
	}

	loadMap();

	HomedFrog* nest;
	// Crea los nidos
	for (int i = 0; i < NEST_NR; i++) {
		nest = new HomedFrog(this, game->getTexture(Game::FROG), Point2D<int>(NEST_FROG_STARTING_X + NEST_FROG_DISTANCE_X * i, NEST_FROG_Y));
		nests.push_back(nest);
		objects.push_back(nest);

	}
	nestsOccupied = 0;

	// Inicializa el info bar
	infoBar = new InfoBar(this, game->getTexture(Game::FROG));

	remainingSeconds = timeLimitSeconds;
	lastSecondTick = SDL_GetTicks();

	// Inicializa el tiempo para la aparición de la primera avispa
	timeUntilWasp = getRandomRange(WASP_MIN_DELAY, SDL_GetTicks() + WASP_MIN_DELAY);
	waspDestructionTime = SDL_GetTicks() + timeUntilWasp;
}

PlayState::~PlayState()
{
	delete infoBar;

	for (auto& obj : objects) {
		delete obj;
	}
	if (jumpStream) {
		SDL_DestroyAudioStream(jumpStream);
		jumpStream = nullptr;
	}
	if (jumpData) {
		SDL_free(jumpData);
		jumpData = nullptr;
	}
}

void
PlayState::render() const
{
	SDL_Renderer* r = game-> getRenderer();
	// Limpia la pantalla
	SDL_RenderClear(r);

	// Renderiza el fondo
	game-> getTexture(Game::BACKGROUND)->render();

	for (auto* obj : objects) {
		obj->render();
	}

	infoBar->render();

	SDL_RenderPresent(r);

}

void
PlayState::update()
{
	for (auto& obj : objects) {
		obj->update();
	}

	infoBar->update();

	Uint32 now = SDL_GetTicks();
	if (now - lastSecondTick >= 1000) {

		int secsPassed = (now - lastSecondTick) / 1000;
		remainingSeconds -= secsPassed;
		lastSecondTick += secsPassed * 1000;

		if (remainingSeconds <= 0) {
			player->onTimeEnd();
			resetTimer();
		}

		std::cout << "Tiempo restante: " << remainingSeconds << std::endl;
	}
	// Obtiene el tiempo actual
	currentTime = SDL_GetTicks();

	// Genera una avispa
	if (currentTime >= waspDestructionTime) {
		int nestNr;
		// Elige un nido aleatorio que no esté ocupado
		do {
			nestNr = getRandomRange(0, NEST_NR - 1);
		} while (nests[nestNr]->isHome());

		// Crea una avispa en la posición del nido elegido, con vida aleatoria
		Wasp* newWasp = new Wasp(this, game->getTexture(Game::WASP), Point2D<int>(waspPositions[nestNr].getX(), NEST_ROW_Y), Vector2D<float>(0, 0), getRandomRange(WASP_MIN_DELAY, WASP_MAX_DELAY));
		objects.push_back(newWasp);
		newWasp->setAnchor(--objects.end());

		// Programa la próxima avispa
		timeUntilWasp = getRandomRange(WASP_MIN_DELAY, SDL_GetTicks() + WASP_MIN_DELAY);
		waspDestructionTime = currentTime + timeUntilWasp;
	}
}
