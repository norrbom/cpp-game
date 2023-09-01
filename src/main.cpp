#include "modules/physics.h"
#include "modules/util.h"
#include "modules/sprite.h"

using namespace std;

int main(const int argc, const char* argv[])
{
	// General settings
	sf::Clock clock;
	float fpsDeltaTime = 0.0;
	string fpsTxt = "FPS:  0";
	string GAME_TITLE = "My Game";

	// NPC Settings
	int speed = 3;
	float speeds[6] = { 0.0, 100.0, 200.0, 400.0, 800.0, 1600.0 }; // pixels per second

	/* Initialize window */
	sf::Vector2i win(1024, 768);
	sf::RenderWindow window(sf::VideoMode(win.x, win.y), "My Game", sf::Style::Default);
	// window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	/* Initialize objects */
	sf::CircleShape characterShape(20.f);
	characterShape.setOrigin(characterShape.getRadius() , characterShape.getRadius());
	characterShape.setFillColor(sf::Color(150, 50, 250));
	float r = characterShape.getRadius();
	Sprite character(&characterShape, sf::Vector2f((float)win.x/2, (float)win.y/2), speeds[speed]);
	character.friction = 0.9f;

	float diam = 10.f;
	int count = 400;
	vector<Sprite> sprites;
	vector<sf::CircleShape> circles;
	for (int i = 0; i < count; ++i) {
		circles.push_back(sf::CircleShape(diam));
	}
	for (int i = 0; i < count; ++i) {
		sprites.push_back(Sprite(&circles[i], sf::Vector2f(rnd(diam / 2, (float)win.x - (diam / 2)), diam / 2), speeds[speed]));
		sprites[i].direction = sf::Vector2f(rnd(-1.0f, 1.0f), rnd(-1.0f, 1.0f));
		sprites[i].shape->setOrigin(diam/2 , diam/2);
		sprites[i].friction = 0.99f;
	}

	sf::Font font;
	if (!font.loadFromFile("3270NerdFontMono-Regular.ttf")) {
		cout << "[ERROR] Could not load Font!";
	}
	sf::Text topMenu;
	topMenu.setFont(font);
	topMenu.setCharacterSize(14);
	topMenu.setFillColor(sf::Color::White);

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
				window.create(sf::VideoMode::getFullscreenModes()[0], GAME_TITLE, sf::Style::Fullscreen);
				window.setFramerateLimit(60);
				win = sf::Vector2i(window.getSize().x, window.getSize().y);
			}


			// Control speed
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				speed = (speed > 1 ? speed -= 1 : 0);
				for (int i = 0; i < sprites.size(); i++) {
					sprites[i].speed = speeds[speed];
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				int max = sizeof(speeds)/sizeof(speeds[0]) - 1;
				speed = (speed < max ? speed += 1 : max);
				for (int i = 0; i < sprites.size(); i++) {
					sprites[i].speed = speeds[speed];
				}
			}

			// Control character, set full speed and direction
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				character.speed = speeds[speed];
				character.direction = sf::Vector2f(-1.0, 0.0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
				character.speed = speeds[speed];
			 	character.direction = sf::Vector2f(1.0, 0.0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
				character.speed = speeds[speed];
			 	character.direction = sf::Vector2f(0.0, -1.0);
			}
			 if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
				character.speed = speeds[speed];
			 	character.direction = sf::Vector2f(0.0, 1.0);
			}
		}

		window.clear(sf::Color::Black);

		if (fpsDeltaTime > 0.5) {
			int fps = int(1/deltaTime);
			fpsTxt = "FPS: " + to_string(fps);
			fpsDeltaTime = 0.0;
		}

		for (int i = 0; i < sprites.size(); i++)
		{
			sf::CircleShape * theShape = sprites[i].shape;
			sf::Vector2f pos = theShape->getPosition();
			sprites[i].autoMove(deltaTime, &win);
			window.draw(*sprites[i].shape);
		}

		topMenu.setString(fpsTxt + "\nESC: Quit\nF: Full screen mode\nArrows: Speed\nAWSD: Movement");
		window.draw(topMenu);
		character.move(deltaTime, &win);
		window.draw(*character.shape);
		window.display();
	}
	return 0;
}
