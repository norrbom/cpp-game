#include "modules/physics.h"
#include "modules/window.h"
#include "modules/util.h"
#include "modules/sprite.h"

using namespace std;

int main(const int argc, const char* argv[])
{
	// General settings
	sf::Clock clock;
	float fpsDeltaTime = 0.0;
	string stats = "FPS:  0";
	string GAME_TITLE = "Dungeon Escape";
	float GRAVITY = 980.0f; // cm/s
	sf::Vector2f initVelocity(rnd(100.0f, 100.0f), rnd(100.0f, 100.0f));
	int fps = 0;

	/* Initialize window */
	sf::RenderWindow window;
	sf::Vector2i win = createWindow(&window, 1024, 768, GAME_TITLE, sf::Style::Default);

	/* Initialize objects */
	sf::CircleShape characterShape(20.f);
	characterShape.setOrigin(characterShape.getRadius() , characterShape.getRadius());
	characterShape.setFillColor(sf::Color(150, 50, 250));
	float r = characterShape.getRadius();
	Sprite character(&characterShape, sf::Vector2f((float)win.x/2, (float)win.y/2), initVelocity, GRAVITY);

	float radius = 40.f;
	int count = 4;
	vector<Sprite> sprites;
	vector<sf::CircleShape> circles;
	for (int i = 0; i < count; ++i) {
		circles.push_back(sf::CircleShape(radius));
	}
	for (int i = 0; i < count; ++i) {
		sprites.push_back(Sprite(&circles[i], sf::Vector2f(rnd(radius, (float)win.x - radius), rnd(radius, (float)win.y- radius)), sf::Vector2f(rnd(100.0f, 400.0f), rnd(100.0f, 400.0f)), GRAVITY));
		sprites[i].bounciness = 0.70f;
		sprites[i].friction = 0.99f;
		sprites[i].shape->setOrigin(radius , radius);
	}

	sf::Font font;
	if (!font.loadFromFile("resources/3270NerdFontMono-Regular.ttf")) {
		throw std::runtime_error {"Could not load Font"};
	}
	sf::Text topMenu("", font, 16);

	while (window.isOpen())
	{
		// Calculate deltaTime
		float deltaTime = clock.restart().asSeconds();
		fpsDeltaTime += deltaTime;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.key.code == sf::Keyboard::F)
			{
				win = createWindow(&window, 0, 0, GAME_TITLE, sf::Style::Fullscreen);
			}

			// Control character, set full speed and direction
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				character.force = sf::Vector2f(-20000.0, 0.0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
			 	character.force = sf::Vector2f(20000.0, 0.0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			 	character.force = sf::Vector2f(0.0, -20000.0);
			}
			 if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			 	character.force = sf::Vector2f(0.0, 20000.0);
			}
		}

		window.clear(sf::Color::Black);

		if (fpsDeltaTime > 0.5) {
			fps = int(1/deltaTime);
			fpsDeltaTime = 0.0;
		}

		for (int i = 0; i < sprites.size(); i++)
		{
			sf::CircleShape * theShape = sprites[i].shape;
			sf::Vector2f pos = theShape->getPosition();
			sprites[i].move(deltaTime, &win);
			window.draw(*sprites[i].shape);
		}


		stats = "FPS: " + to_string(fps) + "\n";
		stats +=
			"Character radius: " + to_string((int)character.shape->getRadius()) + "\n"
			"Window   x: " + to_string(win.x) + " y: " + to_string(win.y) + "\n"
			"velocity x: " + to_string((int)character.velocity.x) + " y: " + to_string((int)character.velocity.y) + "\n"
			"force    x: " + to_string((int)character.force.x)    + " y: " + to_string((int)character.force.y) + "\n"
			"postion  x: " + to_string((int)character.shape->getPosition().x)    + " y: " + to_string((int)character.shape->getPosition().y) + "\n"
			"collision FLOOR: "  + to_string(character.collisions[phys::FLOOR]) + "\n"
			"collision CEILING: "  + to_string(character.collisions[phys::CEILING]) + "\n"
			"collision LEFT: "  + to_string(character.collisions[phys::LEFT]) + "\n"
			"collision RIGHT: "  + to_string(character.collisions[phys::RIGHT]);
		topMenu.setString("ESC: Quit\nF: Full screen mode\nA,W,S,D: Movement\n" + stats);
		window.draw(topMenu);
		character.move(deltaTime, &win);
		window.draw(*character.shape);
		window.display();
	}
	return 0;
}
