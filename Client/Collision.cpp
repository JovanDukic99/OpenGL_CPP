#include "Collision.h"

bool Collision::squareCollision(Square s1, Square s2) {
	return squareOverlap(s1, s2) || squareOverlap(s2, s1);
}

bool Collision::squareOverlap(Square s1, Square s2) {
	if (s1.getX() + s1.getWidth() < s2.getX()) {
		return false;
	}

	if (s2.getX() + s2.getWidth() < s1.getX()) {
		return false;
	}

	if (s1.getY() < s2.getY()) {
		return false;
	}

	if (s2.getY() + s2.getHeight() < s1.getY()) {
		return false;
	}

	return true;
}
