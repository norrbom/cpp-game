#include "modules/physics.h"
#include "modules/util.h"
#include "modules/sprite.h"

int main(const int argc, const char* argv[])
{
	sf::Vector2i win(1280, 720);
	float movementSpeed = 600.0f;
	float fpsDeltaTime = 0.0;
	const int spriteCount = 3;
	float globalSpeed = 600.0f;

	sf::RenderWindow window(sf::VideoMode(win.x, win.y), "My Game", sf::Style::Default);
	// window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	/* initialize shapes */
	sf::CircleShape ball(20.f);
	ball.setFillColor(sf::Color(150, 50, 250));
	ball.setPosition(sf::Vector2f((float)win.x/2, (float)win.y/2));

	sf::CircleShape cs1(25.f);
	Sprite sprite1(&cs1);
	sf::CircleShape cs2(25.f, 3);
	Sprite sprite2(&cs2);
	sf::RectangleShape cs3(sf::Vector2f(35.f, 35.f));
	Sprite sprite3(&cs3);

	Sprite * sprites[spriteCount];
	sprites[0] = &sprite1;
	sprites[1] = &sprite2;
	sprites[2] = &sprite3;

    sf::Clock clock;

	sf::Font font;
	if (!font.loadFromFile("3270NerdFontMono-Regular.ttf")) {
		std::cout << "Font error!";
	}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(14);
	text.setFillColor(sf::Color::White);
	text.setString("FPS: ");

	while (window.isOpen())
	{
		// Calculate deltaTime
		float deltaTime = clock.restart().asSeconds();
		fpsDeltaTime += deltaTime;
		if (fpsDeltaTime > 0.5) {
			int fps = int(1/deltaTime);
			text.setString("FPS: " + std::to_string(fps) + " speed: " + std::to_string((int)globalSpeed));
			fpsDeltaTime = 0.0;
		}


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == sf::Keyboard::Escape)
				window.close();

			sf::Vector2f movement(0.0f, 0.0f);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				movement.x -= movementSpeed * deltaTime;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				movement.x += movementSpeed * deltaTime;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				movement.y -= movementSpeed * deltaTime;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				movement.y += movementSpeed * deltaTime;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				globalSpeed = globalSpeed * 0.8f;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				globalSpeed = globalSpeed * 1.25f;

			ball.move(movement);
		}
		window.clear(sf::Color::Black);
		window.draw(ball);
		window.draw(text);

		 for (int i = 0; i < spriteCount; i++) {
			window.draw(*sprites[i]->move(deltaTime, globalSpeed, &win));
			window.draw(*sprites[i]->move(deltaTime, globalSpeed, &win));
		}
		window.display();
	}
	return 0;
}
