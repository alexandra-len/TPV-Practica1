#include "vehicle.h"
#include <cmath>
#include <SDL3_image/SDL_image.h>

// Verifica si el vehiculo colisiona con el rectangulo otherRect
Collision Vehicle::checkCollision(const SDL_FRect& otherRect) {
	Collision collision(Collision::NONE, { 0, 0 });

	// Define el rectángulo del vehículo
	SDL_FRect vehicleRect(position.getX(), position.getY(), width, height);

	if (SDL_HasRectIntersectionFloat(&vehicleRect, &otherRect)) {
		collision.type = Collision::ENEMY;
	}
	return collision;
}
