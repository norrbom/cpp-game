#include "modules/physics.h"
#include "modules/window.h"
#include "modules/util.h"
#include "modules/sprite.h"

using namespace std;

struct Tile
{
        sf::RectangleShape shape;
};

int main(const int argc, const char* argv[])
{
	// General settings
	sf::Clock clock;
	float inputDeltaTime = 0.0;
	constexpr unsigned FPS = 60;
	unsigned fps = 0;
	float GRAVITY = 980.0f; // cm/s
	string stats = "FPS: " + to_string(FPS);
	string GAME_TITLE = "Dungeon Escape";

	sf::Vector2f initVelocity(rnd(100.0f, 100.0f), rnd(100.0f, 100.0f));

	/* Initialize window and tiles */
	sf::RenderWindow window;
	sf::Vector2i win = createWindow(&window, 1024, 768, FPS, GAME_TITLE,  sf::Style::Default);
	float unitXXXL = (float)win.x/2;
	float unitXXL = (float)win.x/4;
	float unitXL = (float)win.x/8;
	float unitLarge = (float)win.x/16;
	float unitMedium = (float)win.x/32;
	float unitSmall = (float)win.x/64;
	float unitTiny = (float)win.x/128;
	float unitMicro = (float)win.x/256;
	sf::Vector2f TILE_SIZE{ unitMedium, unitMedium };

	/* Tiles */
	std::vector<Tile> tilemap;
	for (auto y = 0; y < win.y / TILE_SIZE.y; y++)
	{
        for (auto x = 0; x < win.x / TILE_SIZE.x; x++)
		{
			auto tile = new Tile();
			tile->shape.setSize( { TILE_SIZE.x, TILE_SIZE.y } );
			tile->shape.setPosition(x * TILE_SIZE.x, y * TILE_SIZE.y);
			tile->shape.setOutlineThickness(0.5f);
			tile->shape.setOutlineColor(sf::Color(255, 125, 125, 32));
			tile->shape.setFillColor(sf::Color(125, 125, 125, 32));
			tilemap.push_back(*tile);
		}
	}

	/* Fixed objects */
	vector<sf::RectangleShape> rectangles;

	float rectangleSizes[2][4] = {
		{unitXXXL, unitLarge, win.x - unitXXXL/2, win.y - unitLarge/2},
		{unitXL, unitXL, win.x/4 - unitXL/2, win.y - unitXL/2}
	};

	for (int i = 0; i < sizeof(rectangleSizes) / sizeof(rectangleSizes[0]); i++) {
		rectangles.push_back(sf::RectangleShape({rectangleSizes[i][0], rectangleSizes[i][1]}));
		rectangles[i].setOrigin(rectangleSizes[i][0]/2, rectangleSizes[i][1]/2);
		rectangles[i].setPosition({rectangleSizes[i][2], rectangleSizes[i][3]});
		rectangles[i].setFillColor(sf::Color(64, 64, 64));
	}

	/* Initialize objects */
	sf::CircleShape characterShape(unitSmall);
	characterShape.setOrigin(characterShape.getRadius() , characterShape.getRadius());
	characterShape.setFillColor(sf::Color(150, 50, 250));
	float r = characterShape.getRadius();
	Sprite character(&characterShape, sf::Vector2f((float)win.x/2, (float)win.y/2), initVelocity, GRAVITY);

	int count = 10;
	vector<Sprite> sprites;
	vector<sf::CircleShape> circles;
	for (int i = 0; i < count; ++i) {
		circles.push_back(sf::CircleShape(unitTiny));
	}
	for (int i = 0; i < count; ++i) {
		sprites.push_back(Sprite(&circles[i], sf::Vector2f(rnd(unitTiny, (float)win.x - unitTiny), rnd(unitTiny, (float)win.y/3)), sf::Vector2f(rnd(100.0f, 400.0f), rnd(100.0f, 400.0f)), GRAVITY));
		sprites[i].bounciness = 0.70f;
		sprites[i].friction = 0.99f;
		sprites[i].shape->setOrigin(sprites[i].shape->getRadius(), sprites[i].shape->getRadius());
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
		inputDeltaTime += deltaTime;
		int lastkey = -1;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.key.code == sf::Keyboard::F)
			{
				win = createWindow(&window, 0, 0, FPS, GAME_TITLE, sf::Style::Fullscreen);
			}

			// Control character
			if (character.collisions[phys::FLOOR])
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					lastkey = sf::Keyboard::A;
					character.force = sf::Vector2f(-r*128, 0.0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					lastkey = sf::Keyboard::D;
					character.force = sf::Vector2f(r*128, 0.0);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					if (lastkey == sf::Keyboard::A)
					{
						character.force = sf::Vector2f(-r*1024, -r*2048);
					}
					else if (lastkey == sf::Keyboard::D)
					{
						character.force = sf::Vector2f(r*1024, -r*2048);
					}
					// jump up
					else {
						character.force = sf::Vector2f(0.0, -r*2048);
					}
				}
			}
		}

		if (inputDeltaTime > .3) {
			fps = int(1/deltaTime);
			lastkey = -1;
			inputDeltaTime = 0.0;
		}

		/* Start drawing */
		window.clear(sf::Color::Black);

		/* Draw fixed objects */
		int i = 0;
		sf::Text tileText(to_string(i), font, 11);
		for (auto& it : tilemap) {
			window.draw(it.shape);
			tileText.setString(to_string(i));
			tileText.setPosition(it.shape.getPosition().x, it.shape.getPosition().y);
			tileText.setFillColor(sf::Color(125, 125, 125, 125));
			window.draw(tileText);
			i++;
		}
		for (int i = 0; i < rectangles.size(); i++)
		{
			window.draw(rectangles[i]);
		}


		/* Move and draw sprites */
		for (int i = 0; i < sprites.size(); i++)
		{
			sf::CircleShape * theShape = sprites[i].shape;
			sprites[i].move(deltaTime, &win, &rectangles);
			window.draw(*sprites[i].shape);
		}

		/* Move and draw the character */
		character.move(deltaTime, &win, &rectangles);
		window.draw(*character.shape);

		/* Draw stats */
		sf::Vector2f pos = character.shape->getPosition();
		float r = character.shape->getRadius();
		stats = "FPS: " + to_string(fps) + "\n";
		stats +=
			// "Character radius: " + to_string((int)character.shape->getRadius()) + "\n"
			// "Window   x: " + to_string(win.x) + " y: " + to_string(win.y) + "\n"
			// "velocity x: " + to_string((int)character.velocity.x) + " y: " + to_string((int)character.velocity.y) + "\n"
			// "force    x: " + to_string((int)character.force.x)    + " y: " + to_string((int)character.force.y) + "\n"
			// "postion  x: " + to_string((int)pos.x)    + " y: " + to_string((int)pos.y) + "\n"
			"collision FLOOR: "  + to_string(character.collisions[phys::FLOOR]) + "\n"
			// "collision CEILING: "  + to_string(character.collisions[phys::CEILING]) + "\n"
			// "collision LEFT: "  + to_string(character.collisions[phys::LEFT]) + "\n"
			// "collision RIGHT: "  + to_string(character.collisions[phys::RIGHT]) + "\n"
			"tiles    #: 0 - " + to_string((int)((int)win.x/TILE_SIZE.x * (int)win.y/TILE_SIZE.y)-1) + "\n"
			"tile     #: " + to_string(
				(int)(
					((int)(pos.y/TILE_SIZE.y))*
					(int)win.x/TILE_SIZE.x +
					(int)((pos.x)/TILE_SIZE.x)
					)
			);
		topMenu.setString("ESC: Quit\nF: Full screen mode\nA,W,S,D: Movement\n" + stats);
		window.draw(topMenu);

		window.display();
	}
	return 0;
}