#ifndef MY_SPRITE
#define MY_SPRITE

class Sprite
{
    public:
        // p must be a pointer returned by new; it must not be NULL
        Sprite(sf::Shape* shape, float speed):
            shape(shape),
            speed(speed),
            direction(rnd(-1, 1), rnd(-1, 1))
        {
            assert(shape != NULL);
            shape->setFillColor(randColor());
        }
        sf::Shape* shape;
        float speed;
        sf::Shape* move(float deltaTime, sf::Vector2i* w) {

            if (touchedGround(shape, (*w).y) || touchedCeiling(shape)) {
                shape->setFillColor(randColor());
                direction.y = direction.y * -1.0f;
            }
            if (touchedRightWall(shape, (*w).x) || touchedLeftWall(shape)) {
                shape->setFillColor(randColor());
                direction.x = direction.x * -1.0f;
            }
            float distance = speed * deltaTime;
            shape->move(sf::Vector2f(distance * direction.x, distance * direction.y));
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