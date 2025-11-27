#include "playState.h"
#include "gameState.h"

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <format>
#include <SDL3_image/SDL_image.h>

#include "vehicle.h"
#include "log.h"
#include "wasp.h"
#include "frog.h"
#include "homedfrog.h"
#include "infobar.h"
#include "turtlegroup.h"
#include "label.h"
#include "vector2D.h"
#include "collision.h"

#include "FileNotFoundError.h"
#include "FileFormatError.h"
#include "SDLError.h"

#include "PauseState.h"

using namespace std;

PlayState::PlayState(Game* game, string map) : GameState(game), mapFile(MAP_FILE + map + ".txt")
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

	GameState::addObject(new Label(this, game->getTexture(Game::BACKGROUND), { 0,0 }));

	loadMap();

	HomedFrog* nest;
	// Crea los nidos
	for (int i = 0; i < NEST_NR; i++) {
		nest = new HomedFrog(this, game->getTexture(Game::FROG), Point2D<int>(NEST_FROG_STARTING_X + NEST_FROG_DISTANCE_X * i, NEST_FROG_Y));
		nests.push_back(nest);
		sceneObjects.push_back(nest);
		GameState::addObject(nest);

	}
	nestsOccupied = 0;

	// Inicializa el info bar
	infoBar = new InfoBar(this, game->getTexture(Game::FROG));
	GameState::addObject(infoBar);
	updateInfoBar();

	

	remainingSeconds = timeLimitSeconds;
	lastSecondTick = SDL_GetTicks();

	// Inicializa el tiempo para la aparición de la primera avispa
	timeUntilWasp = getRandomRange(WASP_MIN_DELAY, SDL_GetTicks() + WASP_MIN_DELAY);
	waspDestructionTime = SDL_GetTicks() + timeUntilWasp;
}

PlayState::~PlayState()
{
	delete infoBar;

	for (auto& obj : sceneObjects) {
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
PlayState::update()
{
	updateTime();

	updateWasps();
	updateInfoBar();
	GameState::update();
}

void PlayState::updateTime() {
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
}

void PlayState::updateWasps() {
	// Obtiene el tiempo actual
	currentTime = SDL_GetTicks();

	// Genera una avispa
	if (currentTime >= waspDestructionTime) {
		int nestNr;
		// Elige un nido aleatorio que no esté ocupado
		do {
			nestNr = getRandomRange(0, NEST_NR - 1);
		} while (nests[nestNr]->isHome());

		cout << "creating wasp nido " << nestNr << endl;
		// TODO: create wasp properly && check wasp collision not working
		// Crea una avispa en la posición del nido elegido, con vida aleatoria
		Wasp* newWasp = new Wasp(this, game->getTexture(Game::WASP), Point2D<int>(waspPositions[nestNr].getX(), NEST_ROW_Y), Vector2D<float>(0, 0), getRandomRange(WASP_MIN_DELAY, WASP_MAX_DELAY));
		newWasp->setPlayAnchor(PlayState::addObject(newWasp));
		newWasp->setGameAnchor(GameState::addObject(newWasp));

		// Programa la próxima avispa
		timeUntilWasp = getRandomRange(WASP_MIN_DELAY, SDL_GetTicks() + WASP_MIN_DELAY);
		waspDestructionTime = currentTime + timeUntilWasp;
	}
}

void PlayState::removeObject(PlayState::Anchor toRemove) {
	sceneObjects.erase(toRemove);
}

void PlayState::updateInfoBar() {
	infoBar->setTime(remainingSeconds);
	infoBar->setHP(frogHP);
}

void PlayState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);
	if (event.type == SDL_EVENT_KEY_DOWN) {
		if (event.key.key == SDLK_ESCAPE) game->pushState(new PauseState(game,this));
	}
}

PlayState::Anchor PlayState::addObject(SceneObject* s) {
	sceneObjects.push_back(s);
	return --sceneObjects.end();
}

void PlayState::deleteObjects() {
	for (auto& obj : objToDelete) {
		delete* obj;
		sceneObjects.erase(obj);
	}

	objToDelete.clear();
}

int PlayState::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<int>(min, max)(randomGenerator);
}

Collision PlayState::checkCollision(const SDL_FRect& rect)const
{
	Collision col{ Collision::NONE, {0,0} };

	for (const auto& obj : sceneObjects) {
		col = obj->checkCollision(rect);
		if (col.type != Collision::NONE)
			return col;
	}
	if (col.type != Collision::NONE)
		return col;

	for (auto& n : nests) {
		col = n->checkCollision(rect);
		if (col.type != Collision::NONE)
			return col;
	}

	return col;
}

void PlayState::loadMap() {
	ifstream map;
	map.open(mapFile);

	if (!map) {
		throw FileNotFoundError(mapFile);
	}

	int lineCounter = 1;

	try {
		string c;
		while (map >> c) {
			if (!map) {
				throw FileFormatError(mapFile, lineCounter);
			}
			if (c == "#") {
				map.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else {
				// Carga vehículos, troncos y la rana según las etiquetas
				if (c == "V") {
					Vehicle* vehicle = new Vehicle(this, map);
					GameState::addObject(vehicle);
					PlayState::addObject(vehicle);
				}
				else if (c == "L") {
					Log* log = new Log(this, map);
					GameState::addObject(log);
					PlayState::addObject(log);
				}
				else if (c == "T") {
					TurtleGroup* turtles = new TurtleGroup(this, map);
					GameState::addObject(turtles);
					PlayState::addObject(turtles);
				}
				else if (c == "F") {
					player = new Frog(this, map);
					GameState::addObject(player);
					PlayState::addObject(player);
					addEventListener(player);
				}
			}
			lineCounter++;
		}
	}
	catch (...) {
		for (auto* obj : sceneObjects) {
			delete obj;
		}
		throw FileFormatError(mapFile, lineCounter);
	}
}


void PlayState::resetTimer() {
	// Restablece segundos disponibles al valor inicial
	remainingSeconds = timeLimitSeconds;
	// Guarda el tick actual para el proximo segundo
	lastSecondTick = SDL_GetTicks();
	std::cout << "[Timer] reset to " << remainingSeconds << std::endl;
	
	infoBar->setTime(remainingSeconds);
}

bool PlayState::checkVictory() {
	if (nestsOccupied == NEST_NR) {
		nestsFull = true;
	}
	return deadFrog || nestsFull;
}

void PlayState::playJumpSound() {
	if (!jumpStream || !jumpData) return;

	//Vacia el buffer del audio stream
	SDL_ClearAudioStream(jumpStream);

	// Inserta los datos del sonido del salto en el stream
	if (!SDL_PutAudioStreamData(jumpStream, jumpData, (int)jumpDataLen)) {
		std::string log = "SDL_PutAudioStreamData failed: " + (string)SDL_GetError();
		SDL_Log(log.c_str());
		return;
	}
	// Indica al dispositivo de audio que reanude la reproduccion
	SDL_ResumeAudioStreamDevice(jumpStream);
}

void PlayState::restartGame()
{
	// Borrar todos los objetos del juego
	for (auto* obj : sceneObjects) {
		delete obj;
	}
	sceneObjects.clear();

	nests.clear();
	nestsOccupied = 0;

	delete infoBar;

	HomedFrog* nest;
	// Crea los nidos
	for (int i = 0; i < NEST_NR; i++) {
		nest = new HomedFrog(this, game->getTexture(Game::FROG), Point2D<int>(NEST_FROG_STARTING_X + NEST_FROG_DISTANCE_X * i, NEST_FROG_Y));
		nests.push_back(nest);
		sceneObjects.push_back(nest);

	}
	nestsOccupied = 0;

	timeUntilWasp = getRandomRange(WASP_MIN_DELAY, SDL_GetTicks() + WASP_MIN_DELAY);
	waspDestructionTime = SDL_GetTicks() + timeUntilWasp;

	infoBar = new InfoBar(this, game->getTexture(Game::FROG));

	loadMap();

	resetTimer();
}
