#include "modules/physics.h"
#include "modules/util.h"
#include "modules/sprite.h"

using namespace std;

int main(const int argc, const char* argv[])
{
	sf::Vector2i win(1280, 720);
	int speed = 3;
	float speeds[6] = { 0.0, 100.0, 200.0, 400.0, 800.0, 1600.0 }; // pixels per second
	float fpsDeltaTime = 0.0;
	string fpsTxt = "FPS:  0";
	string spriteSpeedsTxt = "";

	sf::RenderWindow window(sf::VideoMode(win.x, win.y), "My Game", sf::Style::Default);
	// window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	/* initialize shapes */
	sf::CircleShape ball(20.f);
	ball.setFillColor(sf::Color(150, 50, 250));
	ball.setPosition(sf::Vector2f((float)win.x/2, (float)win.y/2));

	sf::CircleShape cs1(25.f);
	Sprite sprite1(&cs1, speeds[speed]);
	sf::CircleShape cs2(25.f, 3);
	Sprite sprite2(&cs2, speeds[speed]);
	sf::RectangleShape cs3(sf::Vector2f(35.f, 35.f));
	Sprite sprite3(&cs3, speeds[speed]);
	sf::CircleShape cs4(15.f, 3);
	Sprite sprite4(&cs4, speeds[speed]);
	sf::CircleShape cs5(15.f, 3);
	Sprite sprite5(&cs5, speeds[speed]);


	Sprite * sprites[5];

	sprites[0] = &sprite1;
	sprites[1] = &sprite2;
	sprites[2] = &sprite3;
	sprites[3] = &sprite4;
	sprites[4] = &sprite5;
	int spriteCount = sizeof(sprites)/sizeof(sprites[0]);

    sf::Clock clock;

	sf::Font font;
	if (!font.loadFromFile("3270NerdFontMono-Regular.ttf")) {
		cout << "Font error!";
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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				speed = (speed > 1 ? speed -= 1 : 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				int max = sizeof(speeds)/sizeof(speeds[0]) - 1;
				speed = (speed < max ? speed += 1 : max);
				cout << speed << " " << sizeof(speeds)/sizeof(speeds[0]) << "\n";
			}
			for (int i = 0; i < spriteCount; i++) {
				sprites[i]->speed = speeds[speed];
			}
			sf::Vector2f movement(0.0f, 0.0f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				movement.x -= speeds[speed] * deltaTime;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				movement.x += speeds[speed] * deltaTime;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				movement.y -= speeds[speed] * deltaTime;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				movement.y += speeds[speed] * deltaTime;

			ball.move(movement);
		}

		window.clear(sf::Color::Black);

		if (fpsDeltaTime > 0.5) {
			int fps = int(1/deltaTime);
			fpsTxt = "FPS: " + to_string(fps);
			fpsDeltaTime = 0.0;
		}

		spriteSpeedsTxt = "";
		for (int i = 0; i < spriteCount; i++)
		{
			spriteSpeedsTxt += "\nspeed: ";
			spriteSpeedsTxt += to_string((int)sprites[i]->speed);
			spriteSpeedsTxt += " pos: (";
			sf::Vector2f pos = sprites[i]->shape->getPosition();
			spriteSpeedsTxt += to_string((int)pos.x);
			spriteSpeedsTxt += ", ";
			spriteSpeedsTxt += to_string((int)pos.y);
			spriteSpeedsTxt += ")";
			window.draw(*sprites[i]->move(deltaTime, &win));
		}

		topMenu.setString(fpsTxt + spriteSpeedsTxt);
		window.draw(topMenu);
		window.draw(ball);
		window.display();
	}
	return 0;
}
