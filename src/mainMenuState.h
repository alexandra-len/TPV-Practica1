#pragma once
#include "gameState.h"
#include "game.h"
#include <SDL3/SDL.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>
#include "texture.h"

class Button;

class MainMenuState : public GameState
{
private:
    // Lista de nombres de archivos de mapa disponibles
    std::vector<std::string> maps;
    // Lista de botones de selección de mapa
    std::vector<Button*> buttons;
    // Índice del mapa seleccionado actualmente
    int selectedMap = 0;

    // Map con las texturas
    std::unordered_map<std::string, Texture*> mapTextures;

    Button* lArrow;
    Button* rArrow;

public:
    MainMenuState(Game* g);
    ~MainMenuState();

    void handleEvent(const SDL_Event&) override;
    void leftArrow();
    void rightArrow();
    void displayArrows();// Habilita/deshabilita las flechas según si hay mapas adyacentes

    std::string path2string(const std::filesystem::path& p) {
        return reinterpret_cast<const char*>(p.u8string().c_str());
    }
};

