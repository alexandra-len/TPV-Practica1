#include "mainMenuState.h"
#include "label.h"
#include "button.h"
#include "game.h"
#include "playState.h"
#include "gameStateMachine.h"
#include <filesystem>
#include <fstream>
#include <string>
#include "texture.h"
using namespace std;

constexpr const char* CONFIG_FILE = "config.txt";
const filesystem::path TEXTS_ROOT = "../assets/images/texts";

MainMenuState::MainMenuState(Game* g) : GameState(g)
{
    // Intenta cargar el índice del último mapa seleccionado desde config.txt
	ifstream map(CONFIG_FILE);
	if (map.is_open())
		map >> selectedMap;

    // bg añaade el fondo del menú como un Label
	addObject(new Label(this, game->getTexture(Game::MENU_BACKGROUND),Point2D<int>(0, 0)));
    
    // elegir text
    addObject(new Label(this, game->getTexture(Game::ELEGIR), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::ELEGIR)->getFrameWidth()/2, Game::WINDOW_HEIGHT / 2 - game->getTexture(Game::ELEGIR)->getFrameHeight())));

    Button* exitButton = new Button(this, game->getTexture(Game::SALIR), Point2D<int>(Game::WINDOW_WIDTH / 2 - game->getTexture(Game::SALIR)->getFrameWidth() / 2, 2 * Game::WINDOW_HEIGHT / 3 + game->getTexture(Game::SALIR)->getFrameHeight()));
    //Al hacer clic, saca el estado actual(MainMenuState) de la pila(cierra el juego)
    exitButton->connect([this]()
        {
            game->popState();
        });

    addObject(exitButton);
    
    // Mapa de nombres de mapa a sus IDs de textura (para los botones)

    // Carga dinámica de mapas y creación de botones:
    int i = 0;
    
    // Itera sobre todos los archivos en la carpeta de mapas
    for (auto entry : std::filesystem::directory_iterator("../assets/maps")) {
        string map = path2string(entry.path().stem().string());// Obtiene el nombre del archivo sin extensión
        maps.push_back(map);// Añade el nombre del mapa a la lista

        filesystem::path textPath = TEXTS_ROOT / entry.path().filename().replace_extension(".png");
        string textPathString = path2string(textPath);

        mapTextures[map] = new Texture(game->getRenderer(), textPathString.c_str());

        // Crea un botón con la textura correspondiente al nombre del mapa
        Button* mapButton = new Button(this, mapTextures[map], { Game::WINDOW_WIDTH / 2 - mapTextures[map]->getFrameWidth() / 2, Game::WINDOW_HEIGHT / 2 + mapTextures[map]->getFrameHeight() });
        //Al hacer clic, añade un nuevo PlayState con el mapa seleccionado a la pila
        mapButton->connect([this, i]() {game->pushState(new PlayState(game, maps[i])); });
        mapButton->setActive(false);// Por defecto, todos los botones de mapa están inactivos
        
        addObject(mapButton);

        buttons.push_back(mapButton);

        i++;

    }
    // Activa el botón del mapa cargado o preseleccionado
    buttons[selectedMap]->setActive(true);

    // Crea y posiciona las flechas izquierda y derecha.
    // La posición se calcula para que estén a los lados del botón del mapa
    lArrow = new Button(this, game->getTexture(Game::LEFT), { game->getTexture(Game::LEFT)->getFrameWidth(), Game::WINDOW_HEIGHT / 2 + mapTextures["Avispado"]->getFrameHeight() });
    rArrow = new Button(this, game->getTexture(Game::RIGHT), { Game::WINDOW_WIDTH - game->getTexture(Game::RIGHT)->getFrameWidth(), Game::WINDOW_HEIGHT / 2 + mapTextures["Avispado"]->getFrameHeight() });

    lArrow->connect([this]() {leftArrow(); });
    rArrow->connect([this]() {rightArrow(); });

    addObject(lArrow);
    addObject(rArrow);

    displayArrows();
}


MainMenuState::~MainMenuState()
{
	ofstream map(CONFIG_FILE);
	map << selectedMap;

    for (auto& mapT : mapTextures) {
        delete mapT.second;
    }
}

void MainMenuState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);

    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        switch (event.key.key)
        {
            case SDLK_LEFT:
                leftArrow();
                break;

            case SDLK_RIGHT:
                rightArrow();
                break;

            case SDLK_RETURN:
                game->pushState(new PlayState(game, maps[selectedMap]));
                break;
        }
    }
}

void MainMenuState::leftArrow() {
    // Verifica que no estamos en el primer mapa (índice 0)
    if (selectedMap - 1 >= 0)
    {
        buttons[selectedMap]->setActive(false);// Desactiva el botón actual

        selectedMap--;

        buttons[selectedMap]->setActive(true);// Activa el nuevo botón
    }
    displayArrows();
}

void MainMenuState::rightArrow() {
    // Verifica que no estamos en el último mapa
    if (selectedMap + 1 < buttons.size())
    {
        buttons[selectedMap]->setActive(false);
        selectedMap++;
        buttons[selectedMap]->setActive(true);
    }
    displayArrows();
}

// Habilita o deshabilita las flechas de navegación según los límites de la lista de mapas
void MainMenuState::displayArrows() {
    lArrow->setActive(selectedMap - 1 >= 0);
    rArrow->setActive(selectedMap + 1 < buttons.size());
}
