#ifndef MY_PHYSICS
#define MY_PHYSICS

namespace phys
{
	std::array<int,4> collisions;

	enum edge
	{
		FLOOR,
		CEILING,
		LEFT,
		RIGHT
	};

	// TODO: return an array of multiple collisions
	std::array<int,4> collision(sf::CircleShape * shape, sf::Vector2i * frame)
	{
		assert(shape != NULL && frame != NULL);
		sf::Vector2f pos = shape->getPosition();
		float radius = shape->getRadius();
		collisions = {0,0,0,0};

		if (pos.y + radius >= frame->y) collisions[FLOOR]   = 1;
		if (pos.y - radius <= 0)        collisions[CEILING] = 1;
		if (pos.x - radius <= 0)        collisions[LEFT]    = 1;
		if (pos.x + radius >= frame->x) collisions[RIGHT]   = 1;
		return collisions;
	}
}
#endif