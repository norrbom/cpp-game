#ifndef MY_SPRITE
#define MY_SPRITE

class Sprite
{
    public:
        // p must be a pointer returned by new; it must not be NULL
        Sprite(sf::Shape* s): shape(s), direction(rnd(-1, 1), rnd(-1, 1)) {
            assert(shape != NULL);
            shape->setFillColor(randColor());
        }
        sf::Shape* shape;
        sf::Shape* move(float deltaTime, float speed, sf::Vector2i* w) {

            if (touchedGround(shape, (*w).y)) {
                shape->setFillColor(randColor());
                direction.y = -1.0;
            }
            if (touchedCeiling(shape)) {
                shape->setFillColor(randColor());
                direction.y = 1.0;
            }
            if (touchedRightWall(shape, (*w).x)) {
                shape->setFillColor(randColor());
                direction.x = -1.0;
            }
            if (touchedLeftWall(shape)) {
                shape->setFillColor(randColor());
                direction.x = 1.0;
            }

            sf::Vector2f movement(0.0f, 0.0f);
            float distance = speed * deltaTime;
            movement.x = distance * direction.x;
            movement.y = distance * direction.y;

            shape->move(movement);
            return shape;
        }
    private:
        sf::Vector2f direction;

        float rnd(int min, int max) {
            // construct a trivial random generator engine from a time-based seed:
            RangeRandGenerator generator(min, max);
            return (float) generator.get();
        }
        sf::Color randColor() {
            return sf::Color((int)rnd(50, 255), (int)rnd(50, 255), (int)rnd(50, 255));
        }
};

#endif