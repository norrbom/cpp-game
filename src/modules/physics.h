#ifndef MY_PHYSICS
#define MY_PHYSICS

bool touchedGround(sf::Shape* s, int y) {
	if (s->getPosition().y > y) return true;
	return false;
}
bool touchedCeiling(sf::Shape* s) {
	if (s->getPosition().y < 0) return true;
	return false;
}
bool touchedRightWall(sf::Shape* s, int x) {
	if (s->getPosition().x > x) return true;
	return false;
}
bool touchedLeftWall(sf::Shape* s) {
	if (s->getPosition().x < 0) return true;
	return false;
}

#endif