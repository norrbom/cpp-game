#ifndef MY_SPRITE
#define MY_SPRITE

class Sprite
{
    public:
        Sprite() {};
        Sprite(sf::CircleShape* shape, sf::Vector2f pos, sf::Vector2f velocity, float gravity):
            shape(shape),
            velocity(velocity),
            gravity(gravity)
        {
            assert(shape != NULL);
            shape->setPosition(pos);
            shape->setFillColor(randColor());
        };

        sf::CircleShape* shape;
        sf::Vector2f force; // external force on on the Sprite
        sf::Vector2f velocity;

        float bounciness = 0.2f;
        float friction = 0.8f;
        float mass = 1.0f;    // kg
        float gravity = 980.0f; // (cm/s^2)
        std::array<int,4> collisions;

        // force = mass * acceleration
        // acceleration = force / mass
        // velocity = force / mass * dt
        // velocity = acceleration * dt
        // acceleration = velocity / dt
        void applyForces(float dt) {
            velocity.x += force.x / mass * dt;
            // avoid gravity causing micro bouncing forever
            if (collisions[phys::FLOOR] && abs(velocity.y) < (bounciness * gravity / 10) && abs(force.y) < 0.1f)
            {
                velocity.y = 0.0f;
                // TODO: friction on Y and headwind
                velocity.x = velocity.x * friction;
            }
            else {
                velocity.y += gravity * dt + (force.y / mass * dt);
            }
            sf::Vector2f pos = shape->getPosition();
            shape->setPosition(pos.x + (velocity.x * dt), pos.y + (velocity.y * dt));
            force = sf::Vector2f(0.0f, 0.0f);
        }

        void move(float dt, sf::Vector2i * win) {
            collisions = phys::collision(shape, win);
            if (collisions[phys::FLOOR] || collisions[phys::CEILING] || collisions[phys::LEFT] || collisions[phys::RIGHT]) {
                shape->setFillColor(randColor());
                bounce(collisions, win);
            }
            applyForces(dt);

        }
    private:
        void bounce(std::array<int,4> collision, sf::Vector2i * win) {
            sf::Vector2f pos = shape->getPosition();
            float rad = shape->getRadius();
            if (collisions[phys::FLOOR]) {
                shape->setPosition(pos.x, (float)win->y - rad);
                velocity.y = -abs(velocity.y) * bounciness;
            }
            if (collisions[phys::CEILING]) {
                shape->setPosition(pos.x, rad);
                velocity.y = abs(velocity.y) * bounciness;
            }
            if (collisions[phys::LEFT]) {
                shape->setPosition(rad, pos.y);
                velocity.x = abs(velocity.x) * bounciness;
            }
            if (collisions[phys::RIGHT]) {
                shape->setPosition((float)win->x - rad, pos.y);
                velocity.x = -abs(velocity.x) * bounciness;
            }
        }
        sf::Color randColor() {
            return sf::Color((int)rnd(50, 255), (int)rnd(50, 255), (int)rnd(50, 255));
        }
};

#endif