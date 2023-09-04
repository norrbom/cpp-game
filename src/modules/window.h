using namespace std;

sf::Vector2i createWindow(sf::RenderWindow * window, int x, int y, unsigned fps, string title, int style) {
    if (style != sf::Style::Fullscreen) {
        window->create(sf::VideoMode(x, y), title, style);
    }
    else {
        window->create(sf::VideoMode::getFullscreenModes()[0], title, style);
    }
    window->setFramerateLimit(fps);
    sf::Image icon;
    if (!icon.loadFromFile("resources/scull-icon.png"))
        throw std::runtime_error {"Could not load icon file"};
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    return sf::Vector2i(window->getSize().x, window->getSize().y);
}