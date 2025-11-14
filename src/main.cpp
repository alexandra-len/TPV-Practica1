//
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Plantilla de proyecto con SDL
//

#include "game.h"
#include <string>
#include <iostream>
#include "GameError.h"
using namespace std;

int main(int argc, char* argv[])
{
	try {
		Game game = Game();
		game.run();
	}
	/*catch (GameError& e) {
		cout << "Error running game: " << e.what() << endl;
	}*/
	catch (const GameError& e) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Error del juego",e.what(),nullptr);
	}
	return 0;
}
