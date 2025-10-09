#include "vector2D.h"

#include <cmath>

template<typename T>
void Vector2D<T>::normalize() {
	double mag = sqrt(pow(x, 2) + pow(y, 2));
	if (mag > 0.0) {
		x = x / mag;
		y = y / mag;
	}
}

template<typename T>
Vector2D<T> Vector2D<T>::operator*(double d) const {
	Vector2D r;
	r.x = x * d;
	r.y = y * d;
	return r;
}

template<typename T>
T Vector2D<T>::operator*(const Vector2D& d) const {
	return d.x * x + d.y * y;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector2D<T>& v) {
	os << "(" << v.x << "," << v.y << ")";
	return os;
}