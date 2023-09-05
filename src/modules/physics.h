#ifndef MY_PHYSICS
#define MY_PHYSICS

using namespace std;

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

	/*
	Collision detection on CircleShape and a set of RectangleShapes that has centered origin
	*/
	std::array<int,2> collisionRectangles(sf::CircleShape * shape, std::vector<sf::RectangleShape, std::allocator<sf::RectangleShape>> *rectangles)
	{
		assert(shape != NULL && rectangles != NULL);
		sf::Vector2f pos = shape->getPosition();
		float radius = shape->getRadius();
		float shape_left = pos.x - radius;
		float shape_right = pos.x + radius;
		float shape_top = pos.y - radius;
		float shape_bottom = pos.y + radius;
		collisions = {0,0,0,0};
		int x_overlap = 0;
		int y_overlap = 0;

		for (int i = 0; i < rectangles->size(); i++)
		{
			sf::Vector2f rpos = (*rectangles)[i].getPosition();
			sf::Vector2f rsize = (*rectangles)[i].getSize();
			// (a.left < b.right) && (a.right > b.left)
			// (a.top < b.bottom) && (a.bottom > b.top)
			x_overlap = (shape_left < (rpos.x + rsize.x/2) ) && (shape_right > (rpos.x - rsize.x/2));
			y_overlap = (shape_top < (rpos.y + rsize.y/2) ) && (shape_bottom > (rpos.y - rsize.y/2));
			if (x_overlap > 0 && y_overlap > 0)
				return {x_overlap, y_overlap};
		}
		return {0, 0};
	}

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