#ifndef MY_SPRITE
#define MY_SPRITE

class Sprite
{
    public:
        Sprite() {};
        Sprite(sf::CircleShape* shape, sf::Vector2f pos, float speed):
            shape(shape),
            speed(speed)
        {
            assert(shape != NULL);
            shape->setPosition(pos);
            shape->setFillColor(randColor());
        };
        sf::CircleShape* shape;
        sf::Vector2f direction;
        float speed;
        float friction = 1.0;
        void move(float deltaTime, sf::Vector2i * w) {
            float distance = speed * deltaTime;
            sf::Vector2f beforePos = shape->getPosition();
            shape->move(sf::Vector2f(distance * direction.x, distance * direction.y));
            // if (Collision(shape).window(w)) {
            //     // undo move
            //     shape->setPosition(beforePos);
            // }
            // slow down speed due to friction
            speed = speed * friction;

        }
        void autoMove(float deltaTime, sf::Vector2i * win) {
            bounce(win);
            //float distance = speed * deltaTime;
            move(deltaTime, win);
            //shape->move(sf::Vector2f(distance * direction.x, distance * direction.y));
        }
    private:
        void bounce(sf::Vector2i * win) {
            int col = Collision(shape).window(win);
            if (col != 0) {
                shape->setFillColor(randColor());
            }
            if (col == 1) {
                direction.y = -abs(direction.y);
            }
            if (col == 2) {
                direction.y = abs(direction.y);
            }
            if (col == 3) {
                direction.x = abs(direction.x);
            }
            if (col == 4) {
                direction.x = -abs(direction.x);
            }
        }
        sf::Color randColor() {
            return sf::Color((int)rnd(50, 255), (int)rnd(50, 255), (int)rnd(50, 255));
        }
};

#endif