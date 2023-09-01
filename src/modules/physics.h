#ifndef MY_PHYSICS
#define MY_PHYSICS

class Collision
{
    public:
		Collision(sf::CircleShape * shape): shape(shape)
		{
			assert(shape != NULL);
			radius = shape->getRadius();
			pos = shape->getPosition();
		}
		sf::CircleShape * shape;
		sf::Vector2f pos;
		float radius;
		/*
		returns:
			0: No collsision
			1: floor collision
			2: ceiling collision
			3: left collision
			4: right collision
		*/
		int window(sf::Vector2i * win) {
			if (pos.y + radius > win->y) return 1;
			if (pos.y - radius < 0)      return 2;
			if (pos.x - radius < 0)      return 3;
			if (pos.x + radius > win->x) return 4;
			return 0;
		}
};

#endif